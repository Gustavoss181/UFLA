/* 
Bryan Naneti - 202121026
Gustavo Soares - 202120103
Rafael Furtado - 202120498
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
#define INF 10000000

int**MAdj;
int fluxo_max;
int fluxo;
int s;
int t;
typedef vector<int> vi;
vi pai;
vi dis;
vi dTeste;
int n;
int m;
bool flag = false;
vi testesResp;

bool alcancaFim(int valorA, vi *LAdj){
	
	bool fim = false;
	dTeste.assign(valorA, INF);
	dTeste[s] = 0;
	
	queue<int> filaAux;
	filaAux.push(s);
	
	while(!filaAux.empty()){
		int u = filaAux.front();
		filaAux.pop();
		
		if(u == t){
			fim = true;
			break;
		}
		
		for(auto it = LAdj[u].begin(); it != LAdj[u].end(); it++){
			if(dTeste[*it] == INF){
				dTeste[*it] = dTeste[u] + 1;
				filaAux.push(*it);
			}
		}
	}
	
	return fim;
}

void testePercurso(int v, int capFluxo, int valorA){
	if(v == s)
		fluxo = capFluxo;
	
	else if(pai[v] != -1){
		testePercurso(pai[v], min(capFluxo,MAdj[pai[v]][v]), valorA);
		MAdj[pai[v]][v] -= fluxo;
		MAdj[v][pai[v]] += fluxo;
		
		if((!flag) and (MAdj[pai[v]][v] == 0) and (pai[v] < valorA)){
			flag = true;
			if(v >= valorA){
				int filhoV = -1;

				for(int i = 1; i <= n; i++){
					if(MAdj[v][i] != 0){
						filhoV = i;
						break;
					}
				}
				
				testesResp.push_back(pai[v]);
				testesResp.push_back(filhoV);
			}
			else{
				testesResp.push_back(pai[v]);
				testesResp.push_back(v);
			}
		}
	}
}

void buscaLargura(int valorA){
	pai.assign(n + 1, -1);
	dis.assign(n + 1, INF);
	
	dis[s] = 0;
	
	queue<int> filaAux;
	filaAux.push(s);
	
	while(!filaAux.empty()){
		int u = filaAux.front();
		filaAux.pop();
		
		if(u == t)
			break;
			
		for(int v = 1; v <= n; v++){
			if(MAdj[u][v] != 0){
				if(v >= valorA and dis[v] == INF){
					dis[v] = dis[u];
					pai[v] = u;
					
					int filhoV = -1;
					
					for(int i = 1; i <= n; i++){
						if(MAdj[v][i] != 0){
							filhoV = i;
							break;
						}
					}
					
					if(dis[filhoV] == INF){
						dis[filhoV] = dis[v] + 1;
						filaAux.push(filhoV);
						pai[filhoV] = v;
					}
				}
				
				else{
					if(dis[v] == INF){
						dis[v] = dis[u] + 1;
						filaAux.push(v);
						pai[v] = u;
					}
				}
			}
		}
	}
}

int main(){
	cin >> n >> m;
	
	while(n != 0 and m != 0){
		int k = n + 1;
		int valorA = k;
		
		n += m;
		
		MAdj = new int*[n + 1];
		for(int i = 1; i <= n; i++)
			MAdj[i] = new int[n + 1];
			
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				MAdj[i][j] = 0;

		vi *LA = new vi[valorA];
		
		int u, v, cap;
		for(int i = 0; i < m; i++){
			cin >> u >> v >> cap;
			MAdj[u][k] =MAdj[k][v] =MAdj[v][u] = cap;
			k++;
			LA[u].push_back(v);
			LA[v].push_back(u);
		}
		
		fluxo_max = 0;
		s = 1;
		t = 2;
		
		while(true){
			fluxo = 0;
			buscaLargura(valorA);
			flag = false;
			testePercurso(t, INF, valorA);
			if(!fluxo)
				break;
			fluxo_max += fluxo;
		}
		
		for(int i = 0; i < testesResp.size(); i += 2){
			int v1 = testesResp.at(i);
			int v2 = testesResp.at(i + 1);
			LA[v1].erase(remove(LA[v1].begin(), LA[v1].end(), v2), LA[v1].end());
			LA[v2].erase(remove(LA[v2].begin(), LA[v2].end(), v1), LA[v2].end());
		}

		for(int i = 0; i < testesResp.size(); i += 2){
			int v1 = testesResp.at(i);
			int v2 = testesResp.at(i + 1);
			
			LA[v1].push_back(v2);
			LA[v2].push_back(v1);
			
			if(alcancaFim(valorA, LA)){
				cout << v1 << " " << v2 << endl;
			}
			
			LA[v1].erase(remove(LA[v1].begin(), LA[v1].end(), v2), LA[v1].end());
			LA[v2].erase(remove(LA[v2].begin(), LA[v2].end(), v1), LA[v2].end());
		}
		
		testesResp.clear();
		delete[] LA;
		
		cout << endl;
		
		cin >> n >> m;
	}
	
	return 0;
}
