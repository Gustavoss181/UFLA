#include<iostream>
using namespace std;

int main(){
    int cont, nMenos2 = 0, nMenos1 = 1, n;

    cin >> cont;
    
    if(cont == 1)
        cout << nMenos2;
    else{
        cout << nMenos2 << endl;
        cout << nMenos1 << endl;
        while(cont-2 > 0){
            cont--;
            n = nMenos2 + nMenos1;
            nMenos2 = nMenos1;
            nMenos1 = n;
            cout << n << endl;
        }
    }

    return 0;
}