/*
Implemente um algoritmo paralelo com OpenMP para realizar a  soma dos termos da série  1 − 1/2 + 1/3 − 1/4 + ⋯ -1/N, 
onde N é informado pelo usuário e corresponde ao número de termos da série.
Exemplo:
    Entrada: 3
    Saída: 0.83
*/

#include <iostream>
#include <omp.h>

using namespace std;

int main(){
    int n;
    cout << "Digite um inteiro: ";
    cin >> n;

    double soma = 0;
    #pragma omp parallel for num_threads(4) reduction(+:soma)
    for(int i=1; i<n+1; i++){
        if(i%2 == 0)
            soma = soma + (-1.0/i);
        else
            soma = soma + 1.0/i;
    }

    cout << "Resultado: " << soma << endl;

    return 0;
}