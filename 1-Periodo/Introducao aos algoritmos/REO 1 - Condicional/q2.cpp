#include<iostream>

using namespace std;

int main(){
    char sexo;
    float altura, peso;

    cin >> sexo >> altura;

    if(sexo == 'M'){
        peso = (72.7 * altura) - 58;
    }else if(sexo == 'F'){
        peso = (62.1 * altura) - 44.7;
    }

    cout << peso;

    return 0;
}