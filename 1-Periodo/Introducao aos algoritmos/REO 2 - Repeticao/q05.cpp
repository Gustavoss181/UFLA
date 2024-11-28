#include<iostream>
using namespace std;

int main(){
    int n, cont = 2, resultado = 1;

    cin >> n;

    while(cont-1 < n){
        resultado += cont;
        cont++;
    }

    cout << resultado;

    return 0;
}