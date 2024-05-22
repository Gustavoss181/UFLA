/*
É EXTREMAMENTE IMPORTANTE QUE ESSE ARQUIVO SEJA COMPILADO E EXECUTADO ANTES DE
EXECUTAR O ARQUIVO manipulaBinario.cpp PARA O CORRETO FUNCIONAMENTO DO PROGRAMA
*/
#include "header.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

//faz a conversão do arquivo csv para binario
bool csvToBin(){
	//abre o csv COM ESSE NOME para leitura
	ifstream csv("data_athlete_event.csv");
	ofstream bin(FILENAME);

	if (csv and bin) {
		string str;
		char a;
		int campo = 0;
		bool aspasDuplas = true;
		AthleteEvent linha;

		getline(csv, str); //ignora a primeira linha
		str = "";
		
		//o csv é lido caractere por caractere
		while (csv.get(a)) {
			//se o caractere for " o caractere , (separador dos campos) é ignorado
			if (a == '"')
				aspasDuplas = !aspasDuplas;

			//verifica se o caractere lido é o separador dos campos 
			if ((a == ',' or (a == '\n' and campo == 5)) and aspasDuplas) {
				switch (campo + 1) {
					case 1:
						linha.id = stoi(str);//converte string para inteiro
						break;
					case 2:
						strcpy(linha.name, str.c_str());//converte string para vetor de char
						break;
					case 3:
						strcpy(linha.city, str.c_str());
						break;
					case 4:
						strcpy(linha.sport, str.c_str());
						break;
					case 5:
						strcpy(linha.event, str.c_str());
						break;
					case 6:
						strcpy(linha.NOC, str.c_str());
						//quando é armazenado o último campo o registro é escrito no arquivo binário
						bin.write((const char *)(&linha), sizeof(AthleteEvent));
					default:
						break;
				}
				str = "";//a string é resetada depois de armazenar cada campo
				campo = (campo + 1) % 6;//campos de 0-5
			}
			else if (a != ' ' or str != "")
				str += a;//cada caractere é armazenado na string para fazer a conversão correta em cada campo
		}

		bin.close();
		csv.close();

		return true;
	}
	else
		return false;
}

int main() {
	cout << "Convertendo o arquivo de csv para binario..." << endl;
	if(csvToBin())
		cout << "Conversao encerrada" << endl;
	else
		cout << "Erro ao converter" << endl;
	
	return 0;
}
