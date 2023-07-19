// Simulador de Teste, onde o objetivo é representar três formatos de codificações, sendo eles: Codificação Binária, Codificação Manchester e codificação Bipolar. Ao iniciar a simulação, o usuário deverá enviar via terminal a mensagem que será transmitida, e escolher qual codificação será utilizada em todo processo. Para selecionar a codificação, o usuário deverá digitar apenas o número indicado em cada codificação.
#include "./CamadaFisica.hpp"
#include "./CamadaEnlace.hpp"
#include "./MontagemGrafico.hpp"

int main(void) {
    string mensagem_enviada;
    mensagem_enviada = aplicacao_transmissora(); // Função que recebe a mensagem

    // Estrutura para escolher qual formato de codificação será utilizado
    int codificacao;
    cout << endl;
    cout << "Escolha a Codificação (Digite somente o número indicado a codificação desejada): [0] Codificação Binária | [1] Codificação Manchester | [2] Codificação Bipolar: ";
    cin >> codificacao; // Codificação Selecionada

    // Função que transforma a mensagem em um quadro composto por bits
    vector<char> quadro_enviado;
    quadro_enviado = camada_de_aplicacao_transmissora(mensagem_enviada);

    // Estrutura para escolher qual formato de enquadramento será utilizado
    int enquadramento;
    cout << "Escolha o Enquadramento (Digite somente o número indicado o enquadramento desejado): [0] Contagem de Caracteres | [1] Inserção de Bytes: ";
    cin >> enquadramento; // Enquadramento Selecionado

    // Estrutura para escolher qual formato de controle será utilizado
    int controle;
    cout << "Escolha o Controle (Digite somente o número indicado o controle desejado): [0] Bit de Paridade Par | [1] CRC: ";
    cin >> controle; // Controle Selecionado
    cout << endl;

    vector<char> quadro_enlace;
    quadro_enlace = camada_enlace_dados_transmissora(quadro_enviado, enquadramento, controle);

    cout << "O seguinte sinal esta sendo enviado:" << endl;
    // Imprimindo o sinal completo
    for (char i : quadro_enlace) {
        cout << i;
    }

    cout << endl;
    cout << endl;

    vector<char> trem_de_bits_enviado;
    trem_de_bits_enviado = camada_fisica_transmissora(quadro_enlace, codificacao);

    int porcentagem;
    cout << "Escolha a porcentagem de erro: (Digite somente um número de 0 a 100): ";
    cin >> porcentagem; // Controle Selecionado
    cout << endl;

    vector<char> trem_de_bits_recebido;
    trem_de_bits_recebido = meio_de_comunicacao(trem_de_bits_enviado, porcentagem);

    construir_sinal(trem_de_bits_recebido, codificacao);
    this_thread::sleep_for(chrono::seconds(5));

    vector<char> quadro_recebido;
    quadro_recebido = camada_fisica_receptora(trem_de_bits_recebido, codificacao);

    cout << "O seguinte sinal esta sendo recebido:" << endl;
    // Imprimindo o sinal completo
    for (char i : quadro_recebido) {
        cout << i;
    }

    cout << endl;
    cout << endl;

    vector<char> quadro_sem_enquadramento;
    quadro_sem_enquadramento = camada_enlace_dados_receptora(quadro_recebido, enquadramento, controle);

    string mensagem_recebida;
    mensagem_recebida = camada_de_aplicacao_receptora(quadro_sem_enquadramento);

    aplicacao_receptora(mensagem_recebida);
    return 0;
}