#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
#include "header.hpp"

using namespace std;

bool lerArquivo(string nomeArq, Instancia &instancia, vector<Node> &nos, int** &MA){ // 
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

void definirPacotes(vector<Pacote> &pacotes, Instancia instancia, vector<Node> &nos){
	int idPacote = 0;
	for(int i=0; i<instancia.size; i++){
		if(nos[i].dem > 0){
			Pacote aux = Pacote(idPacote, nos[i].id, nos[nos[i].d].id);
			pacotes.push_back(aux);
			nos[i].idPacote = idPacote;
			nos[nos[i].d].idPacote = idPacote;
			idPacote++;
		}
	}
}


bool verificarRota(Instancia instancia, vector<Node> nos, int** MA, vector<int> rota, vector<Pacote> pacotes){ // verifica uma rota gerada para um veiculo
    Veiculo aux = Veiculo(0);
    aux.rota = rota;

	int tempo = 0;

	for(unsigned int i=1; i<rota.size(); i++){
		int pAtual = rota[i];
		Node pontoAtual = nos[pAtual];
		// Pacote pacote = pacotes[pontoAtual.idPacote];

		// tempo de rota atual
		int pAnterior = rota[i-1];
		tempo += MA[pAnterior][pAtual];


        if(pontoAtual.ltw < tempo){ // retorna rota invalida se o ponto visitado já foi fechado
            return false;
        }
		if(pontoAtual.etw > tempo)
            tempo += (pontoAtual.etw - tempo);

		// se o no atual for uma entrega e o par dele de coleta não foi coletado retorna erro
        // if(pontoAtual.dem > 0){ // se for um ponto de coleta
        //     pacote.coletado = true;
        // }
        // if(pontoAtual.dem < 0 and pacote.coletado){ // se for um ponto de entrega
        //     pacote.entregue = true;
        // }

        tempo += pontoAtual.dur;

        aux.carga += pontoAtual.dem;

        if(aux.carga > instancia.capacity) // retorna rota invalida se a capacidade passou do limite
            return false;
        
        if(instancia.routeTime < tempo) // retorna rota invalida se o tempo da rota ultrapassou o tempo máximo estabelecido
            return false;
	}
	return true;
}


int decidirProxPonto(Instancia instancia, vector<Node> nos, vector<Pacote> pacotes, int** MA, int pAtual, int tempo){
	int menor = INT_MAX;
	int idMenor = -1;
	for(int i=1; i<instancia.size; i++){
		Node pontoCandidato = nos[i];
		Pacote pacote = pacotes[pontoCandidato.idPacote];
		if(!pontoCandidato.visitado){
			if(tempo < pontoCandidato.ltw){
				if(!pacote.coletado){
					pacote.prioridade = MA[pAtual][pontoCandidato.id];
					pacote.prioridade += pontoCandidato.etw - tempo;
					//pacote.prioridade += pontoCandidato.ltw - pontoCandidato.etw - tempo;
				}
				else if(!pacote.entregue){
					pacote.prioridade = MA[pAtual][pontoCandidato.id];
					pacote.prioridade += pontoCandidato.etw - tempo;
					pacote.prioridade *= 1 - ((float)tempo)/instancia.routeTime;
				}
			}
			if(menor > pacote.prioridade){
				menor = pacote.prioridade;
				idMenor = pontoCandidato.id;
			}
		}
	}
	return idMenor;
}


vector<Node> selecionarEntregas(vector<Node> nos){ // seleciona apenas os pontos que são de entrega (dem < 0)
    vector<Node> entregas;
    for(unsigned int i=0; i<nos.size(); i++)
        if(nos[i].dem < 0)
            entregas.push_back(nos[i]);
    
    return entregas;
}

void ordenarNosPorJanelaDeTempo(vector<Node> nos){ // ordena os pontos (nesse caso de entrega) por janela de tempo (etw)
	sort(nos.begin(), nos.end(), nodePriorityByTimeWindow);

	for(unsigned int i=0; i<nos.size(); i++)
		nos[i].mostrarCampos();
}


bool existirVerticesNaoVisitados(vector<Node> &nos){ // verifica se todos os nós foram visitados, caso sim ele retorna falso para encerrar o loop
    for(unsigned int i=0; i<nos.size(); i++)
        if(!nos[i].visitado)
            return true;
    return false;
}

void criarSolucao(vector<Veiculo> &veiculos, vector<Node> &nos, int** MA, Instancia instancia, vector<Pacote> pacotes){ // cria a solução com uma frota de veículos
    int m = 0;

    while(existirVerticesNaoVisitados(nos)){ // caso exista algum vertice não visitado o loop continua, criando um novo veículo
        Veiculo veiculo = Veiculo(m++);

        vector<int> rotaAux = veiculo.rota; // cria uma rota auxiliar para fazer o teste se é uma rota válida
        while(veiculo.tempo < instancia.routeTime){
			int proxPonto = decidirProxPonto(instancia, nos, pacotes, MA, veiculo.rota.back(), veiculo.tempo);
			rotaAux.push_back(proxPonto);
			rotaAux.push_back(0);
			if(verificarRota(instancia, nos, MA, rotaAux, pacotes)){
				rotaAux.pop_back();
				nos[proxPonto].visitado = true;
				veiculo.tempo += MA[veiculo.rota.back()][proxPonto];
				veiculo.tempo += nos[proxPonto].dur;
				veiculo.carga += nos[proxPonto].dem; // ????????
				nos[proxPonto].dem > 0 ? pacotes[nos[proxPonto].idPacote].coletado = true : pacotes[nos[proxPonto].idPacote].entregue = true;
				veiculo.rota = rotaAux;
			}
			else{
				nos[proxPonto].visitado = false;
                rotaAux = veiculo.rota;
			}
		}

        veiculo.rota.push_back(0);
		veiculo.mostrarRota();
        veiculos.push_back(veiculo); // ao encerrar o loop o veículo é add na frota da solução final
    }
}


int main(){
	Instancia instancia;
	vector<Node> nos;
	int** MA;
	vector<Veiculo> veiculos;
	vector<Pacote> pacotes;

	string nomeArq;
	cout << "Digite o nome da instancia (sem a extensao): ";
	cin >> nomeArq;
	nomeArq = "instances/" + nomeArq + ".txt";

	lerArquivo(nomeArq, instancia, nos, MA);
	definirPacotes(pacotes, instancia, nos);

	// cout << decidirProxPonto(instancia, nos, pacotes, MA, 0, 0) << endl;

    criarSolucao(veiculos, nos, MA, instancia, pacotes);

    // for(unsigned int i=0; i<veiculos.size(); i++){
    //     veiculos[i].mostrarRota();
	// }

	for(int i=0; i<instancia.size; i++)
		delete MA[i];
	delete MA;

	return 0;
}