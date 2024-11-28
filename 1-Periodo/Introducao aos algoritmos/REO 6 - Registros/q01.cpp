#include<iostream>
using namespace std;

struct Carro{
    string nome;
    int ano;
    int preco;
};

int main(){
    int n, ref;
    cin >> n;
    Carro carros[n];
    for(int i=0; i<n; i++){
        cin >> carros[i].nome;
        cin >> carros[i].ano;
        cin >> carros[i].preco;
    }
    cin >> ref;

    for(Carro carro : carros){
        if(carro.preco < ref)
            cout << carro.nome << " " << carro.ano << " " << carro.preco << endl;
    }

    return 0;
}