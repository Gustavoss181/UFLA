#include<iostream>
using namespace std;

int main(){
    float iti[4][4];

    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            cin >> iti[i][j];

    int n, par, che;
    float valor=0;
    cin >> n;
    cin >> par;
    for(int i=0; i<n-1; i++){
        cin >> che;
        valor += iti[par][che];
        par = che;
    }

    cout << valor;

    return 0;
}