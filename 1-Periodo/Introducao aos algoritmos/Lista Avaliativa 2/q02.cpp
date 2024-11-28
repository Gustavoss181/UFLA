#include<iostream>
using namespace std;

int main(){
    int t;
    cin >> t;
    string frase[t];
    for(int i=0; i<t; i++)
        cin >> frase[i];
    
    const int UMPRIMO = 37;
    const int M = 15;
    int somaHash = 0;
    for(int i=0; i<t; i++){
        long hash = 0;
        for(unsigned j = 0; j < frase[i].size(); j++){
            hash = (UMPRIMO * hash + frase[i][j]) % M;
        }
        cout << hash << " ";
        somaHash += hash;
    }
    cout << somaHash;

    return 0;
}