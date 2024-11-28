#include<iostream>

using namespace std;

int main(){
    int valorEntregue, valorT, troco, n20, n10, n5, n2, n1;

    cin >> valorEntregue;
    cin >> valorT;

    troco = valorEntregue - valorT;

    n20 = troco/20;
    troco %= 20;
    n10 = troco/10;
    troco %= 10;
    n5 = troco/5;
    troco %= 5;
    n2 = troco/2;
    troco %= 2;
    n1 = troco;

    cout << n20 << endl;
    cout << n10 << endl;
    cout << n5 << endl;
    cout << n2 << endl;
    cout << n1 << endl;

    return 0;
}