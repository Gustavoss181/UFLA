#include <bits/stdc++.h>
#define INF INT_MAX
using namespace std;

void floydWarshall(int grafo[][100], int V) {
    int dist[V][V];
    int pai[V][V];

    for(int i=0; i<V; i++) {
        for(int j=0; j<V; j++) {
            dist[i][j] = grafo[i][j];
            if(grafo[i][j] != INF && i!=j) {
                pai[i][j] = i;
            }
            else {
                pai[i][j] = -1;
            }
        }
    }

    for(int k=0; k<V; k++) {
        for(int i=0; i<V; i++) {
            for(int j=0; j<V; j++) {
                if(dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    pai[i][j] = pai[k][j];
                }
            }
        }
    }

    cout << "Matriz de Distância:\n";
    for(int i=0; i<V; i++) {
        for(int j=0; j<V; j++) {
            if(dist[i][j] == INF) {
                cout << "INF\t";
            }
            else {
                cout << dist[i][j] << "\t";
            }
        }
        cout << endl;
    }

    cout << "Matriz de Pai:\n";
    for(int i=0; i<V; i++) {
        for(int j=0; j<V; j++) {
            cout << pai[i][j] << "\t";
        }
        cout << endl;
    }
}

int main() {
    int V, E;
    cin >> V >> E;
    int grafo[100][100];

    for(int i=0; i<V; i++) {
        for(int j=0; j<V; j++) {
            if(i==j) {
                grafo[i][j] = 0;
            }
            else {
                grafo[i][j] = INF;
            }
        }
    }

    for(int i=0; i<E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        grafo[u][v] = w;
        grafo[v][u] = w;
    }

    floydWarshall(grafo, V);
    return 0;
}