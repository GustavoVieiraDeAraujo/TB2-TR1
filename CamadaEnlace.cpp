#include "./CamadaEnlace.hpp"
#include "./CamadaFisica.hpp"

// Função para converter um número inteiro em um número binário (não é no formato ASCII)
// A função já retorna o número binário com a quantidade de casas desejadas
vector<char> converter_decimal_em_byte (int numero, int tamanho) {
    vector<char> numero_binario;
    const int n = 8;
 
    // Transforma o inteiro em binário, com 8 algarismos significativos
    string binario = bitset<n>(numero).to_string();

    // Laço para reduzir o número binário na quantidade de casas desejadas
    for (int i = binario.size() - tamanho; i < binario.size(); i++) {
        numero_binario.push_back(binario[i]);
    }

    return numero_binario;
}

// Função para converter um número binário em um número inteiro (não é no formato ASCII)
int converter_byte_em_decimal (vector<char> numero_binario, int tamanho) {
    int numero_inteiro = 0;

    for (char bit : numero_binario) {
        // Condição para evitar que o tamanho seja negativo
        if ( tamanho < 0) {
            break;
        }

        // Transforma um char em int
        int num = bit - '0';
        if (num == 1) {
            numero_inteiro += pow(2, tamanho);
        }

        tamanho--;
    }

    return numero_inteiro;
}

// Função para fazer a divisão do CRC
vector<char> divisao_de_bit (vector<char> quadro, vector<char> polinomio_gerador) {
    // As quantidade de repetições é a diferença entre o quadro total e n-1
    // OBS -> n = o tamanho do polinomio gerador
    int repeticoes = quadro.size() - (polinomio_gerador.size() - 1);
    vector<char> resto_da_divisao;
    vector<char> parte_do_divisor;
    vector<char> divisor;

    // Laço para fazer divisão
    for (int i = 0; i < repeticoes; i++) {
        // Laço para separar a parte do dividendo utilizado para dividir, sendo responsável por separar n primeiros bits e calcula o xor entre o dividendo e o divisor
        for (int x = 0; x < polinomio_gerador.size(); x++) {
            // Inicio da divisão, separa os n primeiros bits para começar a divisão
            if (i == 0 || x == 0) {
                parte_do_divisor.push_back(quadro.front());
                quadro.erase(quadro.begin());
            }
            
            if (parte_do_divisor[0] == '0') {
                // Se o início do grupo de dividendo é zero, ele pula essa etapa da divisão (mesma coisa que fazer a divisão binária por zero)
                divisor = {'0', '0', '0', '0'};
            } else {
                divisor = polinomio_gerador;
            }

            // Transforma os char de cada quadro (quadro do divisor e quadro do dividendo) em int
            int num1 = parte_do_divisor[x] - '0';
            int num2 = divisor[x] - '0';
            // Realiza o xor
            int resultado_int = num1 ^ num2;

            // Transforma resultado<int> em um bit<char>
            string resultado_string = to_string(resultado_int);
            char resultado_char = resultado_string[0];
            resto_da_divisao.push_back(resultado_char);

        }
        
        //  Adiciona o resto da divisão para a próxima etapa da divisão
        parte_do_divisor = resto_da_divisao;
        parte_do_divisor.erase(parte_do_divisor.begin());
        resto_da_divisao.clear();
    }

    return parte_do_divisor;
}

vector<char> camada_enlace_dados_transmissora (vector<char> quadro, int enquadramento, int controle) {
    vector<char> quadro_com_enquadramento;
    quadro_com_enquadramento = camada_enlace_dados_transmissora_enquadramento(quadro, enquadramento);

    vector<char> quadro_com_controle_de_erro;
    quadro_com_controle_de_erro = camada_enlace_dados_transmissora_controle_de_erro(quadro_com_enquadramento, controle);

    return quadro_com_controle_de_erro;
}

vector<char> camada_enlace_dados_transmissora_enquadramento (vector<char> quadro, int tipo_de_enquadramento) {
    vector<char> quadro_encapsulado;

    switch (tipo_de_enquadramento) {
        case 0:
            quadro_encapsulado = camada_enlace_dados_transmissora_enquadramento_contagem_de_caracteres(quadro);
            break;
        case 1:
            quadro_encapsulado = camada_enlace_dados_transmissora_enquadramento_insercao_de_bytes(quadro);
            break;
    }

    return quadro_encapsulado;
}

// Função para fazer o enquadramento por contagem de caracteres
vector<char> camada_enlace_dados_transmissora_enquadramento_contagem_de_caracteres (vector<char> quadro_bruto) {
    // Flag que limita a quantidade de caracteres por quadro
    int tamanho_do_quadro = 5;
    vector<char> quadro_com_cabecalho;
    // Transforma a flag em binario (ASCII)
    string cabecalho_max = converter_mensagem_em_bit(to_string(tamanho_do_quadro));

    string cabecalho;
    int tamanho_q = 0;

    while (quadro_bruto.size() > 0) {
        // O quadro é maior que a flag
        if (quadro_bruto.size() >= tamanho_do_quadro) {
            cabecalho = cabecalho_max;
            tamanho_q = tamanho_do_quadro;
        // O quadro é menor que a flag, então a flag é ajustada para o tamanho que o quadro possui     
        } else {
            cabecalho = converter_mensagem_em_bit(to_string(quadro_bruto.size()));;
            tamanho_q = quadro_bruto.size(); 
        }

        // Adiciona o cabeçalho (flag em ASCII)
        for (char bit : cabecalho) {
                quadro_com_cabecalho.push_back(bit);
        }

        // Adiciona os bits do quadro de acordo com a flag
        for (int i = 0; i < tamanho_q; i++) {
            quadro_com_cabecalho.push_back(quadro_bruto[0]);
            quadro_bruto.erase(quadro_bruto.begin());
        }
    }

    return quadro_com_cabecalho;
}

// Função para fazer o enquadramento por inserção de bytes
vector<char> camada_enlace_dados_transmissora_enquadramento_insercao_de_bytes (vector<char> quadro_bruto) {
    int tamanho_do_quadro = 3; // Tamanho do quadro de Bytes (sem considerar os 2 bytes de cabeçalho e possível byte de flag esc)
    vector<char> quadro_com_cabecalho;
    // Flag estabelecida
    string flag = "11110000";
    string esc = "00011011";

    while (quadro_bruto.size() > 0) {
        // Adiciona o cabeçalho inicial
        for (char i : flag) {
            quadro_com_cabecalho.push_back(i);
        }

        // Se a quantidade de bytes do quadro a ser enviado é menor que o tamanho_do_quadro, ele envia todos os bytes
        if (quadro_bruto.size() < tamanho_do_quadro * 8) {
            tamanho_do_quadro = quadro_bruto.size() / 8;
        }
        
        for (int i = 0; i < tamanho_do_quadro; i++) {
            string verificador_de_flag = "";
            // Laço para separar os 8 bits antes de inserir no quadro final
            for (int x = 0; x < 8; x++) { // Range de 8 para adicionar 8 bits (byte)
                verificador_de_flag += quadro_bruto[0];
                quadro_bruto.erase(quadro_bruto.begin());
            }
            
            // Verifica se o byte tem o mesmo valor que a flag
            if (verificador_de_flag == flag) {
                // Se tiver, um byte ESC é adicionado
                for (char bit : esc) {
                    quadro_com_cabecalho.push_back(bit);
                }    
            }
            
            // Adiciona o byte no quadro final
            for (char bit : verificador_de_flag) {
                quadro_com_cabecalho.push_back(bit);    
            }
        }

        // Adiciona o cabeçalho final
        for (char i : flag) {
            quadro_com_cabecalho.push_back(i);
        }
    }

    return quadro_com_cabecalho;
}

vector<char> camada_enlace_dados_transmissora_controle_de_erro (vector<char> quadro, int tipo_de_controle_de_erro) {
    vector<char> quadro_com_controle_de_erro;

    switch (tipo_de_controle_de_erro) {
        case 0: //bit de paridade par
            quadro_com_controle_de_erro = camada_enlace_dados_transmissora_controle_de_erro_bit_paridade_par(quadro);
            break;
        case 1: //CRC
            quadro_com_controle_de_erro = camada_enlace_dados_transmissora_controle_de_erro_crc(quadro);
            break;
    }

    return quadro_com_controle_de_erro;
}

// Função para fazer o controle por bit de paridade
vector<char> camada_enlace_dados_transmissora_controle_de_erro_bit_paridade_par (vector<char> quadro) {
    int valor_bit_paridade = 0;

    // Pega cada bit do quadro e faz o cálculo de XOR com o bit anterior
    for (char bit : quadro) {
        // Transforma <char> em <int>
        int num = bit - '0';
        valor_bit_paridade = num ^ valor_bit_paridade;
    }

    // Transforma <int> em <char>, e adiciona no quadro resultante
    string bit_paridade = to_string(valor_bit_paridade);
    for (char bit_p : bit_paridade) {
        quadro.push_back(bit_p);
    }

    return quadro;
}

// Função para fazer o controle por crc
vector<char> camada_enlace_dados_transmissora_controle_de_erro_crc (vector<char> quadro) {
    // Define o polinomio gerador
    vector<char> polinomio_gerador = {'1', '0', '0', '0', '1', '0', '0', '1', '0', '1', '1', '1', '1', '1', '0', '1'};
    vector<char> resto_da_divisao;
    // Quadro exclusivo para fazer a primeira divisão
    vector<char> quadro_dividendo = quadro;

    // Adiciona n-1 bits de valor 0 no quadro (n = quant. de bits do polinômio gerador)
    for (int i = 0; i < polinomio_gerador.size() - 1; i++) {
        quadro_dividendo.push_back('0');
    }

    // Faz a divisão de bits e recebe o resto da divisão
    resto_da_divisao = divisao_de_bit(quadro_dividendo, polinomio_gerador);

    // Adiciona o resto da divisão no final do quadro
    for (char i : resto_da_divisao) {
        quadro.push_back(i);
    }

    return quadro;
}

vector<char> camada_enlace_dados_receptora (vector<char> quadro_recebido, int enquadramento, int controle) {
    vector<char> quadro_deteccao_feita;
    quadro_deteccao_feita = camada_enlace_dados_receptora_controle_de_erro(quadro_recebido, controle);

    vector<char> quadro_sem_enquadramento;
    quadro_sem_enquadramento = camada_enlace_dados_receptora_enquadramento(quadro_deteccao_feita, enquadramento);

    return quadro_sem_enquadramento;
}

vector<char> camada_enlace_dados_receptora_enquadramento (vector<char> quadro_encapsulado, int tipo_de_enquadramento) {
    vector<char> quadro;

    switch (tipo_de_enquadramento) {
        case 0:
            quadro = camada_enlace_dados_receptora_enquadramento_contagem_de_caracteres(quadro_encapsulado);
            break;
        case 1:
            quadro = camada_enlace_dados_receptora_enquadramento_insercao_de_bytes(quadro_encapsulado);
            break;
    }

    return quadro;
}

// Função para desfazer o enquadramento por contagem de caracteres
vector<char> camada_enlace_dados_receptora_enquadramento_contagem_de_caracteres (vector<char> quadro_bruto) {
    vector<char> quadro;

    while (quadro_bruto.size() > 0) {
        vector<char> cabecalho;
        string byte = "";

        // Separa o cabeçalho
        for (int i = 0; i < 8; i++) {
            byte += quadro_bruto[0];
            quadro_bruto.erase(quadro_bruto.begin());
        }

        // Transforma o cabeçalho em decimal e <int>
        int tamanho_do_quadro = stoi(byte, nullptr, 2);
        int caractere = static_cast<char>(tamanho_do_quadro) - '0';

        // Separa o quadro de acordo com o cabeçalho
        for (int i = 0; i < caractere; i++) {
            quadro.push_back(quadro_bruto[0]);
            quadro_bruto.erase(quadro_bruto.begin());
        }
    }

    return quadro;
}

// Função para desfazer o enquadramento por inserção de bytes
vector<char> camada_enlace_dados_receptora_enquadramento_insercao_de_bytes (vector<char> quadro_bruto) {
    vector<char> quadro_com_cabecalho;
    // Flag estabelecida
    string flag = "11110000";
    string esc = "00011011";

    while (quadro_bruto.size() > 0) {
        string verificador_de_flag = "";
        // Separa o quadro em bytes
        for (int x = 0; x < 8; x++) {
            verificador_de_flag += quadro_bruto[0];
            quadro_bruto.erase(quadro_bruto.begin());
        }
            
        // Verifica se o byte é uma flag ou um ESC
        if (verificador_de_flag == flag) {
            continue;
        } else if (verificador_de_flag == esc) {
            // Se tiver um ESC, a função considera o próximo byte como pertencente ao quadro final
            for (int i = 0; i < 8; i++) {
                quadro_com_cabecalho.push_back(quadro_bruto[0]);
                quadro_bruto.erase(quadro_bruto.begin());
                continue;
            }
        }
            
        // Adiciona o byte no quadro final
        for (char bit : verificador_de_flag) {
            quadro_com_cabecalho.push_back(bit);    
        }
    }
    
    return quadro_com_cabecalho;
}

vector<char> camada_enlace_dados_receptora_controle_de_erro (vector<char> quadro, int tipo_de_controle_de_erro) {
    vector<char> quadro_controle_feito;

    switch (tipo_de_controle_de_erro) {
        case 0: //bit de paridade par
            quadro_controle_feito = camada_enlace_dados_receptora_controle_de_erro_bit_paridade_par(quadro);
            break;
        case 1: //CRC
            quadro_controle_feito = camada_enlace_dados_receptora_controle_de_erro_crc(quadro);
            break;
    }

    return quadro_controle_feito;
}

// Função para desfazer o controle por bit de paridade
vector<char> camada_enlace_dados_receptora_controle_de_erro_bit_paridade_par (vector<char> quadro) {
    int valor_bit_paridade_obtido = 0;
    int bit_paridade = 0;

    // Destaca o bit final do restante do quadro
    bit_paridade = quadro.back() - '0';
    quadro.pop_back();

    // Pega cada bit do quadro e faz o cálculo de XOR com o bit anterior
    for (char bit : quadro) {
        int num = bit - '0';
        valor_bit_paridade_obtido = num ^ valor_bit_paridade_obtido;
    }
    
    // Compara o bit do quadro com o bit obtido
    if (valor_bit_paridade_obtido == bit_paridade) {
        cout << "Deu certo!" << endl;
    } else {
        cout << "ERRO DETECTADO!" << endl;
    }

    return quadro;
}

// Função para desfazer o controle por crc
vector<char> camada_enlace_dados_receptora_controle_de_erro_crc (vector<char> quadro) {
    // Define o polinomio gerador
    vector<char> polinomio_gerador = {'1', '0', '0', '0', '1', '0', '0', '1', '0', '1', '1', '1', '1', '1', '0', '1'};
    vector<char> resto_da_divisao;
    // Faz a divisão de bits e recebe o resto da divisão
    resto_da_divisao = divisao_de_bit(quadro, polinomio_gerador);

    // Verifica se o resto está correto ou não
    char resultado = '0';
    for (char i : resto_da_divisao) {
        // Se tiver um bit = 1, o quadro está incorreto
        if (i == '1') {
            resultado = i;
            break;
        }
    }

    if (resultado == '0') {
        cout << "Deu certo!" << endl;
    } else {
        cout << "ERRO DETECTADO!" << endl;
    }

    // Retira o resto da divisão do polinomio para retorná-lo
    for (int i = 0; i < polinomio_gerador.size() - 1; i++) {
        quadro.pop_back();
    }
    return quadro;
}
