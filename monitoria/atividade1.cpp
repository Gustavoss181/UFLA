#include <iostream>

using namespace std;


float* realocar(float* vetor, int &tam){
    int novoTam = tam + 1; // tamanho do novo vetor é tamanho antigo + 1
    float *novoVetor = new float[novoTam]; // definir novo vetor
    for(int i=0; i<tam; i++){ // cópia dos dados do vetor antigo para  o novo vetor
        novoVetor[i] = vetor[i];
    }
    tam = novoTam;
    delete [] vetor;
    return novoVetor;
}

int main(){

    int tam = 2;
    float *vetor = new float[tam];

    float valor;
    cin >> valor;
    int i=0;
    while(valor >= 0){
        if(i == tam)
            vetor = realocar(vetor, tam);
        vetor[i] = valor;
        i++;
        cin >> valor;
    }

    for(int i=0; i<tam; i++)
        cout << vetor[i] << " ";

    delete [] vetor;

    return 0;
}