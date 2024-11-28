#include<iostream>
using namespace std;

struct Produto{
	int id;
	string descricao;
	float preco;
};

void insertionSort(Produto v[], int t){
	for(int i=1; i<t; i++){
		Produto pivo = v[i];
		int j;
		for(j=i-1; j>=0 and v[j].preco>pivo.preco; j--)
			v[j+1] = v[j];
		v[j+1] = pivo;
	}
}

int main(){
	int tam;
	cin >> tam;
	Produto produtos[tam];
	for(int i=0; i<tam; i++){
		cin >> produtos[i].id;
		cin.ignore(2, '\n');
		getline(cin, produtos[i].descricao);
		cin >> produtos[i].preco;
	}

	insertionSort(produtos, tam);

	float min, max;
	cin >> min;
	cin >> max;
	
	for(int i=0; i<tam; i++)
		if(produtos[i].preco >= min and produtos[i].preco <= max){
			cout << produtos[i].id << " ";
			cout << '"' << produtos[i].descricao << '"' << " ";
			cout << produtos[i].preco << endl;
		}

	return 0;
}