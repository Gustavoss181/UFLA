#include<iostream>

using namespace std;

int main(){
    string cor1, cor2, mistura;

    cin >> cor1 >> cor2;

    if(cor1 == cor2)
        cout << cor1;
    else if((cor1 == "amarelo" and cor2 == "azul") or (cor1 == "azul" and cor2 == "amarelo"))
        cout << "verde";
    else if((cor1 == "amarelo" and cor2 == "vermelho") or (cor1 == "vermelho" and cor2 == "amarelo"))
        cout << "laranja";
    else if((cor1 == "vermelho" and cor2 == "azul") or (cor1 == "azul" and cor2 == "vermelho"))
        cout << "violeta";

    return 0;
}