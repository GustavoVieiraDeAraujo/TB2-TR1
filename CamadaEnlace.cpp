#include "./CamadaEnlace.hpp"
#include "./CamadaFisica.hpp"

vector<char> converter_decimal_em_byte (int numero) {
    const int n = 8;
    vector<char> cabecalho;
 
    string binario = bitset<n>(numero).to_string();

    for (char bit : binario) {
        cabecalho.push_back(bit);
    }

    return cabecalho;
}

int converter_byte_em_decimal (vector<char> cabecalho) {
    int index = 7;
    int numero = 0;

    for (char bit : cabecalho) {
        if ( index < 0) {
            break;
        }

        int num = bit - '0';
        if (num == 1) {
            numero += pow(2, index);
        }

        index--;
    }

    return numero;
}

vector<char> camada_enlace_dados_transmissora (vector<char> quadro) {
    vector<char> quadro_com_enquadramento;
    quadro_com_enquadramento = camada_enlace_dados_transmissora_enquadramento(quadro);

    vector<char> quadro_com_controle_de_erro;
    quadro_com_controle_de_erro = camada_enlace_dados_transmissora_controle_de_erro(quadro_com_enquadramento);

    return quadro_com_controle_de_erro;
}

vector<char> camada_enlace_dados_transmissora_enquadramento (vector<char> quadro) {
    int tipo_de_enquadramento = 1;

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

vector<char> camada_enlace_dados_transmissora_enquadramento_contagem_de_caracteres (vector<char> quadro_bruto) {
    int tamanho_do_quadro = 8;
    vector<char> quadro_com_cabecalho;

    while (quadro_bruto.size() > 0) {
        vector<char> cabecalho = converter_decimal_em_byte(tamanho_do_quadro);

        for (char bit : cabecalho) {
            quadro_com_cabecalho.push_back(bit);
        }

        for (int i = 0; i < tamanho_do_quadro; i++) {
            quadro_com_cabecalho.push_back(quadro_bruto[0]);
            quadro_bruto.erase(quadro_bruto.begin());
        }
    }

    return quadro_com_cabecalho;
}

vector<char> camada_enlace_dados_transmissora_enquadramento_insercao_de_bytes (vector<char> quadro_bruto) {
    int tamanho_do_quadro = 8;
    vector<char> quadro_com_cabecalho;
    string flag = "11111111";
    string esc = "00011011";

    while (quadro_bruto.size() > 0) {
        for (char i : flag) {
            quadro_com_cabecalho.push_back(i);
        }

        for (int i = 0; i < tamanho_do_quadro; i++) {
            quadro_com_cabecalho.push_back(quadro_bruto[0]);
            quadro_bruto.erase(quadro_bruto.begin());
        }

        for (char i : flag) {
            quadro_com_cabecalho.push_back(i);
        }
    }

    return quadro_com_cabecalho;
}

vector<char> camada_enlace_dados_transmissora_controle_de_erro (vector<char> quadro) {
    int tipo_de_controle_de_erro = 0;
    vector<char> quadro_com_controle_de_erro;

    switch (tipo_de_controle_de_erro) {
        case 0: //bit de paridade par
            quadro_com_controle_de_erro = camada_enlace_dados_transmissora_controle_de_erro_bit_paridade_par(quadro);
            break;
        case 1: //CRC
            break;
    }

    return quadro_com_controle_de_erro;
}

vector<char> camada_enlace_dados_transmissora_controle_de_erro_bit_paridade_par (vector<char> quadro) {
    int valor_bit_paridade = 0;

    for (char bit : quadro) {
        int num = bit - '0';
        valor_bit_paridade = num ^ valor_bit_paridade;
    }

    string bit_paridade = to_string(valor_bit_paridade);
    for (char bit_p : bit_paridade) {
        quadro.push_back(bit_p);
    }

    return quadro;
}

vector<char> camada_enlace_dados_transmissora_controle_de_erro_crc (vector<char> quadro) {
    string polinomio_gerador = "0010";

    return quadro;
}




vector<char> camada_enlace_dados_receptora (vector<char> quadro_recebido) {
    vector<char> quadro_deteccao_feita;
    quadro_deteccao_feita = camada_enlace_dados_receptora_controle_de_erro(quadro_recebido);

    vector<char> quadro_sem_enquadramento;
    quadro_sem_enquadramento = camada_enlace_dados_receptora_enquadramento(quadro_deteccao_feita);

    return quadro_sem_enquadramento;
}

vector<char> camada_enlace_dados_receptora_enquadramento (vector<char> quadro_encapsulado) {
    int tipo_de_enquadramento = 1;

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

vector<char> camada_enlace_dados_receptora_enquadramento_contagem_de_caracteres (vector<char> quadro_bruto) {
    int tamanho_do_byte = 8;
    vector<char> quadro;

    while (quadro_bruto.size() > 0) {
        vector<char> cabecalho;
        int tamanho_do_quadro;

        for (int i = 0; i < tamanho_do_byte; i++) {
            cabecalho.push_back(quadro_bruto[0]);
            quadro_bruto.erase(quadro_bruto.begin());
        }

        tamanho_do_quadro = converter_byte_em_decimal(cabecalho);

        for (int i = 0; i < tamanho_do_quadro; i++) {
            quadro.push_back(quadro_bruto[0]);
            quadro_bruto.erase(quadro_bruto.begin());
        }
    }

    return quadro;
}

vector<char> camada_enlace_dados_receptora_enquadramento_insercao_de_bytes (vector<char> quadro_bruto) {
    int tamanho_do_quadro = 8;
    vector<char> quadro;
    string flag = "11111111";
    string esc = "00011011";

    while (quadro_bruto.size() > 0) {
        for (char i : flag) {
            quadro_bruto.erase(quadro_bruto.begin());
        }

        for (int i = 0; i < tamanho_do_quadro; i++) {
            quadro.push_back(quadro_bruto[0]);
            quadro_bruto.erase(quadro_bruto.begin());
        }

        for (char i : flag) {
            quadro_bruto.erase(quadro_bruto.begin());
        }
    }

    return quadro;
}

vector<char> camada_enlace_dados_receptora_controle_de_erro (vector<char> quadro) {
    int tipo_de_controle_de_erro = 0;
    vector<char> quadro_controle_feito;

    switch (tipo_de_controle_de_erro) {
        case 0: //bit de paridade par
            quadro_controle_feito = camada_enlace_dados_receptora_controle_de_erro_bit_paridade_par(quadro);
            break;
        case 1: //CRC
            break;
    }

    return quadro_controle_feito;
}

vector<char> camada_enlace_dados_receptora_controle_de_erro_bit_paridade_par (vector<char> quadro) {
    int valor_bit_paridade_obtido = 0;
    int bit_paridade = 0;

    bit_paridade = quadro.back() - '0';
    quadro.pop_back();

    for (char bit : quadro) {
        int num = bit - '0';
        valor_bit_paridade_obtido = num ^ valor_bit_paridade_obtido;
    }
    
    if (valor_bit_paridade_obtido == bit_paridade) {
        cout << "Deu certo!" << endl;
    } else {
        cout << "ERRO DETECTADO!" << endl;
    }

    return quadro;
}

// vector<char> camada_enlace_dados_receptora_controle_de_erro_crc (vector<char> quadro) {}