#include<iostream>

using namespace std;

int main(){
    int nProduto, nCaixa;

    cin >> nProduto;

    nCaixa = (nProduto-1)/6 + 1;

    cout << nCaixa;

    return 0;
}