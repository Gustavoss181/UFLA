#include<iostream>
using namespace std;

int main(){
    char gabarito[8];
    char alunos[10][8];
    float notas[10] = {0};

    for(int i=0; i<8; i++)
        cin >> gabarito[i];
    
    for(int i=0; i<10; i++)
        for(int j=0; j<8; j++)
            cin >> alunos[i][j];

    for(int i=0; i<10; i++)
        for(int j=0; j<8; j++)
            if(alunos[i][j] == gabarito[j])
                notas[i] += 100/8.0;

    int cont = 0;
    for(int i=0; i<10; i++){
        cout << notas[i] << endl;
        if(notas[i] >= 60)
            cont += 10;
    }

    cout << endl << cont;
        

    return 0;
}