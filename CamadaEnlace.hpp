#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <bitset>
#include<math.h>
#include <iostream>

using namespace std;

vector<char> converter_decimal_em_byte (int numero, int tamanho);
int converter_byte_em_decimal (vector<char> cabecalho);

vector<char> camada_enlace_dados_transmissora (vector<char> quadro, int enquadramento, int controle);
vector<char> camada_enlace_dados_transmissora_enquadramento (vector<char> quadro, int tipo_de_enquadramento);
vector<char> camada_enlace_dados_transmissora_enquadramento_contagem_de_caracteres (vector<char> quadro);
vector<char> camada_enlace_dados_transmissora_enquadramento_insercao_de_bytes (vector<char> quadro);

vector<char> camada_enlace_dados_transmissora_controle_de_erro (vector<char> quadro, int tipo_de_controle_de_erro);
vector<char> camada_enlace_dados_transmissora_controle_de_erro_bit_paridade_par (vector<char> quadro);
vector<char> camada_enlace_dados_transmissora_controle_de_erro_crc (vector<char> quadro);


vector<char> camada_enlace_dados_receptora (vector<char> quadro_recebido, int enquadramento, int controle);
vector<char> camada_enlace_dados_receptora_enquadramento (vector<char> quadro_encapsulado, int tipo_de_enquadramento);
vector<char> camada_enlace_dados_receptora_enquadramento_contagem_de_caracteres (vector<char> quadro_bruto);
vector<char> camada_enlace_dados_receptora_enquadramento_insercao_de_bytes (vector<char> quadro_bruto);

vector<char> camada_enlace_dados_receptora_controle_de_erro (vector<char> quadro, int tipo_de_controle_de_erro);
vector<char> camada_enlace_dados_receptora_controle_de_erro_bit_paridade_par (vector<char> quadro);
vector<char> camada_enlace_dados_receptora_controle_de_erro_crc (vector<char> quadro);