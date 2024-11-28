#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <ctime>
#include "header.hpp"

using namespace std;

// le o arquivo selecionado e instancia todas as estruturas de dados
bool lerArquivo(string nomeArq, Instancia &instancia, Node* &nos, int** &MA){
	ifstream txt(nomeArq);

	if(txt){
		string str, str2;
		int campo = 0;
		
		txt >> str;
		// define os dados da instancia
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
		
		// define os dados dos pontos/nós
		nos = new Node[instancia.size];

		for(int i=0; i<instancia.size; i++){
			txt >> str;
			nos[i].id = stoi(str);
			txt >> str;
			nos[i].lat = stof(str);
			txt >> str;
			nos[i].lon = stof(str);
			txt >> str;
			nos[i].dem = stoi(str);
			txt >> str;
			nos[i].etw = stoi(str);
			txt >> str;
			nos[i].ltw = stoi(str);
			txt >> str;
			nos[i].dur = stoi(str);
			txt >> str;
			nos[i].p = stoi(str);
			txt >> str;
			nos[i].d = stoi(str);
		}
		

		// define a matriz de adjacencias com os pesos
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

// define os pacotes com seus pontos de coleta e entrega
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

// gera uma solução totalmente aleatoria para o problema
void gerarSolucaoAleatoria(Instancia &instancia, Veiculo* &veiculos){
    unsigned seed = time(0);

    srand(seed);

	int nVeiculos = 10; // começar com apenas 10 veiculos
	instancia.nVeiculos = nVeiculos;
	veiculos = new Veiculo[nVeiculos];

	for(int i=0; i<nVeiculos; i++){
		veiculos[i].id = i;
		veiculos[i].nPontos = instancia.size/instancia.nVeiculos; // define o numero de pontos que o veiculo vai visitar
		veiculos[i].rota = new int[veiculos[i].nPontos];
		veiculos[i].rota[0] = 0;
		// gera aleatoriamente os pontos que cada veiculo vai visitar 0 -> 1 -> 2 -> ... -> nPontos
		// nessa forma os pontos podem se repetir
		// todos os veiculos tem origem e destino no ponto 0
		for(int j=1; j<veiculos[i].nPontos-1; j++){
			veiculos[i].rota[j] = rand()%instancia.size;
		}
		veiculos[i].rota[veiculos[i].nPontos-1] = 0;
		veiculos[i].carga = 0;
	}

}

// verifica apenas se uma solucao é valida, não se é a melhor solucao
bool verificarSolucao(Instancia instancia, Node* nos, int** MA, Veiculo* veiculos, Pacote* pacotes){
	/*
	*** Fazer com que todos os veiculos se desloquem ao mesmo tempo
		Nao conseguimos implementar por falta de tempo
	*/

	bool retorno = true;

	for(int k=0; k<instancia.nVeiculos; k++){
		Veiculo veiculoAtual = veiculos[k]; // verifica um veiculo de cada vez
		int tempo = 0; // 

		for(int i=1; i<veiculoAtual.nPontos; i++){
			int pAtual = veiculoAtual.rota[i];
			int pAnterior = veiculoAtual.rota[i-1];

			Node pontoAtual = nos[veiculoAtual.rota[i]];
			Pacote pacote = pacotes[pontoAtual.idPacote];

			// tempo de rota atual
			tempo += MA[pAnterior][pAtual];

			// se o ponto atual estiver "funcionando" (ou "aberto")
			if(pontoAtual.etw > tempo and tempo < pontoAtual.ltw){

				// se for um ponto de coleta e o pacote nao foi coletado e a carga do veiculo do veiculo for menor que a capacidade
				if(pontoAtual.dem > 0 and !pacote.coletado and veiculoAtual.carga < instancia.capacity){
					pacote.coletado = true;
					pacote.idVeiculo = veiculoAtual.id;
					veiculoAtual.carga += pontoAtual.dem;
				}
				
				// se for um ponto de entrega e o pacote referente a esse ponto foi coletado e nao foi entregue
				// e o veiculo atual for o veiculo que coletou o pacote
				if(pontoAtual.dem < 0 and pacote.coletado and !pacote.entregue and pacote.idVeiculo == veiculoAtual.id){
					pacote.entregue = true;
					veiculoAtual.carga += pontoAtual.dem;
				}
			}


			// soma no tempo total o tempo de espera. E se for só passagem???? nao implementado ainda
			// o veiculo nao fica parado esperando o local abrir nessa verificacao, ele passa direto como se fosse apenas passagem
		}
		// se o tempo ultrapassar o tempo limite (para cada veiculo)
		if(tempo > instancia.routeTime){
			retorno = false;
		}
	}

	// se algum dos pacotes nao for entregue (baseado em todas as restricoes calculadas acima)
	for(int i=0; i<instancia.nPacotes; i++){
		if(!pacotes[i].entregue)
			retorno = false;
	}

	return retorno;
}


int main(){
	Instancia instancia;
	Node* nos;
	int** MA;
	Veiculo *veiculos;
	Pacote *pacotes;

	string nomeArq;
	cout << "Digite o nome da instancia (sem a extensao): ";
	cin >> nomeArq;
	nomeArq = "instances/" + nomeArq + ".txt";

	lerArquivo(nomeArq, instancia, nos, MA);

	definirPacotes(pacotes, instancia, nos);

	gerarSolucaoAleatoria(instancia, veiculos);

	bool solucao = verificarSolucao(instancia, nos, MA, veiculos, pacotes);

	if(solucao)
		cout << "A solucao e valida" << endl;
	else
		cout << "A solucao e invalida" << endl;

	// deletar vetores alocados dinamicamente
	delete pacotes;
	for(int i=0; i<instancia.nVeiculos; i++)
		delete veiculos[i].rota;
	delete veiculos;
	delete nos;
	for(int i=0; i<instancia.size; i++)
		delete MA[i];
	delete MA;

	return 0;
}