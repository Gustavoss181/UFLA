#include<iostream>
using namespace std;

int main(){
    int cont = 0, qtdA = 0, qtdB = 0;
    char c;

    while (cont < 10){
        cont++;
        cin >> c;
        if(c == 'a')
            qtdA++;
        else
            qtdB++;
    }

    if(qtdA < qtdB)
        cout << 1;
    else
        cout << 0;

    return 0;
}