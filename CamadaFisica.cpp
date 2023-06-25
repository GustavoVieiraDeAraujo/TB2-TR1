#include "./CamadaFisica.hpp"

// Transmissão

void aplicacao_transmissora(void) {
    string mensagem;
    cout << "Digite uma mensagem:" << endl;
    cin >> mensagem;

    camada_de_aplicacao_transmissora(mensagem);
}

void camada_de_aplicacao_transmissora(string mensagem) {
    vector<string> quadro;
    camada_fisica_transmissora(quadro);
}

void camada_fisica_transmissora(vector<string> quadro) {
    int tipo_de_codificacao = 0;
    vector<string> fluxo_bruto_de_bits;

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

vector<string> camada_fisica_transmissora_codificacao_binaria(vector<string> fluxo_bruto_de_bits) {
    vector<string> fluxo_bruto_de_bits_codificado;
    return fluxo_bruto_de_bits_codificado;
}

vector<string> camada_fisica_transmissora_codificacao_manchester(vector<string> fluxo_bruto_de_bits) {
    vector<string> fluxo_bruto_de_bits_codificado;
    return fluxo_bruto_de_bits_codificado;
}

vector<string> camada_fisica_transmissora_codificacao_bipolar(vector<string> fluxo_bruto_de_bits) {
    vector<string> fluxo_bruto_de_bits_codificado;
    return fluxo_bruto_de_bits_codificado;
}

// Comunicação

void meio_de_comunicacao(vector<string> fluxo_bruto_de_bits) {
    vector<string> fluxo_bruto_de_bits_ponto_a, fluxo_bruto_de_bits_ponto_b;
    fluxo_bruto_de_bits_ponto_a = fluxo_bruto_de_bits;

    for (string bit : fluxo_bruto_de_bits_ponto_a){
        fluxo_bruto_de_bits_ponto_b.push_back(bit);
    }

    camada_fisica_receptora(fluxo_bruto_de_bits_ponto_b);
}

// Recepção

void camada_fisica_receptora(vector<string> quadro) {
    int tipo_de_decodificacao = 0;
    vector<string> fluxo_bruto_de_bits;

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

vector<string> camada_fisica_receptora_decodificacao_binaria(vector<string> quadro) {
    vector<string> fluxo_bruto_de_bits_decodificado;
    return fluxo_bruto_de_bits_decodificado;
}

vector<string> camada_fisica_receptora_decodificacao_manchester(vector<string> quadro) {
    vector<string> fluxo_bruto_de_bits_decodificado;
    return fluxo_bruto_de_bits_decodificado;
}

vector<string> camada_fisica_receptora_decodificacao_bipolar(vector<string> quadro) {
    vector<string> fluxo_bruto_de_bits_decodificado;
    return fluxo_bruto_de_bits_decodificado;
}

void camada_de_aplicacao_receptora(vector<string> quadro) {
    aplicacao_receptora("inicio");
}

void aplicacao_receptora(string mensagem) {
    cout << "A mensagem recebida foi: " << mensagem << endl;
}
