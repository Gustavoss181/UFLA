#include <iostream>
#include <time.h>
#include <omp.h>

#define N 10

using namespace std;

int* gerarVetorAleatorio(int tam, int seed = time(NULL), int min = 0, int max = 100){
    int *vet = new int[tam];

    srand(seed);
    #pragma omp parallel for num_threads(4)
    for(int i=0; i<tam; i++)
        vet[i] = (rand() % (max-min)) + min;

    return vet;
}

int encontraMaior(int *vet, int inicio, int fim){
    int maior = vet[inicio];
    for(int i=inicio; i<fim; i++)

}

int main(){
    int *vet = gerarVetorAleatorio(N, 5, 0, 20);

    for(int i=0; i<N; i++)
        cout << vet[i] << " ";
    cout << endl;

    int maior = 0;
    #pragma omp parallel for num_threads(4)
    {
        for(int i=)
    }

    return 0;
}