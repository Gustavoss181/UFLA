#include<iostream>
using namespace std;

int main(){
    int m[4][4];

    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            cin >> m[i][j];

    int somaLinha = 0, somaCol = 0;
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++){
            if(m[i][j] == -1) m[i][j] = 2;
            else if(m[i][j] < 0) m[i][j] *= -1;
            somaLinha += m[i][j];
            somaCol += m[j][i];
        }
    if(somaLinha == 4 and somaCol == 4)
        cout << "sim";
    else
        cout << "nao";
    
    return 0;
}