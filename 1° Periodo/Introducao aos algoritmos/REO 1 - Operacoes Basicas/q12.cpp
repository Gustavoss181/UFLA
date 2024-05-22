#include<iostream>

using namespace std;

int main(){
    int valorI, n100, n50, n20, n10, n5, n2, n1;

    cin >> valorI;

    n100 = valorI/100;
    valorI %= 100;
    n50 = valorI/50;
    valorI %= 50;
    n20 = valorI/20;
    valorI %= 20;
    n10 = valorI/10;
    valorI %= 10;
    n5 = valorI/5;
    valorI %= 5;
    n2 = valorI/2;
    valorI %= 2;
    n1 = valorI;

    cout << n100 << endl;
    cout << n50 << endl;
    cout << n20 << endl;
    cout << n10 << endl;
    cout << n5 << endl;
    cout << n2 << endl;
    cout << n1 << endl;

    return 0;
}