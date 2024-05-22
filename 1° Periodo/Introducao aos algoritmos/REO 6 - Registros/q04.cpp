#include<iostream>
using namespace std;

struct Carga{
    string tipo;
    int qtd;
};

struct Arma{
    string nome;
    string carga;
};

int main(){
    int qtdCargas;
    cin >> qtdCargas;
    Carga cargas[qtdCargas];
    for(int i=0; i<qtdCargas; i++)
        cin >> cargas[i].tipo >> cargas[i].qtd;
    
    int qtdArmas;
    cin >> qtdArmas;
    Arma armas[qtdArmas];
    for(int i=0; i<qtdArmas; i++)
        cin >> armas[i].nome >> armas[i].carga;
    
    int soma=0;
    for(int i=0; i<qtdArmas; i++)
        for(int j=0; j<qtdCargas; j++)
            if(armas[i].carga == cargas[j].tipo)
                soma += cargas[j].qtd;
    
    cout << soma;

    return 0;
}