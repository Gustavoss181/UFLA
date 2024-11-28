#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <ctime>
#include "header.hpp"

using namespace std;

bool lerArquivo(string nomeArq, Instancia &instancia, Node* &nos, int** &MA){
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

void gerarSolucaoAleatoria(Instancia &instancia, Veiculo* &veiculos){
    unsigned seed = time(0);

    srand(seed);

	int nVeiculos = 10; // começar com apenas 10 veiculos
	instancia.nVeiculos = nVeiculos;
	veiculos = new Veiculo[nVeiculos];

	for(int i=0; i<nVeiculos; i++){
		veiculos[i].id = i; // inutil?
		veiculos[i].nPontos = instancia.size/instancia.nVeiculos;
		veiculos[i].rota = new int[veiculos[i].nPontos];
		veiculos[i].rota[0] = 0;
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
	Nao conseguimos implementar por falta de tempo
	Fazer com que todos os veiculos se desloquem ao mesmo tempo
	*/

	bool retorno = true;

	for(int k=0; k<instancia.nVeiculos; k++){
		Veiculo veiculoAtual = veiculos[k];
		int tempo = 0; // 

		for(int i=1; i<veiculoAtual.nPontos; i++){
			int pAtual = veiculoAtual.rota[i];
			Node pontoAtual = nos[veiculoAtual.rota[i]];
			Pacote pacote = pacotes[pontoAtual.idPacote];

			// tempo de rota atual
			int pAnterior = veiculoAtual.rota[i-1];
			tempo += MA[pAnterior][pAtual];

			
			// se o no atual for uma entrega e o par dele de coleta não foi coletado retorna erro
			if(pontoAtual.etw > tempo and tempo < pontoAtual.ltw){ // se o ponto atual estiver "funcionando" (ou "aberto")

				if(pontoAtual.dem > 0 and !pacote.coletado){ // se for um ponto de coleta
					pacote.coletado = true;
					pacote.idVeiculo = veiculoAtual.id;
				}

				if(pontoAtual.dem < 0 and pacote.coletado and !pacote.entregue and pacote.idVeiculo == veiculoAtual.id){ // se for um ponto de entrega
					cout << "O pacote " << pacote.id << " foi entregue!" << endl;
					pacote.entregue = true;
				}
			}


			// soma no tempo total o tempo de espera. E se for só passagem???? nao implementado ainda
			// o veiculo nao fica parado esperando o local abrir nessa verificacao, ele passa direto como se fosse apenas passagem
		}
		if(tempo > instancia.routeTime){
			cout << "Tempo Excedido" << endl;
			cout << "Tempo ideal: " << instancia.routeTime << endl;
			cout << "Tempo gasto: " << tempo << endl;
			retorno = false;
		}
	}

	for(int i=0; i<instancia.nPacotes; i++){
		if(pacotes[i].entregue == 0){
			cout << "O pacote de id " << i << " nao foi entregue" << endl;
			retorno = false;
		}
	}

	return retorno;
}

/*
bool verifySolution(string solutionFileName) {

	// <vehicle>;<origin>,<destiny1>,<destiny2>,...,<destinyN>,<origin>
	ifstream file(solutionFileName+".txt");

	string id;

	while(getline(file, id, ';')) {
		int vehicleId = stoi(id);
		cout << "\n============== " << "Restrições(" << vehicleId << ")" << " ==============\n" << endl;
		Veiculo veiculo(vehicleId);
		M.push_back(veiculo);

		string route;
		getline(file, route);
		stringstream sst(route);

		string clientId;
		vector<int> sequence;

		while(getline(sst, clientId, ',')) {
			sequence.push_back(stoi(clientId));
		}

		cout << "Origem de serviço" << endl;
		// 2. Origem de serviço
		if (sequence[0] or sequence[sequence.size()-1])
			return false;


		for (int i = 0; i < sequence.size(); i++) {
			cout << "==== " << sequence[i] << " ====" << endl;
			Vertice *cliente = &searchById(sequence[i]);
			if (cliente->id != 0) { // Vértice não é o depósito
				cout << "Exclusividade de visita" << endl;
				// 4. Exclusividade de visita
				if (cliente->vehicleId != -1)
					return false;
				cliente->vehicleId = vehicleId;

				cout << "Atendimento de pedido e Precedência de coleta e entrega" << endl;
				// 5. Atendimento de pedido
				// 1. Precedência de coleta e entrega
				if (cliente->dem < 0) {
					Vertice coleta = searchById(cliente->p);
					if (cliente->vehicleId != coleta.vehicleId)
						return false;
				}
			}
			cout << "Janelas de tempo" << endl;
			// 3. Janelas de tempo
			if (M[vehicleId].t > cliente->timeWindow.second)
				return false;
			if (M[vehicleId].t < cliente->timeWindow.first)
				M[vehicleId].t += (cliente->timeWindow.first - M[vehicleId].t);
			int duracao = cliente->dur;
			int custo = 0;
			if (i < (sequence.size()-1)) {
				Aresta aresta = searchById(sequence[i], sequence[i+1]);
				custo = aresta.c;
			}

			cout << "Horário de serviço" << endl;
			// 2. Horário de serviço
			if ((M[vehicleId].t += duracao + custo) > ROUTE_TIME)
				return false;
			
			cout << "Capacidade do veículo" << endl;
			// 6. Capacidade do veículo
			if ((M[vehicleId].q += cliente->dem) > CAPACITY)
				return false;
		}

	}

	cout << "Obrigatoriedade de visita" << endl;
	// 4. Obrigatoriedade de visita
	for (int i = 0; i < V.size(); i++) {
		if (V[i].id != 0) {
			if (V[i].vehicleId == -1)
				return false;
		}
	}

	return true;

}
*/

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

	for(int i=0; i<100; i++){
		definirPacotes(pacotes, instancia, nos);

		gerarSolucaoAleatoria(instancia, veiculos);

		bool solucao = verificarSolucao(instancia, nos, MA, veiculos, pacotes);

		system("pause");
	}
	// if(solucao)
	// 	cout << "A solucao e valida" << endl;
	// else
	// 	cout << "A solucao e invalida" << endl;

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