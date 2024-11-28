#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
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

void definirPacotes(Pacote* &pacotes, Instancia &instancia, vector<Node> &nos){
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


bool verificarRota(Instancia instancia, vector<Node> nos, int** MA, vector<int> rota, Pacote *pacotes){ // verifica uma rota gerada para um veiculo
    Veiculo aux = Veiculo(0);
    aux.rota = rota;

	int tempo = 0;

	for(unsigned int i=1; i<rota.size(); i++){
		int pAtual = rota[i];
		Node pontoAtual = nos[pAtual];
		Pacote pacote = pacotes[pontoAtual.idPacote];

		// tempo de rota atual
		int pAnterior = rota[i-1];
		tempo += MA[pAnterior][pAtual];


        if(pontoAtual.ltw < tempo){ // retorna rota invalida se o ponto visitado já foi fechado
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

        if(aux.carga > instancia.capacity) // retorna rota invalida se a capacidade passou do limite
            return false;
        
        if(instancia.routeTime < tempo) // retorna rota invalida se o tempo da rota ultrapassou o tempo máximo estabelecido
            return false;
	}
	return true;
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

void criarSolucao(vector<Veiculo> &veiculos, vector<Node> &nos, int** MA, Instancia instancia, Pacote* pacotes){ // cria a solução com uma frota de veículos
    int m = 0;

    vector<Node> pontosEntrega = selecionarEntregas(nos); // seleciona apenas os pontos de entrega
    sort(pontosEntrega.begin(), pontosEntrega.end(), nodePriorityByTimeWindow); // ordena esses pontos por janela de tempo

    while(existirVerticesNaoVisitados(pontosEntrega)){ // caso exista algum vertice não visitado o loop continua, criando um novo veículo
        Veiculo veiculo = Veiculo(m++);

        vector<int> rotaAux = veiculo.rota; // cria uma rota auxiliar para fazer o teste se é uma rota válida
        for(unsigned int i=0; i<pontosEntrega.size(); i++){
            if(!pontosEntrega[i].visitado){
                rotaAux.push_back(nos[pontosEntrega[i].p].id);
                rotaAux.push_back(pontosEntrega[i].id); // se o ponto de entrega não foi visitado ele é add na rota com o seu respectivo ponto de coleta logo antes
                rotaAux.push_back(0);
                if(verificarRota(instancia, nos, MA, rotaAux, pacotes)){ // se a rota é válida então ela é armazenada como a rota oficial do veículo
                    rotaAux.pop_back();
                    pontosEntrega[i].visitado = true;
                    veiculo.rota = rotaAux;
					pacotes[nos[pontosEntrega[i].p].idPacote].idVeiculo = veiculo.id;
					pacotes[pontosEntrega[i].idPacote].idVeiculo = veiculo.id;
                }
                else{ // caso não seja válida é escrita a rota anterior (que é válida) narota auxiliar e testa para o próximo ponto no vetor de pontos de entrega
                    pontosEntrega[i].visitado = false;
                    rotaAux = veiculo.rota;
                }
            }
        }

        veiculo.rota.push_back(0);
        veiculos.push_back(veiculo); // ao encerrar o loop o veículo é add na frota da solução final
    }
}


// --------------------------------------------------Solucao Macro3----------------------------------------------------------


void gerarArquivoCadaInstancia(string instancia, vector<Node> nos, Pacote *pacotes, vector<Veiculo> veiculos){
	string nome = "pontos/solucao-" + instancia + ".csv";
	cout << nome << endl;
	ofstream pontos(nome);

	if(pontos){
		pontos << "id,lat,lon,tipo,idVeiculo,pAnte,pProx" << endl;
		pontos << nos[0].id << "," 
			   << nos[0].lat << ","
			   << nos[0].lon << ","
			   << "deposito" << ","
			   << "-1" << ","
			   << "-1" << ","
			   << "-1" << endl;
		for(int i=0; i<veiculos.size(); i++){
			vector<int> rota = veiculos[i].rota;
			for(int j=0; j<rota.size(); j++){
				if(rota[j] != 0){
					string tipo;
					if(nos[rota[j]].dem > 0)
						tipo = "coleta";
					else if(nos[rota[j]].dem < 0)
						tipo = "entrega";
					
					pontos << nos[rota[j]].id << "," 
						   << nos[rota[j]].lat << ","
						   << nos[rota[j]].lon << ","
						   << tipo << ","
						   << pacotes[nos[rota[j]].idPacote].idVeiculo << ","
						   << nos[rota[j-1]].id << ","
						   << nos[rota[j+1]].id << endl;
				}
			}
		}

		pontos.close();
	}
	else{
		cout << "arquivo falhou" << endl; 
	}
}


int calcularCusto(vector<Veiculo> veiculos, int** MA){
	int total = 0;
	
	for(int i=0; i<veiculos.size(); i++){
		for(int j=1; j<veiculos[i].rota.size(); j++){
			total += MA[veiculos[i].rota[j-1]][veiculos[i].rota[j]];
		}
	}

	return total;
}


void gerarArquivosSaida(ifstream &instancias, ofstream &nCaminhoes){
//void gerarArquivosSaida(){

	string nomesInstancias[] = {"bar-n100-1", "bar-n100-2", "ber-n100-3", "ber-n100-4", "nyc-n100-4", "nyc-n100-5", "poa-n100-1", "poa-n100-2", "poa-n100-6", "poa-n100-7", "bar-n200-1", "bar-n200-2", "bar-n200-3", "bar-n200-4", 
		"ber-n200-5", "ber-n200-6", "nyc-n200-3", "nyc-n200-4", "poa-n200-1", "poa-n200-2", "bar-n400-1", "ber-n600-1", "nyc-n800-3", "poa-n1000-1", "poa-n1500-6", "nyc-n2000-4", "ber-n2500-3", "bar-n3000-6", "poa-n4000-2", "poa-n5000-3"};
	
	string linha;
	instancias >> linha;
	nCaminhoes << linha << "," << "nVeiculosS" << "," << "custoTotalS" << endl;


	for(int i=0; i<30; i++){
		Instancia instancia;
		vector<Node> nos;
		int** MA;
		vector<Veiculo> veiculos;
		Pacote *pacotes;

		string nomeArq = nomesInstancias[i];
		nomeArq = "instances/" + nomeArq + ".txt";
		lerArquivo(nomeArq, instancia, nos, MA);
		definirPacotes(pacotes, instancia, nos);
    	criarSolucao(veiculos, nos, MA, instancia, pacotes);

		for(unsigned int i=0; i<veiculos.size(); i++){
			veiculos[i].mostrarRota();
		}

		instancias >> linha;
		nCaminhoes << linha << "," << veiculos.size() << "," << calcularCusto(veiculos, MA) << endl;

		gerarArquivoCadaInstancia(nomesInstancias[i], nos, pacotes, veiculos);

		delete pacotes;
		for(int i=0; i<instancia.size; i++)
			delete MA[i];
		delete MA;
	}
}

int main(){
	ifstream arqInstancias("valoresInstancias.csv");
	ofstream nCaminhoes("dadosInstancias.csv");

	if(arqInstancias and nCaminhoes){
		gerarArquivosSaida(arqInstancias, nCaminhoes);

		nCaminhoes.close();
		arqInstancias.close();
	}

	// gerarArquivosSaida();

	return 0;
}