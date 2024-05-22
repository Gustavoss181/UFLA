#include<iostream>
#include<cmath>

using namespace std;

int main(){
    float hDegrau, hEscada;
    int minDegraus;

    cin >> hDegrau;
    cin >> hEscada;

    hEscada *= 100;
    minDegraus = ceil(hEscada/hDegrau);

    cout << minDegraus;

    return 0;
}