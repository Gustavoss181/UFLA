#include<iostream>
using namespace std;

struct Pessoa{
    string nome;
    int dia;
    int mes;
    int ano;
};

int main(){
    int n;
    cin >> n;
    Pessoa pessoas[n];
    for(int i=0; i<n; i++){
        cin >> pessoas[i].nome;
        cin >> pessoas[i].dia;
        cin >> pessoas[i].mes;
        cin >> pessoas[i].ano;
    }

    Pessoa dataRef;
    cin >> dataRef.dia >> dataRef.mes >> dataRef.ano;

    for(int i=0; i<n; i++){
        cout << pessoas[i].nome << ": ";
        int idade = dataRef.ano - pessoas[i].ano;
        if(dataRef.mes < pessoas[i].mes)
            idade--;
        else if(dataRef.dia < pessoas[i].dia and dataRef.mes == pessoas[i].mes)
            idade--;
        
        if(idade < 0)
            cout << -1 << endl;
        else if(idade == 0 or idade == 1)
            cout << idade << " ano" << endl;
        else
            cout << idade << " anos" << endl;
    }

    return 0;
}