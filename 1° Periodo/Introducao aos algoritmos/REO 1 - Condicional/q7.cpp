#include<iostream>

using namespace std;

int main(){
    int tipo;
    float valorI, valorF;

    cin >> tipo >> valorI;

    switch (tipo)
    {
    case 1:
        valorF = valorI*1.005;
        break;
    case 2:
        valorF = valorI*1.03 - 30;
        break;
    default:
        break;
    }

    cout << valorF;

    return 0;
}