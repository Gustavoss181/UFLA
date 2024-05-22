#include<iostream>

using namespace std;

int main(){
    int n, par = 0, impar = 0;

    cin >> n;

    if(n/10000 % 2 == 0)
        par++;
    else
        impar++;

    if(n/1000 % 2 == 0)
        par++;
    else
        impar++;

    if(n/100 % 2 == 0)
        par++;
    else
        impar++;

    if(n/10 % 2 == 0)
        par++;
    else
        impar++;

    if(n % 2 == 0)
        par++;
    else
        impar++;

    cout << par << endl << impar;

    return 0;
}