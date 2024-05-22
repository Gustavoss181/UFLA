#include <iostream>
#include <fstream>
using namespace std;

int main(){
	string nome_arquivo;
	cin >>nome_arquivo;
	ifstream arquivo(nome_arquivo);
	if(arquivo) {
		
		string texto;
		arquivo>>texto;
		cout<<texto<<endl;
		arquivo.close();
	}
	else 
		cout<<"arquivo nao encontrado"<<endl;
	
	
	
	return 0;
}