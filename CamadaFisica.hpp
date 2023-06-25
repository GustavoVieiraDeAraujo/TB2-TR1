#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>

using namespace std;

#define limpar system("clear");

// Suporte

string converter_mensagem_em_bit(string mensagem);

// Construir Sinal

void construir_sinal(vector<char> quadro);
void construir_sinal_binario(vector<char> quadro);
void construir_sinal_bipolar(vector<char> quadro);
void construir_sinal_manchester(vector<char> quadro);

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