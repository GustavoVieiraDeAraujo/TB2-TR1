// Teleinformática e Redes 2023.1, UnB
// Prof. Marcelo Marotta
// Simulador de Teste, onde o objetivo é representar três formatos de codificações, sendo eles: Codificação Binária, Codificação Manchester e codificação Bipolar. Ao iniciar a simulação, o usuário deverá enviar via terminal a mensagem que será transmitida, e escolher qual codificação será utilizada em todo processo. Para selecionar a codificação, o usuário deverá digitar apenas o número indicado em cada codificação.
#include "./CamadaFisica.hpp"
#include "./MontagemGrafico.hpp"

int main(void) {
    string mensagem_enviada;
    mensagem_enviada = aplicacao_transmissora(); // Função que recebe a mensagem

    // Estrutura para escolher qual formato de codificação será utilizado
    int codificacao;
    cout << "Escolha a Codificação (Digite somente o número indicado a codificação desejada): [0] Codificação Binária | [1] Codificação Manchester | [2] Codificação Bipolar:" << endl;
    cin >> codificacao; // Codificação Selecionada

    // Função que transforma a mensagem em um quadro composto por bits
    vector<char> quadro_enviado;
    quadro_enviado = camada_de_aplicacao_transmissora(mensagem_enviada);

    vector<char> trem_de_bits_enviado;
    trem_de_bits_enviado = camada_fisica_transmissora(quadro_enviado, codificacao);


    vector<char> trem_de_bits_recebido;
    trem_de_bits_recebido = meio_de_comunicacao(trem_de_bits_enviado);

    // limpar;
    cout << "O seguinte sinal esta sendo enviado:" << endl;
    construir_sinal(trem_de_bits_recebido, codificacao);
    this_thread::sleep_for(chrono::seconds(5));
    // limpar;

    vector<char> quadro_recebido;
    quadro_recebido = camada_fisica_receptora(trem_de_bits_recebido, codificacao);

    string mensagem_recebida;
    mensagem_recebida = camada_de_aplicacao_receptora(quadro_recebido);

    aplicacao_receptora(mensagem_recebida);

    return 0;
}