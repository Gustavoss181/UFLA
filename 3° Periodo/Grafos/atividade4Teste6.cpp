/*
Bryan Naneti - 202121026
Gustavo Soares - 202120103
Rafael Furtado - 202120498
*/

#include<iostream>
#include<vector>
#include <queue>
#include <algorithm>
#include <map>
using namespace std;

#define INF 1000

//*******************//
// Variaveis globais //
//*******************//

// Matriz de adjacencia do grafo direcionado
int** MA;
int** residual;

// Valor do fluxo maximo acumulado
int fluxo_max;

// Valor do fluxo maximo na iteracao atual
int fluxo;

// Origem
int s;

// Destino
int t;

// Vetor que armazena o pai de cada vertice pela BFS
typedef vector<int> vi;
vi pai;

// Vetor que armazena a distancia de cada vertice, obtida pela BFS
vi dist;

typedef pair<int,int> par;
vector<par> pares;

// Numero de vertices do grafo
int n;

// Numero de arestas do grafo
int m;

//mapa
map<int, pair<int, int>> mapaVertices;

void caminho_aumentante(int v, int capacidade_fluxo){
    if(v == s){
        fluxo = capacidade_fluxo;
        return;
    }
 
    else if (pai[v] != -1){
        caminho_aumentante(pai[v], min(capacidade_fluxo, residual[pai[v]][v]));
        residual[pai[v]][v] -= fluxo;
        residual[v][pai[v]] += fluxo;
    }
}

void bfs(){
    pai.assign(n+m, -1);
    dist.assign(n+m, INF);
    dist[s] = 0;
    queue<int> fila;
    fila.push(s);
 
    while(!fila.empty()){
        int u = fila.front();
        fila.pop();
        if(u == t)
          break;
     
        for(int v = 0; v < n+m; v++){
            if(residual[u][v] && dist[v] == INF){
                dist[v] = dist[u] + 1;
                fila.push(v);
                pai[v] = u;
            }
        }
    }
}

int main(){
    cin >> n >> m;

    while(n != 0 and m != 0){
        residual = new int*[n+m];
        for(int i = 0; i < n+m; i++){
            residual[i] = new int[n+m];
            for(int j=0; j<n+m; j++)
                residual[i][j] = 0;
        }

        MA = new int*[n];
        for(int i = 0; i < n; i++){
            MA[i] = new int[n];
            for(int j = 0; j < n; j++){
                MA[i][j] = 0;
            }
        }

        int u, v, cap;
        int k = n;
        for(int i = 0; i < m; i++){
            cin >> u >> v >> cap;
            u--;
            v--;
            residual[u][k] = cap;
            residual[k][v] = cap;
            residual[v][u] = cap;
            mapaVertices[k] = par(u, v);
            MA[u][v] = MA[v][u] = cap;
            k++;
        }
        
        fluxo_max = 0;
        s = 0;
        t = 1;
    
        while(true){
            fluxo = 0;
            bfs();
            caminho_aumentante(t, INF);
            if(!fluxo)
            break;
            fluxo_max += fluxo;
        }

        int** residual2 = new int*[n];
        for(int i=0; i<n; i++){
            residual2[i] = new int[n];
            for(int j=0; j<n; j++)
                residual2[i][j] = 0;
        }

        for(int k=n; k<n+m; k++)
            residual2[mapaVertices[k].first][mapaVertices[k].second] = residual[mapaVertices[k].first][k];
        
        int pertence[n];
        pertence[0] = 1;
        for(int i=1; i<n; i++)
            pertence[i] = 0;
        
        for(int i=1; i<n; i++)
            if(residual2[0][i] > 0)
                pertence[i] = 1;

        for(int i=0; i<n; i++)
            for(int j=1; j<n; j++)
                if(residual2[i][j] == 0 and MA[i][j] != 0 and pertence[i] == 1)
                    cout << i+1 << " " << j+1 << endl;

        cin >> n >> m;
    }

    return 0;
}