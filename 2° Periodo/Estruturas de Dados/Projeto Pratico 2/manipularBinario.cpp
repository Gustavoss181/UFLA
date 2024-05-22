#include "header.hpp"
#include <fstream>
#include <iostream>
using namespace std;

//início das funções pricipais


int nElementos(ifstream &bin){////retorna a qntd de registros do arquivo
	bin.seekg(0, ios::end);
	return bin.tellg()/sizeof(AthleteEvent);
}


int nElementos(fstream &bin){//sobrecarga da função nElementos mas para fstream
	bin.seekg(0, ios::end);
	return bin.tellg()/sizeof(AthleteEvent);
}


AthleteEvent novoElemento(int id){//função separada para recebimento de novo elemento
	AthleteEvent novo;
	
	novo.id = id;
	cout << "Id: " << novo.id << endl;
	
	cout << "Insira os valores " << endl;
	
	cout << "Nome: ";
	cin >> novo.name;
	cout << "Cidade: ";
	cin >> novo.city;
	cout << "Esporte: ";
	cin >> novo.sport;
	cout << "Evento: ";
	cin >> novo.event;
	cout << "NOC: ";
	cin >> novo.NOC;
	
	return novo;
}


void imprimirNumRange(int ini, int fim){
	ifstream bin(FILENAME);
	
	if(bin){
		//lidando com inputs incorretos
		if(ini < 0) ini = 0;//.
		int tam = nElementos(bin)-1;//.
		if(fim > tam) fim = tam;
		
		bin.seekg(ini * sizeof(AthleteEvent), ios::beg);
			AthleteEvent linha;

		for(int i=0; i<fim-ini+1; i++){
			bin.read((char *) (&linha), sizeof(AthleteEvent));
			linha.mostrarCampos();
		}
		
		bin.close();
	}
}


void imprimirTudo(){
	ifstream bin(FILENAME);
	bin.seekg(0, ios::beg);
	if(bin){
		AthleteEvent linha;
		
		while(bin.read((char *) (&linha), sizeof(AthleteEvent))){
			linha.mostrarCampos();
		}
		bin.close();
	}
}


void adicionar(int pos){  
	fstream bin;
	bin.open(FILENAME, ios::binary | ios::out | ios::in);
	if(bin){
		AthleteEvent novo = novoElemento(nElementos(bin));
		AthleteEvent aux;
		
		//Os elementos, um a um, são duplicados do final para o início. Na prática eles são movidos uma posição para frente no arquivo
		for(int i=nElementos(bin)-1; i>=pos; i--){
			bin.seekg(i * sizeof(AthleteEvent), ios::beg);
			bin.read((char *) &aux, sizeof(AthleteEvent));
			bin.seekp((i+1) * sizeof(AthleteEvent), ios::beg);
			bin.write((const char *) &aux, sizeof(AthleteEvent));
		}
		//O novo elemento é adicionado na posição desejada
		bin.seekp(pos * sizeof(AthleteEvent), ios::beg);
		bin.write((const char *) (&novo), sizeof(AthleteEvent));
		bin.close();
	}
	cout << endl << "Os elementos antecessor e sucessor do novo elemento inserido:" << endl << endl;
	imprimirNumRange(pos-1, pos+1);
}


void alterar(int pos){//Sobreescrevemos todo o registro na posição desejada
	fstream bin;
	AthleteEvent novo;
	bin.open(FILENAME, ios::binary | ios::out | ios::in);
	
	if(bin){
		AthleteEvent aux;
		bin.seekg(pos * sizeof(AthleteEvent), ios::beg);
		bin.read((char *) &aux, sizeof(AthleteEvent));
		
		novo = novoElemento(aux.id);
		bin.seekp(pos*sizeof(AthleteEvent), ios::beg);
		bin.write((const char *) (&novo), sizeof(AthleteEvent));
		
		bin.close();
	}
	cout << endl << "Os elementos antecessor e sucessor do elemento alterado:" << endl << endl;
	imprimirNumRange(pos-1, pos+1);
}


void inverter(int pos1, int pos2){// Utilizamos dois registros como auxiliares na inversão
	fstream bin;
	bin.open(FILENAME, ios::binary | ios::out | ios::in);
	
	if(bin){		
		AthleteEvent elem1, elem2;
		
		bin.seekg(pos1 * sizeof(AthleteEvent), ios::beg);
		bin.read((char *) &elem1, sizeof(AthleteEvent));
	
		bin.seekg(pos2 * sizeof(AthleteEvent), ios::beg);
		bin.read((char *) &elem2, sizeof(AthleteEvent));
	
		bin.seekp(pos1 * sizeof(AthleteEvent), ios::beg);
		bin.write((const char *) &elem2, sizeof(AthleteEvent));
	
		bin.seekp(pos2 * sizeof(AthleteEvent), ios::beg);
		bin.write((const char *) &elem1, sizeof(AthleteEvent));
		
		bin.close();
	}
	cout << endl << "Os elementos antecessor e sucessor dos elementos invertidos:" << endl << endl;
	imprimirNumRange(pos1-1, pos1+1);
	cout << endl << "~ ~ ~ ~ ~ ~ ~ ~ ~ || ~ ~ ~ ~ ~ ~ ~ ~ ~ ~" << endl << endl;
	imprimirNumRange(pos2-1, pos2+1);
}


//fim das funções principais

void menu() {

	cout << "+-------------------------------+" << endl
		<< "| Escolha uma das opcoes:       |" << endl
		<< "| [1] Inserir                   |" << endl
		<< "| [2] Alterar                   |" << endl
		<< "| [3] Inverter                  |" << endl
		<< "| [4] Imprimir tudo             |" << endl
		<< "| [5] Imprimir apenas uma parte |" << endl
		<< "| [6] Sair                      |" << endl
		<< "+-------------------------------+" << endl;
}

int main() {
	int opcao, posicao1, posicao2;

	cout << "                   ,----,            \n"
		<< "                 ,/   .`|            \n"
		<< "  ,----..      ,`   .'  :   ,---,.   \n"
		<< " /   /   \\   ;    ;     / ,'  .'  \\ \n"
		<< "|   :     :.'___,/    ,',---.' .'  | \n"
		<< ".   |  ;. /|    :     | |   |  |:  | \n"
		<< ".   ; /--` ;    |.';  ; :   :  :  /  \n"
		<< ";   | ;    `----'  |  | :   |    ;   \n"
		<< "|   : |        '   :  ; |   :     \\ \n"
		<< ".   | '___     |   |  ' |   |   .  | \n"
		<< "'   ; : .'|    '   :  | '   :  ';  | \n"
		<< "'   | '/  :    ;   |.'  |   |  |   ; \n"
		<< "|   :    /     '---'    |   :     /  \n"
		<< " \\ \\   .'               |   |   ,'   \n"
		<< "  `---`                 `------'     \n";

	do {
		menu();
		cin >> opcao;

		switch (opcao) {
			case 1:
				cout << "Passe a posicao onde quer inserir o dado: ";
				cin >> posicao1;
				adicionar(posicao1);
				break;

			case 2:
				cout << "Passe a posicao onde quer alterar: ";
				cin >> posicao1;
				alterar(posicao1);
				break;

			case 3:
				cout << "Passe as posicoes que quer inverter: ";
				cin >> posicao1 >> posicao2;
				inverter(posicao1, posicao2);
				break;

			case 4:
				imprimirTudo();
				break;

			case 5:
				int inicio, fim;
				cout << "Passe a posicao inicial: ";
				cin >> inicio;
				cout << "Passe a posicao final: ";
				cin >> fim;
				imprimirNumRange(inicio, fim);
				break;

			case 6:
				cout << "Ate mais.. <0.->" << endl;
				break;

			default:
				cout << "Opcao incorreta, digite algo valido." << endl;
				break;
		}

	} while (opcao != 6);

	return 0;
}
