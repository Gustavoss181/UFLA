#include<iostream>
using namespace std;

void simplificarFracao(int num, int den){
    int cont=1, maxDivComum = 1;

    while(cont < num or cont < den){
        if(num%cont == 0 and den%cont == 0)
            maxDivComum = cont;
        cont++;
    }

    cout << num/maxDivComum << endl << den/maxDivComum;
}

int main(){
    int num, den;

    cin >> num >> den;

    simplificarFracao(num, den);

    return 0;
}