#include<iostream>
using namespace std;

// void geraMatriz(float mo[][], float mc[][], int tam, int pos){
    
// }

float det3(float m3[3][3], int tam){

}

float det4(float m4[4][4], int tam){
    float det = 0;
    for(int i=0; i<tam; i++){
        float m3[tam-1][tam-1];
        // for(int j=0; j<tam-1; j++)
        //     m3[]
        // if(i%2 == 0)
        //     det += det3()
    }
    return det;
}

int main(){
    int tam = 4;
    float m[tam][tam];

    for(int i=0; i<tam; i++)
        for(int j=0; j<tam; j++)
            cin >> m[i][j];

    cout << det4(m, tam);
    
    return 0;
}