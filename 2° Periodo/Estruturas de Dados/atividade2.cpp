/*
Autores:
Bryan Naneti - 202121026
Gustavo Soares Silva - 202120103
Rafael Furtado - 202120498
*/

#include<utility>
#include<vector>
#include<iostream>
#include <queue>
#include <climits>
using namespace std;

typedef pair<int, int> ii; // pares de inteiros
typedef vector<int> vi; // vetor de inteiros
typedef vector<ii> vii; // vetor de pares de inteiros

vi explorado;
priority_queue<ii> Q;
vector<vii> LA;
int n;
int m;

void atualizaFila(int u){
  explorado[u] = 1;
	for(int j = 0; j < int(LA[u].size()); j++){
		ii v = LA[u][j];
		if(!explorado[v.first])
			Q.push(ii(v.second, v.first));
	}
}

int prim(){
	explorado.assign(n, 0);
	atualizaFila(1);
	
	// custo da AGM
	int resultado = INT_MAX;
	
	while(!Q.empty()){
		ii u = Q.top();
		Q.pop();

		int w = u.first;
		int v = u.second;
 
		if(!explorado[v]){
			if(resultado > w)
				resultado = w;
			atualizaFila(v);
		}
	}

	return resultado;
}

int main(){
	int qtdTestes;
	cin >> qtdTestes;
	
	for(int cont=0; cont < qtdTestes; cont++){
		cin >> n >> m;
	
		for(int i = 0; i <= n; i++){
			vii lista;
			LA.push_back(lista);
		}
				
		int u, v, w;
		for(int i = 0; i < m; i++){
			cin >> u >> v >> w;
			int contador = 0, continua = 0;
			for(vector<vii>::iterator it = LA.begin(); it != LA.end() && continua < 2; ++it){
				if(contador == u){
					ii par1(v, w);
					(*it).push_back(par1);    
					continua++;
				}
		 
				else if(contador == v){
					ii par2(u, w);
					(*it).push_back(par2);    
					continua++;
				}
				contador++;
			}
		}
	
		cout << prim() << endl;
		LA.clear();
		explorado.clear();
	}
	return 0;
}
