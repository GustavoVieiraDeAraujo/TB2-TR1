#include "./CamadaFisica.hpp"
#include "./MontagemGrafico.hpp"

#include <string>

// Suporte

string converter_mensagem_em_bit(string mensagem) {
    string quadro;
    for (char caracter : mensagem) {
        int caracter_em_decimal = static_cast<unsigned char>(caracter);
        for (int i = 7; i >= 0; --i) {
            quadro += ((caracter_em_decimal & (1 << i)) ? '1' : '0');
        }
    }
    return quadro;
}


// Transmissão

// Função para receber a mensagem da simulação, enviada pelo usuário via terminal
string aplicacao_transmissora(void) {
    string mensagem;
    cout << "Digite uma mensagem:" << endl;
    getline(cin, mensagem); // Mensagem recebida
    cout << "A mensagem e: ";
    cout << mensagem << endl;

    return mensagem;
}

// Função cujo o objetivo é transformar a mensagem :string em um quadro :vector<char>, convertendo os caracteres em bytes, seguindo o padrão ASCII e concatenando os bytes no quadro.
vector<char> camada_de_aplicacao_transmissora(string mensagem) {
    vector<char> quadro;

    for (char bit : converter_mensagem_em_bit(mensagem)) {
        quadro.push_back(bit);
    }

    return quadro;
}


vector<char> camada_fisica_transmissora(vector<char> quadro, int tipo_de_codificacao) {
    vector<char> fluxo_bruto_de_bits;

    switch (tipo_de_codificacao) {
    case 0:
        fluxo_bruto_de_bits = camada_fisica_transmissora_codificacao_binaria(quadro);
        break;
    case 1:
        fluxo_bruto_de_bits = camada_fisica_transmissora_codificacao_manchester(quadro);
        break;
    case 2:
        fluxo_bruto_de_bits = camada_fisica_transmissora_codificacao_bipolar(quadro);
        break;
    }

    return fluxo_bruto_de_bits;
}


vector<char> camada_fisica_transmissora_codificacao_binaria(vector<char> fluxo_bruto_de_bits) {
    vector<char> fluxo_bruto_de_bits_codificado;

    for (char bit_fluxo : fluxo_bruto_de_bits) {
        fluxo_bruto_de_bits_codificado.push_back(bit_fluxo);
    }

    return fluxo_bruto_de_bits_codificado;
}


vector<char> camada_fisica_transmissora_codificacao_manchester(vector<char> fluxo_bruto_de_bits) {
    vector<char> fluxo_bruto_de_bits_codificado;

    for (char bit : fluxo_bruto_de_bits) {
        if (bit == '0') {
            fluxo_bruto_de_bits_codificado.push_back('0');
            fluxo_bruto_de_bits_codificado.push_back('1');
        }
        else {
            fluxo_bruto_de_bits_codificado.push_back('1');
            fluxo_bruto_de_bits_codificado.push_back('0');
        }
    }

    return fluxo_bruto_de_bits_codificado;
}


vector<char> camada_fisica_transmissora_codificacao_bipolar(vector<char> fluxo_bruto_de_bits) {
    string qual_foi_ultimo_bit = "-1";
    string construir_quadro_codificado;

    for (char bit : fluxo_bruto_de_bits) {
        if (bit == '0') {
            construir_quadro_codificado += "0";
        }
        else {
            construir_quadro_codificado += ((qual_foi_ultimo_bit == "1") ? "-1" : "1");
            qual_foi_ultimo_bit = ((qual_foi_ultimo_bit == "1") ? "-1" : "1");
        }
    }

    vector<char> fluxo_bruto_de_bits_codificado(construir_quadro_codificado.begin(), construir_quadro_codificado.end());

    return fluxo_bruto_de_bits_codificado;
}


// Comunicação

vector<char> meio_de_comunicacao(vector<char> fluxo_bruto_de_bits) {
    vector<char> fluxo_bruto_de_bits_ponto_a, fluxo_bruto_de_bits_ponto_b;
    fluxo_bruto_de_bits_ponto_a = fluxo_bruto_de_bits;

    for (char bit : fluxo_bruto_de_bits_ponto_a) {
        fluxo_bruto_de_bits_ponto_b.push_back(bit);
    }
    
    return fluxo_bruto_de_bits_ponto_b;
}


// Recepção

vector<char> camada_fisica_receptora(vector<char> quadro, int tipo_de_decodificacao) {
    vector<char> fluxo_bruto_de_bits;

    switch (tipo_de_decodificacao) {
    case 0:
        fluxo_bruto_de_bits = camada_fisica_receptora_decodificacao_binaria(quadro);
        break;
    case 1:
        fluxo_bruto_de_bits = camada_fisica_receptora_decodificacao_manchester(quadro);
        break;
    case 2:
        fluxo_bruto_de_bits = camada_fisica_receptora_decodificacao_bipolar(quadro);
        break;
    }

    return fluxo_bruto_de_bits;
}


vector<char> camada_fisica_receptora_decodificacao_binaria(vector<char> quadro) {
    string construir_quadro_decodificado;

    for (int i = 0; i < quadro.size(); i++) {
        construir_quadro_decodificado += quadro[i];
    }

    vector<char> fluxo_bruto_de_bits_decodificado(construir_quadro_decodificado.begin(), construir_quadro_decodificado.end());
    return fluxo_bruto_de_bits_decodificado;
}


vector<char> camada_fisica_receptora_decodificacao_manchester(vector<char> quadro) {
    string construir_quadro_decodificado;

    for (int i = 0; i < quadro.size(); i += 2) {
        string clock;
        for (int j = i; (j < (i + 2)); j++) {
            clock += quadro[j];
        }
        if (clock == "01") {
            construir_quadro_decodificado += "0";
        } else {
            construir_quadro_decodificado += "1";
        }
    }

    vector<char> fluxo_bruto_de_bits_decodificado(construir_quadro_decodificado.begin(), construir_quadro_decodificado.end());
    return fluxo_bruto_de_bits_decodificado;
}


vector<char> camada_fisica_receptora_decodificacao_bipolar(vector<char> quadro) {
    string construir_quadro_decodificado;

    for (int i = 0; i < quadro.size(); i++) {
        if (quadro[i] == '0') {
            construir_quadro_decodificado += '0';

        } else if (quadro[i] == '-') {
            construir_quadro_decodificado += '1';
            i += 1;

        } else {
            construir_quadro_decodificado += '1';
        }
    }

    vector<char> fluxo_bruto_de_bits_decodificado(construir_quadro_decodificado.begin(), construir_quadro_decodificado.end());

   
    return fluxo_bruto_de_bits_decodificado;
}


string camada_de_aplicacao_receptora(vector<char> quadro) {
    string mensagem;

    for (int i = 0; i < quadro.size(); i += 8) {
        string byte;
        for (int j = i; (j < (i + 8)); j++) {
            byte += quadro[j];
        }

        int valor = stoi(byte, nullptr, 2);
        char caractere = static_cast<char>(valor);
        mensagem += caractere;
    }

    return mensagem;
}


void aplicacao_receptora(string mensagem) {
    cout << "A mensagem recebida foi: " << mensagem << endl;
}
