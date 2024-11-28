#include<iostream>
using namespace std;

struct Meme{
	int num;
	string nome;
	string arq;
	string site;
};

void inserir(Meme v[], int tam){
	for(int i=0; i<tam; i++){
		cin >> v[i].num;
		cin >> v[i].nome;
		cin >> v[i].arq;
		cin >> v[i].site;
	}
}

void selectionSort(Meme v[], int t){
	for(int i=0; i<t-1; i++){
		int pMenor = i;
		for(int j=i+1; j<t; j++)
			if(v[pMenor].num > v[j].num)
				pMenor = j;
		Meme aux = v[pMenor];
		v[pMenor] = v[i];
		v[i] = aux;
	}
}

void mostrar(Meme v[], int t, string site){
	bool encontrou = false;
	for(int i=0; i<t; i++)
		if(v[i].site == site){
			cout << v[i].num << " ";
			cout << v[i].nome << " ";
			cout << v[i].arq << " ";
			cout << v[i].site << endl;
			encontrou = true;
		}
	if(!encontrou)
		cout << "Inexistente";
}

int main(){
	int tam;
	cin >> tam;
	Meme memes[tam];
	inserir(memes, tam);
	string site;
	cin >> site;

	selectionSort(memes, tam);

	mostrar(memes, tam, site);

	return 0;
}