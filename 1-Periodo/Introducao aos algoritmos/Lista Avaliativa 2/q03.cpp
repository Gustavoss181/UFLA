#include<iostream>
using namespace std;

int main(){
    const int l=2, c=2, p=3;
    int n;
    
    //alocar
    int*** m = new int **[l];
    for(int i=0; i<l; i++){
        m[i] = new int *[c];
        for(int j=0; j<c; j++)
            m[i][j] = new int [p];
    }

    //inserir dados
    for(int i=0; i<l; i++)
        for(int j=0; j<c; j++)
            for(int k=0; k<p; k++)
                cin >> m[i][j][k];
    cin >> n;
    
    //mostrar resultado
    bool ctrl = true;
    for(int i=0; i<l; i++)
        for(int j=0; j<c; j++)
            for(int k=0; k<p; k++)
                if(m[i][j][k] == n){
                    cout << i << " " << j << " " << k << endl;
                    ctrl = false;
                }
    if(ctrl)
        cout << -1;
    //desalocar
    for(int i=0; i<l; i++)
        for(int j=0; j<c; j++)
            delete[] m[i][j];
    for(int i=0; i<l; i++)
        delete[] m[i];
    delete[] m;

    return 0;
}