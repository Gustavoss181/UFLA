#include<iostream>
using namespace std;

int main(){
    float m[4][4];

    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            cin >> m[i][j];

    float soma1=0, soma2=0;

    for(int i=0; i<4; i++){
        float mult=1;
        for(int j=0; j<4; j++)
            mult *= m[j][(j+i)%4];
        soma1 += mult;
    }

    for(int i=0; i<4; i++){
        float mult=1;
        for(int j=0; j<4; j++)
            mult *= m[j][(3-j+i)%4];
        soma2 += mult;
    }

    cout << soma1 - soma2;
    
    return 0;
}