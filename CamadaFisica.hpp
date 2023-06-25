#include <string>
#include <vector>
#include <iostream>

using namespace std;

// Transmissão

void aplicacao_transmissora();
void camada_de_aplicacao_transmissora(string mensagem);
void camada_fisica_transmissora(vector<string> quadro);
vector<string> camada_fisica_transmissora_codificacao_bipolar(vector<string> quadro);
vector<string> camada_fisica_transmissora_codificacao_binaria(vector<string> quadro);
vector<string> camada_fisica_transmissora_codificacao_manchester(vector<string> quadro);

// Comunicação

void meio_de_comunicacao(vector<string> fluxo_bruto_de_bits);

// Recepçao

void camada_fisica_receptora(vector<string> quadro);
void camada_de_aplicacao_receptora(vector<string> quadro);
vector<string> camada_fisica_receptora_decodificacao_bipolar(vector<string> quadro);
vector<string> camada_fisica_receptora_decodificacao_binaria(vector<string> quadro);
vector<string> camada_fisica_receptora_decodificacao_manchester(vector<string> quadro);
void aplicacao_receptora(string mensagem);