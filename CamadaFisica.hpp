#include <string>
#include <vector>
#include <iostream>

using namespace std;

// Transmissão

void aplicacao_transmissora();
void camada_de_aplicacao_transmissora(string mensagem);
void camada_fisica_transmissora(vector<char> quadro);
vector<char> camada_fisica_transmissora_codificacao_bipolar(vector<char> quadro);
vector<char> camada_fisica_transmissora_codificacao_binaria(vector<char> quadro);
vector<char> camada_fisica_transmissora_codificacao_manchester(vector<char> quadro);

// Comunicação

void meio_de_comunicacao(vector<char> fluxo_bruto_de_bits);

// Recepçao

void camada_fisica_receptora(vector<char> quadro);
void camada_de_aplicacao_receptora(vector<char> quadro);
vector<char> camada_fisica_receptora_decodificacao_bipolar(vector<char> quadro);
vector<char> camada_fisica_receptora_decodificacao_binaria(vector<char> quadro);
vector<char> camada_fisica_receptora_decodificacao_manchester(vector<char> quadro);
void aplicacao_receptora(string mensagem);