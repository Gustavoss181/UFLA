#include<iostream>

using namespace std;

int main(){
    float saldoM, credito;

    cin >> saldoM;

    if(saldoM < 0)
        credito = 0;
    else if(saldoM < 200)
        credito = saldoM*0.10;
    else if(saldoM < 400)
        credito = saldoM*0.15;
    else if(saldoM < 800)
        credito = saldoM*0.20;
    else if(saldoM < 1600)
        credito = saldoM*0.25;
    else
        credito = saldoM*0.30;

    cout << saldoM << endl << credito;

    return 0;
}