/*
TENHA CERTEZA DE QUE O ARQUIVO csvToBin.cpp FOI COMPILADO E EXECUTADO E QUE O ARQUIVO data_athlete_event.bin FOI GERADO PARA UM CORRETO FUNCIONAMENTO DO PROGRAMA
*/
#include "header.hpp"
#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;

int nElementos(ifstream &bin){//retorna a quantidade de registros do arquivo
	bin.seekg(0, ios::end);
	return bin.tellg()/sizeof(AthleteEvent);
}


int nElementos(fstream &bin){//sobrecarga da função nElementos mas para fstream
	bin.seekg(0, ios::end);
	return bin.tellg()/sizeof(AthleteEvent);
}

int nElementos(){//sobrecarga da função nElementos quando o arquivo não foi aberto (main) 
	ifstream bin(FILENAME);
	if(bin){
		bin.seekg(0, ios::end);
		int tam = bin.tellg()/sizeof(AthleteEvent);
		bin.close();
		return tam;
	}
	else	
		return 0;
}

void limitarEntrada(char vetor[], int tam){//limita q a entrada passe de um numero de caracteres
	string aux;
	getline(cin, aux);
	while((int)aux.length() > tam){
		cout << "Ultrapassou o tamanho de " << tam << " caracteres." << endl;
		cout << "Digite novamente: ";
		getline(cin, aux);
	}
	strcpy(vetor, aux.c_str());
}

int limitarEntrada(int min, int max){//limita que a posição passada esteja dentro de um limite
	int aux;
	while(!(cin >> aux) or aux < min or aux > max){
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Digite um valor valido: ";
	}
	return aux;
}


AthleteEvent novoElemento(int id){//função separada para recebimento de novo elemento
	AthleteEvent novo;
	
	cout << "Novo elemento:" << endl;
	
	novo.id = id;
	cout << "Id: " << novo.id << endl;
	
	cin.ignore(100, '\n');
	cout << "Nome: ";
	limitarEntrada(novo.name, 100);
	cout << "Cidade: ";
	limitarEntrada(novo.city, 100);
	cout << "Esporte: ";
	limitarEntrada(novo.sport, 100);
	cout << "Evento: ";
	limitarEntrada(novo.event, 100);
	cout << "NOC: ";
	limitarEntrada(novo.NOC, 3);
	
	return novo;
}

//início das funções pricipais

void imprimirNumRange(int ini, int fim){//imprime de uma posição inicial até uma posição final
	ifstream bin(FILENAME);
	
	if(bin){
		//lidando com inputs incorretos
		if(ini < 0) ini = 0;
		int tam = nElementos(bin)-1;
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


void imprimirTudo(){//imprime, do início do arquivo até o final dele, todos os elementos
	ifstream bin(FILENAME);
	bin.seekg(0, bin.beg);
	if(bin){
		AthleteEvent linha;
		
		while(bin.read((char *) (&linha), sizeof(AthleteEvent))){
			linha.mostrarCampos();
		}
		
		bin.close();
	}
}


void adicionar(int pos){//adiciona um novo elemento numa posição desejada
	fstream bin;
	bin.open(FILENAME, ios::binary | ios::out | ios::in);
	if(bin){
		AthleteEvent novo = novoElemento(nElementos(bin));
		AthleteEvent aux;
		
		//Os elementos, um a um, são duplicados do final para o início.
		//Na prática eles são movidos uma posição para frente no arquivo
		cout << "inserindo..." << endl;
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


void inverter(int pos1, int pos2){//troca as posições entre dois elementos
	fstream bin;
	bin.open(FILENAME, ios::binary | ios::out | ios::in);
	
	if(bin){
		// Utilizamos 2 registros como auxiliares na inversão
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
	int opcao;

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

		while(!(cin >> opcao)){
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Digite um numero inteiro: ";
		}
		switch (opcao) {
			case 1:
				cout << "Passe a posicao onde quer inserir o dado: ";
				int posicao;
				posicao = limitarEntrada(0, nElementos());
				adicionar(posicao);
				break;

			case 2:
				cout << "Passe a posicao onde quer alterar: ";
				int pos;
				pos = limitarEntrada(0, nElementos());
				alterar(pos);
				break;

			case 3:
				int posicao1, posicao2;
				cout << "Passe as posicoes que quer inverter: ";
				posicao1 = limitarEntrada(0, nElementos());
				posicao2 = limitarEntrada(0, nElementos());
				inverter(posicao1, posicao2);
				break;

			case 4:
				imprimirTudo();
				break;

			case 5:
				int inicio, fim;
				cout << "Passe a posicao inicial: ";
				inicio = limitarEntrada(0, nElementos()-1);
				cout << "Passe a posicao final: ";
				fim = limitarEntrada(inicio, nElementos());
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
