#include <iostream>
#include <iomanip>
#include <pthread.h>
#include <cstdlib>

using namespace std;

struct ThreadData // estrutura com dados necessários para as threads
{
    long long comeco; // começo do intervalo de iteração
    long long fim; // fim do intervalo de iteração
    int index; // posição dentro do vetor de resultados parciais
    double* resultado; // ponteiro para o vetor de resultados parciais
};

void* thread_func(void* arg)  // função da trhead
{
    ThreadData* data = (ThreadData*)arg; // cast do ponteiro 'arg' para o tipo ThreadData, amrmazenamento deste ponteiro na variável 'data'
    double soma_local = 0.0; // variável local que armazena a soma

    for (long long k = data->comeco; k < data->fim; k++) // laço for que realiza o cálculo dos termos entre 'comeco' e 'fim' do ponteiro
    {
        double sign = (k % 2 == 0) ? 1.0 : -1.0;
        soma_local += sign / (2.0 * k + 1.0);
    }

    data->resultado[data->index] = soma_local; // armazena o resultado parcial obtido no laço acima no vetor de resultados através do ponteiro 'resultado', na posição 'index' no vetor
    return nullptr;
}

int main(int argc, char* argv[])  // main receberá dois argumentos do usuário para o código funcionar: o primeiro (argv[1]) é a quantidade de termos da série de Leibniz que serão calculados, o segundo (argv[2]) é a quantidade de threads utilizadas
{
    if (argc != 3) 
    {
        cout << "Você deve passar dois argumentos: <quantidadeDeTermos> <quantidadeDeThreads>" << endl;
        return 1;
    }

    long long N = atoll(argv[1]); // 'N' armazena a quantidade de termos da série que serão calculados
    int num_threads = atoi(argv[2]); // 'num-threads' armazena a quantidade de threads usadas

    // armazenamento de dados das threads com alocação dinâmica de memória
    pthread_t* threads = new pthread_t[num_threads]; // cira vetor 'threads' com identificadores de thread, na quantidade passada por 'num_threads'
    ThreadData* tdata = new ThreadData[num_threads]; // cria vetor 'tdata' com estruturas ThreadData, com as informações para cada thread
    double* resultado = new double[num_threads]; // cria vetor 'resultado' que armazenará os resultados parciais de cada thread

    long long BlocoDeIteracoes = N / num_threads; // definição do tamanho de cada bloco de iteração parcial para cada thread, distribuindo o número de termos ('N') para o número de threads ('num_threads')

    for (int i = 0; i < num_threads; i++)  // para cada thread 'i':
    {
        tdata[i].comeco = i * BlocoDeIteracoes; // cálculo da posição inicial de iteração ('comeco') para a thread
        tdata[i].fim = (i == num_threads - 1) ? N : (i + 1) * BlocoDeIteracoes; // cálculo da posição final de iteração ('fim') para a thread, será 'N' se esta thread for a última (condição 'i == num_threads - 1') e será o próximo bloco se não for a última
        tdata[i].index = i;
        tdata[i].resultado = resultado; // aponta o resultado parcial da thread para o vetor geral de resultados

        pthread_create(&threads[i], nullptr, thread_func, &tdata[i]); // cria e inicia a thread
    }

    for (int i = 0; i < num_threads; i++) // laço faz a 'main' aguardar pela finalização da execução de cada thread
    {
        pthread_join(threads[i], nullptr); // bloqueia a execução até que a thread 'i' finalize execução
    }

    double soma = 0.0; // variável que armazenará a soma final dos termos calculados pelas threads
    for (int i = 0; i < num_threads; i++)  // laço que soma todos os resultados parciais obtidos e armazena o resultado final em 'soma'
    {
        soma += resultado[i];
    }

    double pi = 4.0 * soma; // múltiplica a soma dos termos calculados pelas threads por 4 para chegar ao valor aproximado de pi

    cout << fixed << setprecision(15) << "pi = " << pi << "\n";

    // liberação da mmemória alocada pelo programa
    delete[] threads;
    delete[] tdata;
    delete[] resultado;

    return 0;
}
