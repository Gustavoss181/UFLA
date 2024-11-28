#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include "header.hpp"

using namespace std;

bool lerArquivo(string nomeArq, Instancia &instancia, vector<Node> &nos, int** &MA){
	ifstream txt(nomeArq);

	if(txt){
		string str, str2;
		int campo = 0;
		
		//o csv é lido caractere por caractere
		txt >> str;
		do{
			getline(txt, str2);
			size_t start = str2.find_first_not_of(" ");
			str2 = str2.substr(start);
			switch(campo){
				case 0:
					instancia.name = str2;
					break;
				case 1:
					instancia.location = str2;
					break;
				case 2:
					instancia.comment = str2;
					break;
				case 3:
					instancia.type = str2;
					break;
				case 4:
					instancia.size = stoi(str2);
					break;
				case 5:
					instancia.distribution = str2;
					break;
				case 6:
					instancia.depot = str2;
					break;
				case 7:
					instancia.routeTime = stoi(str2);
					break;
				case 8:
					instancia.timeWindow = stoi(str2);
					break;
				case 9:
					instancia.capacity = stoi(str2);
					break;
				default:
					break;
			}
			campo++;

			txt >> str;
		}while (str != "NODES");

		for(int i=0; i<instancia.size; i++){
			txt >> str;
			Node aux;
			aux.id = stoi(str);
			txt >> str;
			aux.lat = stof(str);
			txt >> str;
			aux.lon = stof(str);
			txt >> str;
			aux.dem = stoi(str);
			txt >> str;
			aux.etw = stoi(str);
			txt >> str;
			aux.ltw = stoi(str);
			txt >> str;
			aux.dur = stoi(str);
			txt >> str;
			aux.p = stoi(str);
			txt >> str;
			aux.d = stoi(str);

			nos.push_back(aux);
		}

		MA = new int*[instancia.size];
		for(int i=0; i<instancia.size; i++)
			MA[i] = new int[instancia.size];
		
		
		txt >> str;
		for(int i=0; i<instancia.size; i++){
			for(int j=0; j<instancia.size; j++){
				txt >> str;
				MA[i][j] = stoi(str);
			}
		}

		txt.close();

		return true;
	}
	else
		return false;
}

void definirPacotes(Pacote* &pacotes, Instancia &instancia, Node* &nos){
	instancia.nPacotes = (instancia.size-1)/2;
	pacotes = new Pacote[instancia.nPacotes];

	int idPacote = 0;
	for(int i=0; i<instancia.size; i++){
		if(nos[i].dem > 0){
			pacotes[idPacote].id = idPacote;
			pacotes[idPacote].pColeta = nos[i].id;
			pacotes[idPacote].pEntrega = nos[nos[i].d].id;
			nos[i].idPacote = idPacote;
			nos[nos[i].d].idPacote = idPacote;
			pacotes[idPacote].coletado = false;
			pacotes[idPacote].entregue = false;
			pacotes[idPacote].idVeiculo = NAO_DEFINIDO;
			idPacote++;
		}
	}
}


bool verificarRota(Instancia instancia, vector<Node> nos, int** MA, vector<int> rota, Pacote *pacotes){
    Veiculo aux = Veiculo(0);
    aux.rota = rota;

	int tempo = 0;

	for(int i=1; i<rota.size(); i++){
		int pAtual = rota[i];
		Node pontoAtual = nos[pAtual];
		Pacote pacote = pacotes[pontoAtual.idPacote];

		// tempo de rota atual
		int pAnterior = rota[i-1];
		tempo += MA[pAnterior][pAtual];


        if(pontoAtual.ltw < tempo){
            return false;
        }
		if(pontoAtual.etw > tempo)
            tempo += (pontoAtual.etw - tempo);

		// se o no atual for uma entrega e o par dele de coleta não foi coletado retorna erro
        if(pontoAtual.dem > 0){ // se for um ponto de coleta
            pacote.coletado = true;
        }
        if(pontoAtual.dem < 0 and pacote.coletado){ // se for um ponto de entrega
            pacote.entregue = true;
        }

        tempo += pontoAtual.dur;

        aux.carga += pontoAtual.dem;

        if(aux.carga > instancia.capacity)
            return false;
        
        if(instancia.routeTime < tempo)
            return false;
	}
	return true;
}


vector<Node> selecionarEntregas(vector<Node> nos){
    vector<Node> entregas;
    for(int i=0; i<nos.size(); i++)
        if(nos[i].dem < 0)
            entregas.push_back(nos[i]);
    
    return entregas;
}

void ordenarNosPorJanelaDeTempo(vector<Node> nos){
	sort(nos.begin(), nos.end(), nodePriorityByTimeWindow);

	for(auto i=0; i<nos.size(); i++)
		nos[i].mostrarCampos();
}


bool existirVerticesNaoVisitados(vector<Node> &nos){
    for(int i=0; i<nos.size(); i++)
        if(!nos[i].visitado)
            return true;
    return false;
}

void criarSolucao(vector<Veiculo> &veiculos, vector<Node> &nos, int** MA, Instancia instancia, Pacote* pacotes){
    int m = 0;

    vector<Node> pontosEntrega = selecionarEntregas(nos);
    sort(pontosEntrega.begin(), pontosEntrega.end(), nodePriorityByTimeWindow);

    while(existirVerticesNaoVisitados(pontosEntrega)){
        Veiculo veiculo = Veiculo(m++);

        vector<int> rotaAux = veiculo.rota;
        for(int i=0; i<pontosEntrega.size(); i++){
            if(!pontosEntrega[i].visitado){
                rotaAux.push_back(nos[pontosEntrega[i].p].id);
                rotaAux.push_back(pontosEntrega[i].id);
                rotaAux.push_back(0);
                if(verificarRota(instancia, nos, MA, rotaAux, pacotes)){
                    rotaAux.pop_back();
                    pontosEntrega[i].visitado = true;
                    veiculo.rota = rotaAux;
                }
                else{
                    pontosEntrega[i].visitado = false;
                    rotaAux = veiculo.rota;
                }
            }
        }

        veiculo.rota.push_back(0);
        veiculos.push_back(veiculo);
    }
}


int main(){

	Instancia instancia;
	vector<Node> nos;
	int** MA;
	vector<Veiculo> veiculos;
	Pacote *pacotes;

	string nomeArq;
	// cout << "Digite o nome da instancia (sem a extensao): ";
	// cin >> nomeArq;
	nomeArq = "instances/nyc-n2000-4.txt";

	lerArquivo(nomeArq, instancia, nos, MA);

    criarSolucao(veiculos, nos, MA, instancia, pacotes);

    for(int i=0; i<veiculos.size(); i++){
        cout << i << ";";
        for(int j=0; j<veiculos[i].rota.size(); j++){
            cout <<  veiculos[i].rota[j] << ",";
        }
        cout << endl;
    }



	delete pacotes;
	for(int i=0; i<instancia.size; i++)
		delete MA[i];
	delete MA;

	return 0;
}