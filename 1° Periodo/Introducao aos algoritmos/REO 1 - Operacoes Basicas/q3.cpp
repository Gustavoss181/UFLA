#include<iostream>

using namespace std;

int main(){
    float real, dolar, euro, libra;

    cin >> real;

    dolar = real/2.13;
    euro = real/2.84;
    libra = real/3.34;

    cout << dolar << endl;
    cout << euro << endl;
    cout << libra << endl;

    return 0;
}