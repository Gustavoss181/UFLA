#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "header.hpp"
using namespace MeuCabecalho;
using namespace std;

int main(){
	ifstream csv("data_athlete_event.csv");
	ofstream bin("data_athlete_event.bin");
	// ifstream csv("teste2.csv");
	// ofstream bin("teste.bin");
	
	if(csv){
		string str;
		char a;
		int campo = 0;
		bool aspasDuplas = true;
		AthleteEvent linha;

		getline(csv, str);//ignorar a primeira linha
		str = "";
		
		while(csv.get(a)){
			if(a == '"')
				aspasDuplas = !aspasDuplas;
			
			if((a == ',' or (a == '\n' and campo == 5)) and aspasDuplas){
				switch(campo + 1){
					case 1:
						linha.id = stoi(str);
						break;
					case 2:
						strcpy(linha.name, str.c_str());
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
						bin.write((const char *) (&linha), sizeof(AthleteEvent));
					default:
						break;
				}
				str = "";
				campo = (campo+1)%6;
			}
			else if(a != ' ' or str != "")
				str += a;
		}

		cout << "Encerrou" << endl;
		
		bin.close();
		csv.close();
	}

    return 0;
}
