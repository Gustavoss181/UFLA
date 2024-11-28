#include <iostream>
#include <fstream>
using namespace std;

int main(){
	string nome;
	int pos;
	cin >> nome >> pos;
	ifstream ler(nome);
	
	int letras=0, palavras=0;
	if(ler){
		string palavra;
		while(ler >> palavra)
			palavras++;
		ler.close();
	}
	
	ifstream ler2(nome);
	if(ler2){
		char letra;
		while(ler2.get(letra)){
			if(letras == pos)
				cout << letra;
			letras++;
		}
		ler2.close();
	}
		
	ofstream escrever("resultado.txt");
	if(escrever)
		escrever << letras << " " << palavras;
	escrever.close();
	ler.close();
    
    return 0;
}