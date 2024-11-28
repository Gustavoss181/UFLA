#include<iostream>
using namespace std;

int main(){
    int matricula, maiorMatri, segMaiorMatri;
    float nota, maiorNota = -1, segMaiorNota = -1;

    cin >> matricula;
    while(matricula != 0){
        cin >> nota;
        if(nota > maiorNota){
            segMaiorMatri = maiorMatri;
            segMaiorNota = maiorNota;
            maiorNota = nota;
            maiorMatri = matricula;
        }
        else if(nota > segMaiorNota){
            segMaiorNota = nota;
            segMaiorMatri = matricula;
        }
        cin >> matricula;
    }

    cout << maiorMatri << " " << maiorNota << endl;
    cout << segMaiorMatri << " " << segMaiorNota;

    return 0;
}