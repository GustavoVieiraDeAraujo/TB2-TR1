#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <bitset>
#include<math.h>
#include <iostream>

using namespace std;

vector<char> converter_decimal_em_byte (int numero);
vector<char> camada_enlace_dados_transmissora (vector<char> quadro);
vector<char> camada_enlace_dados_transmissora_enquadramento (vector<char> quadro);
vector<char> camada_enlace_dados_transmissora_enquadramento_contagem_de_caracteres (vector<char> quadro);
vector<char> camada_enlace_dados_transmissora_enquadramento_insercao_de_bytes (vector<char> quadro);
void camada_enlace_dados_transmissora_controle_de_erro (vector<char> quadro);
