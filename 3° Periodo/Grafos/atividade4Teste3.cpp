#include <iostream>
#include <vector>
#include <utility>
#include <functional>
using namespace std;

#define INF 1000000000
#define NIL -1

/*
 * Variaveis globais
 */

// matriz de adjacencia
int** MA;

int** pai;

// quantidade de vertices
int n;

// quantidade de arestas
int m;

// quantidade de pares origem-destino a ser calculado
int k;

int floyd_warshall(){
    for(int k = 0; k < n; k++)
        for(int i = 0; i < n; i++)
            for(int j = i+1; j < n; j++)
                if(MA[i][j] > MA[i][k] + MA[k][j] and k > i){
                    MA[i][j] = MA[i][k] + MA[k][j];
                    MA[j][i] = MA[i][k] + MA[k][j];
                    pai[i][j] = pai[k][j];
                }
}

int main(){
    
    cin >> n >> m;
    while(n != 0 && m != 0){
        MA = new int*[n];
        pai = new int*[n];
        int u, v, h;
     
        for(int i = 0; i < n; i++){
            MA[i] = new int[n];
            pai[i] = new int[n];
            for(int j = 0; j < n; j++){
                MA[i][j] = INF;
                pai[i][j] = NIL;
            }
        }

        for(int i = 0; i < m; i++){
            cin >> u >> v >> h;
            u--;
            v--;
            MA[u][v] = MA[v][u] = h;
            pai[u][v] = u;
        }
     
        floyd_warshall();

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++)
                cout << pai[i][j]+1 << " ";
            cout << endl;
        }

        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                if(pai[i][j] == i)
                    cout << i+1 << " " << j+1 << " " << MA[i][j] << endl;
        

        for(int i=0; i<n; i++){
            delete [] MA[i];
            delete [] pai[i];
        }
        delete [] MA;
        delete [] pai;
     
        cin >> n >> m;
    }
 
    return 0;
}