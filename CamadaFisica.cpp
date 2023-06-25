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

// Construir Sinal

void construir_sinal_binario(vector<char> quadro){
    int largura_desenho_em_espaco;
    int maxima_largura_desenho_em_espaco = 35;
    int numero_de_espacos_para_desenhar_bit = 4;

    int diferenca = ((quadro.size()*numero_de_espacos_para_desenhar_bit)-maxima_largura_desenho_em_espaco);
    if ( diferenca > 0){
        largura_desenho_em_espaco = maxima_largura_desenho_em_espaco;
    } else {
        largura_desenho_em_espaco = quadro.size();
    }

    string segunda_linha, terceira_linha, quarta_linha, quinta_linha;
    segunda_linha = terceira_linha = quarta_linha = quinta_linha = "|";
    
    char ultimo_bit_desenhado='i';

    for (int i = 0; i < largura_desenho_em_espaco; i++) {
        if ( quadro[i] == '1' && ultimo_bit_desenhado == 'i'){
            segunda_linha += "***";
            terceira_linha += "   ";
            quarta_linha += "   ";
            quinta_linha += "   ";
            ultimo_bit_desenhado = '1';
        } else if ( quadro[i] == '0' && ultimo_bit_desenhado == 'i'){
            segunda_linha += "   ";
            terceira_linha += "   ";
            quarta_linha += "   ";
            quinta_linha += "***";
            ultimo_bit_desenhado = '0';
        } else if (quadro[i] == '1' && quadro[i] != ultimo_bit_desenhado){
            segunda_linha += "****";
            terceira_linha += "*   ";
            quarta_linha += "*   ";
            quinta_linha += "*   ";
            ultimo_bit_desenhado = '1';
        } else if (quadro[i] == '1' && quadro[i] == ultimo_bit_desenhado){
            segunda_linha += "***";
            terceira_linha += "   ";
            quarta_linha += "   ";
            quinta_linha += "   ";
            ultimo_bit_desenhado = '1';
        } else if (quadro[i] == '0' && quadro[i] != ultimo_bit_desenhado){
            segunda_linha += "*   ";
            terceira_linha += "*   ";
            quarta_linha += "*   ";
            quinta_linha += "****";
            ultimo_bit_desenhado = '0';
        } else if (quadro[i] == '0' && quadro[i] == ultimo_bit_desenhado){
            segunda_linha += "   ";
            terceira_linha += "   ";
            quarta_linha += "   ";
            quinta_linha += "***";
            ultimo_bit_desenhado = '0';
        }
    }

    string primeira_linha, sexta_linha;
    primeira_linha = sexta_linha = "|";
    
    for(int i = 0; i < (segunda_linha.length()-1); i++){
        primeira_linha += "-";
        sexta_linha += "-";
    }
    primeira_linha += "|";
    sexta_linha += "|";

    segunda_linha += "|";
    terceira_linha += "|";
    quarta_linha += "|";
    quinta_linha += "|";

    cout << primeira_linha << endl;
    cout << segunda_linha << endl;
    cout << terceira_linha << endl;
    cout << quarta_linha << endl;
    cout << quinta_linha << endl;
    cout << sexta_linha << endl;
}

void construir_sinal_manchester(vector<char> quadro){
    int tamanho_linha = ((quadro.size()*5)/2);

    string primeira_linha="|";
    string sexta_linha="|";
    for(int i = 0; i < (tamanho_linha);i++){
        primeira_linha+='-';
        sexta_linha+='-';
    }
    primeira_linha+="|";
    sexta_linha+="|";

    string segunda_linha="|";
    string terceira_linha="|";
    string quarta_linha="|";
    string quinta_linha="|";
    for (int i = 0; i < quadro.size(); i += 2) {
        string bit_codificado;
        for (int j = i; (j < (i+2)); j++) {
            bit_codificado += quadro[j];
        }
        terceira_linha+="  *  ";
        quarta_linha+= "  *  ";
        if (bit_codificado == "01"){
            segunda_linha+="  ***";
            quinta_linha+="***  ";
        } else {
            segunda_linha+="***  ";
            quinta_linha+="  ***";
        }
    }
    segunda_linha+="|";
    terceira_linha+="|";
    quarta_linha+="|";
    quinta_linha+="|";

    cout << primeira_linha << endl;
    cout << segunda_linha << endl;
    cout << terceira_linha << endl;
    cout << quarta_linha << endl;
    cout << quinta_linha << endl;
    cout << sexta_linha << endl;

}

void construir_sinal_bipolar(vector<char> quadro){
    cout << "temp";
}

void construir_sinal(vector<char> quadro){
    int tipo_de_codificacao = 0;

    switch (tipo_de_codificacao) {
        case 0:
            construir_sinal_binario(quadro);
            break;
        case 1:
            construir_sinal_manchester(quadro);
            break;
        case 2:
            construir_sinal_bipolar(quadro);
            break;
    }
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

    limpar;
    cout << "O seguinte sinal esta sendo enviado:" << endl;
    construir_sinal(fluxo_bruto_de_bits_ponto_b);
    this_thread::sleep_for(chrono::seconds(5));
    limpar;
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
    string construir_quadro_decodificado;
    
    for (int i = 0; i < quadro.size(); i += 8) {
        string byte;
        for (int j = i; (j < (i+8)); j++) {
            byte += quadro[j];
        }
        if (byte == "00110000"){
            construir_quadro_decodificado+="0";
        } else {
            construir_quadro_decodificado+="1";
        }
    }

    vector<char> fluxo_bruto_de_bits_decodificado(construir_quadro_decodificado.begin(), construir_quadro_decodificado.end());
    return fluxo_bruto_de_bits_decodificado;
}

vector<char> camada_fisica_receptora_decodificacao_manchester(vector<char> quadro) {
    string construir_quadro_decodificado;
    
    for (int i = 0; i < quadro.size(); i += 2) {
        string clock;
        for (int j = i; (j < (i+2)); j++) {
            clock += quadro[j];
        }
        if (clock == "01"){
            construir_quadro_decodificado+="0";
        } else {
            construir_quadro_decodificado+="1";
        }
    }

    vector<char> fluxo_bruto_de_bits_decodificado(construir_quadro_decodificado.begin(), construir_quadro_decodificado.end());
    return fluxo_bruto_de_bits_decodificado;
}

vector<char> camada_fisica_receptora_decodificacao_bipolar(vector<char> quadro) {
    string construir_quadro_decodificado;

    for(int i=0; i < quadro.size(); i++){
        if (quadro[i] == '0'){
            construir_quadro_decodificado+='0';
        } else if ( quadro[i] == '-'){
            construir_quadro_decodificado+='1';
            i+=1;
        } else {
            construir_quadro_decodificado+='1';
        }
    }

    vector<char> fluxo_bruto_de_bits_decodificado(construir_quadro_decodificado.begin(), construir_quadro_decodificado.end());
    return fluxo_bruto_de_bits_decodificado;
}

void camada_de_aplicacao_receptora(vector<char> quadro) {
    string mensagem;

    for (int i = 0; i < quadro.size(); i += 8) {
        string byte;
        for (int j = i; (j < (i+8)); j++) {
            byte += quadro[j];
        }
        int valor = stoi(byte, nullptr, 2);
        char caractere = static_cast<char>(valor);
        mensagem += caractere;
    }

    aplicacao_receptora(mensagem);
}

void aplicacao_receptora(string mensagem) {
    cout << "A mensagem recebida foi: " << mensagem << endl;
}
