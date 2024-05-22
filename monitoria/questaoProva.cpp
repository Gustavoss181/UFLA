#include <iostream>

using namespace std;

void realocar(int* &vetor, int &tam, int posValorExcluir){
    int *novoVetor = new int[tam-1];

    int cont=0;
    for(int i=0; i<tam; i++){
        if(i != posValorExcluir){
            novoVetor[cont] = vetor[i];
            cont++;
        }
    }

    delete [] vetor;
    vetor = novoVetor;
    tam--;
}

int main(){

    int tam;
    cin >> tam;

    int *vetor = new int[tam];

    for(int i=0; i<tam; i++)
        cin >> vetor[i];

    for(int i=0; i<tam-1; i++){
        for(int j=i+1; j<tam; j++){
            cout << i << " -> " << j << endl;
            if(vetor[i] == vetor[j]){
                cout << vetor[i] << " == " << vetor[j] << endl;
                realocar(vetor, tam, j);
            }
        }
    }

    for(int i=0; i<tam; i++)
        cout << vetor[i] << " ";

    delete [] vetor;

    return 0;
}