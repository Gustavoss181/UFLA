#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;
//pode usar biblioteca string para converter valores
//pode usar continue
//tamanho fixo pra um vetor
//armazena quebra de linha
//sempre vai ter um espaço depois do ;

struct Celula{
	float campo1;
	int campo2;
	char campo3[120];
	float campo4;
	char campo5[120];
	int campo6; 
};

int main(){
	ifstream csv("arq.csv");
	ofstream arq("teste.bin");
	
	if(csv){
		string str = "";
		char a;
		int campo = 0;
		bool aspasDuplas = true;
		bool aspasSimples = true;
		Celula teste;
		
		while(csv.get(a)){
			if(a == '"' and aspasSimples)
				aspasDuplas = !aspasDuplas;
			if(a == '\'' and aspasDuplas)
				aspasSimples = !aspasSimples;
			
			if((a == ';' or (a == '\n' and campo == 5)) and aspasDuplas and aspasSimples){
				switch(campo + 1){
					case 1:
						teste.campo1 = stof(str);
						break;
					case 2:
						teste.campo2 = stoi(str);
						break;
					case 3:
						strcpy(teste.campo3, str.c_str());
						break;
					case 4:
						teste.campo4 = stof(str);
						break;
					case 5:
						strcpy(teste.campo5, str.c_str());
						break;
					case 6:
						teste.campo6 = stoi(str);
						arq.write((const char *) (&teste), sizeof(Celula));
					default:
						break;
				}
				str = "";
				campo = (campo+1)%6;
			}
			else if(a != ' ' or str != "")
				str += a;
		}
		
		arq.close();
		csv.close();
	}
	
	ifstream arq2("teste.bin");
	
	if(arq2){
		arq2.seekg(0, arq2.end);
		int tamArq = arq2.tellg();
		arq2.seekg(0, arq2.beg);

		int tam = tamArq/sizeof(Celula);
		Celula teste[tam];
		arq2.read((char *) (&teste), tamArq);
		for(int i=0; i<tam; i++){
			cout << teste[i].campo1 << endl;
			cout << teste[i].campo2 << endl;
			cout << teste[i].campo3 << endl;
			cout << teste[i].campo4 << endl;
			cout << teste[i].campo5 << endl;
			cout << teste[i].campo6 << endl;
			cout << "- - - - - - - - - - - - " << endl;
		}
		arq2.close();
	}
    
    return 0;
}