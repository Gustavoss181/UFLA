#include<iostream>
using namespace std;

string* desduplica(string v[], int *t){
    //trecho para saber o tamanho do vetor a ser retornado
    int cont=0;
    string nome="";
    for(int i=0; i<*t; i++){
        if(nome != v[i]){
            nome = v[i];
            cont++;
        }
    }
    //preenchimento do vetor a ser retornado
    string *novoV = new string[cont];
    cont=0;
    nome="";
    for(int i=0; i<*t; i++){
        if(nome != v[i]){
            nome = v[i];
            novoV[cont] = nome;
            cont++;
        }
    }

    *t=cont;
    return novoV;
}

int main(){
    int n;
    cin >> n;
    string v[n], *ptrV=NULL;
    for(int i=0; i<n; i++)
        cin >> v[i];
    
    ptrV = desduplica(v, &n);

    cout << n << endl;
    for(int i=0; i<n; i++)
        cout << ptrV[i] << endl;
    
    return 0;
}