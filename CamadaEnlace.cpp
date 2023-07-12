#include "./CamadaEnlace.hpp"
#include "./CamadaFisica.hpp"

vector<char> converter_decimal_em_byte (int numero) {
    const int n = 8;
    vector<char> cabecalho;
 
    string binario = bitset<n>(numero).to_string();

    for (char byte : binario) {
        cabecalho.push_back(byte);
    }

    return cabecalho;
}

int converter_byte_em_decimal (vector<char> cabecalho) {
    int index = 7;
    int numero;

    for (char byte : cabecalho) {
        if ( index < 0) {
            break;
        }

        int num = byte - '0';
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

    // camada_enlace_dados_transmissora_controle_de_erro(quadro);
    return quadro_com_enquadramento;
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
        // //Teste
        // cout << quadro_bruto.front() << endl;
        // cout << "TESTE" << endl;
        // for (int i = 0; i < quadro_bruto.size(); i++) {
        //     cout << quadro_bruto[i];
        // }
        // cout << endl;


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

    cout << quadro_com_cabecalho.size() << endl;
    return quadro_com_cabecalho;
}

// void camada_enlace_dados_transmissora_controle_de_erro (vector<char> quadro) {

// }

vector<char> camada_enlace_dados_receptora (vector<char> quadro_com_enquadramento) {
    vector<char> quadro;
    quadro = camada_enlace_dados_receptora_enquadramento(quadro_com_enquadramento);

    // camada_enlace_dados_receptora_controle_de_erro(quadro);
    return quadro;
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
    vector<char> quadro_com_cabecalho;

    while (quadro_bruto.size() > 0) {
        vector<char> cabecalho;
        int tamanho_do_quadro;

        for (int i = 0; i < tamanho_do_byte; i++) {
            cabecalho.push_back(quadro_bruto[0]);
            quadro_bruto.erase(quadro_bruto.begin());
        }

        tamanho_do_quadro = converter_byte_em_decimal(cabecalho);

        // for ()



        // vector<char> cabecalho = converter_decimal_em_byte(tamanho_do_quadro);

        // for (char bit : cabecalho) {
        //     quadro_com_cabecalho.push_back(bit);
        // }

        // for (int i = 0; i < tamanho_do_quadro; i++) {
        //     quadro_com_cabecalho.push_back(quadro_bruto[0]);
        //     quadro_bruto.erase(quadro_bruto.begin());
        // }
    }

    return quadro_com_cabecalho;
}