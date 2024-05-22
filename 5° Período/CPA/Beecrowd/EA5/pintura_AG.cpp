#include <iostream>

using namespace std;

struct Matriz{
    bool** matriz;
    int l; // n° de Linhas
    int c; // n° de colunas

    Matriz(int nLinhas, int nColunas){
        l = nLinhas;
        c = nColunas;
        matriz = new bool*[l];
        for(int i=0; i<l; i++){
            matriz[i] = new bool[c];
            for(int j=0; j<c; j++)
                matriz[i][j] = false;
        }
    }

    void mostrar(){
        cout << "---------------------" << endl;
        cout << l << " x " << c << endl;
        for(int i=0; i<l; i++){
            for(int j=0; j<c; j++)
                cout << matriz[i][j] << " ";
            cout << endl;
        }
    }

    void preencheRec(int i, int j, int lRec, int cRec){
        for(int ii=0; ii<lRec; ii++){
            for(int jj=0; jj<cRec; jj++){
                matriz[i+ii][j+jj] = !matriz[i+ii][j+jj];
            }
        }
    }

};

int preencherMatriz(Matriz desenhoFinal, int lRec, int cRec){
    Matriz resultado(desenhoFinal.l, desenhoFinal.c);

    int cont = 0;
    for(int i=0; i<resultado.l-lRec+1; i++){
        for(int j=0; j<resultado.c-cRec+1; j++){
            if(resultado.matriz[i][j] != desenhoFinal.matriz[i][j]){
                resultado.preencheRec(i, j, lRec, cRec);
                cont++;
            }
        }
    }
    
    for(int i=0; i<resultado.l; i++)
        for(int j=0; j<resultado.c; j++)
            if(resultado.matriz[i][j] != desenhoFinal.matriz[i][j])
                return -1;
    
    return cont;
}

int main(){
    int n, m, r, c;

    cin >> n >> m >> r >> c;
    while(n+m+r+c != 0){
        Matriz desenhoFinal(n, m);
        string aux;
        for(int i=0; i<n; i++){
            cin >> aux;
            for(int j=0; j<m; j++)
                desenhoFinal.matriz[i][j] = (aux[j] == '1' ? true : false);
        }
        
        cout << preencherMatriz(desenhoFinal, r, c) << endl;

        cin >> n >> m >> r >> c;
    }

    return 0;
}