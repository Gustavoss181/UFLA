#include<iostream>

using namespace std;

int main(){
    float salaMin, salaB, salario;
    int hrsTrab;

    cin >> salaMin;
    cin >> hrsTrab;

    salaB = hrsTrab * salaMin*0.05;

    salario = salaB - salaB * 0.23;

    cout << salario;

    return 0;
}