#include "./CamadaFisica.hpp"

// Suporte

string converter_mensagem_em_bit(string mensagem){
    string quadro;
    for (char caracter : mensagem) {
        int caracter_em_decimal = static_cast<unsigned char>(caracter);
        for (int i = 7; i >= 0; --i) {
            quadro+=((caracter_em_decimal & (1 << i)) ? '1' : '0');
        }
    }
    return quadro;
}


// Transmissão

void aplicacao_transmissora(void) {
    string mensagem;
    cout << "Digite uma mensagem:" << endl;
    cin >> mensagem;

    camada_de_aplicacao_transmissora(mensagem);
}

void camada_de_aplicacao_transmissora(string mensagem) {
    vector<char> quadro;

    for (char bit : converter_mensagem_em_bit(mensagem)){
        quadro.push_back(bit);
    }

    camada_fisica_transmissora(quadro);
}

void camada_fisica_transmissora(vector<char> quadro) {
    int tipo_de_codificacao = 0;
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

    meio_de_comunicacao(fluxo_bruto_de_bits);
}

vector<char> camada_fisica_transmissora_codificacao_binaria(vector<char> fluxo_bruto_de_bits) {
    vector<char> fluxo_bruto_de_bits_codificado;

    for(char bit_fluxo : fluxo_bruto_de_bits){
        string bit_fluxo_string(1, bit_fluxo);
        for(char bit_fluxo_codificado : converter_mensagem_em_bit(bit_fluxo_string)){
            fluxo_bruto_de_bits_codificado.push_back(bit_fluxo_codificado);
        }
    }

    return fluxo_bruto_de_bits_codificado;
}

vector<char> camada_fisica_transmissora_codificacao_manchester(vector<char> fluxo_bruto_de_bits) {
    vector<char> fluxo_bruto_de_bits_codificado;

    for (char bit : fluxo_bruto_de_bits) {
        if (bit == '0') {
            fluxo_bruto_de_bits_codificado.push_back('0');
            fluxo_bruto_de_bits_codificado.push_back('1');
        } else {
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
            construir_quadro_codificado+="0";
        } else {
            construir_quadro_codificado += ((qual_foi_ultimo_bit == "1") ? "-1" : "1");
            qual_foi_ultimo_bit = ((qual_foi_ultimo_bit == "1") ? "-1" : "1");
        }
    }

    vector<char> fluxo_bruto_de_bits_codificado(construir_quadro_codificado.begin(), construir_quadro_codificado.end());
    
    return fluxo_bruto_de_bits_codificado;
}

// Comunicação

void meio_de_comunicacao(vector<char> fluxo_bruto_de_bits) {
    vector<char> fluxo_bruto_de_bits_ponto_a, fluxo_bruto_de_bits_ponto_b;
    fluxo_bruto_de_bits_ponto_a = fluxo_bruto_de_bits;

    for (char bit : fluxo_bruto_de_bits_ponto_a){
        fluxo_bruto_de_bits_ponto_b.push_back(bit);
    }

    camada_fisica_receptora(fluxo_bruto_de_bits_ponto_b);
}

// Recepção

void camada_fisica_receptora(vector<char> quadro) {
    int tipo_de_decodificacao = 0;
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

    camada_de_aplicacao_receptora(fluxo_bruto_de_bits);
}

vector<char> camada_fisica_receptora_decodificacao_binaria(vector<char> quadro) {
    vector<char> fluxo_bruto_de_bits_decodificado;
    return fluxo_bruto_de_bits_decodificado;
}

vector<char> camada_fisica_receptora_decodificacao_manchester(vector<char> quadro) {
    vector<char> fluxo_bruto_de_bits_decodificado;
    return fluxo_bruto_de_bits_decodificado;
}

vector<char> camada_fisica_receptora_decodificacao_bipolar(vector<char> quadro) {
    vector<char> fluxo_bruto_de_bits_decodificado;
    return fluxo_bruto_de_bits_decodificado;
}

void camada_de_aplicacao_receptora(vector<char> quadro) {
    aplicacao_receptora("inicio");
}

void aplicacao_receptora(string mensagem) {
    cout << "A mensagem recebida foi: " << mensagem << endl;
}
