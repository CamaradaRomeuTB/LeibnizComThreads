#include <iostream>
#include <iomanip>

using namespace std;

int main() 
{
    long long N; // número de termos da série de Leibniz que serão calculados
    cout << "Digite a quantidade de termos da série que serão calculados: ";
    cin >> N;
    double soma = 0.0; // soma dos termos

    for (long long k = 0; k < N; k++)
    {
        double sinal = (k % 2 == 0) ? 1.0 : -1.0; // se o contador 'k' for par, o sinal do termo será positivo; se 'k' for ímpar, o sinal será negativo (mesma função de -1^n, mas mais simples)
        soma += sinal / (2.0 * k + 1.0); // calcula o termo e o soma à soma total 'soma'
    }

    double pi = 4.0 * soma; // calcula aproximação de pi multiplicando a soma total dos termos por 4

    cout << fixed << setprecision(15) << "pi = " << pi << endl; // print dos resultados

    return 0;
}