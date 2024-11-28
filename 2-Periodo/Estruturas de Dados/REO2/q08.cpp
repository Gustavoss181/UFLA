#include<iostream>
using namespace std;

class Noh{
	friend class Fila;
	private:
		string dado;
		Noh *prox;
	public:
		Noh(string dado);
};

Noh::Noh(string dado){
	this->dado = dado;
	this->prox = NULL;
}

class Fila{
	private:
		Noh *inicio;
		Noh *fim;
		int tam;
	public:
		Fila();
		void inserir(string placa);
		void remover(string placa);
		void mostrarFila();
};

Fila::Fila(){
	inicio = NULL;
	fim = NULL;
	tam = 0;
}

void Fila::inserir(string placa){
	Noh *novo = new Noh(placa);
	if(tam == 0)
		inicio = novo;
	else
		fim->prox = novo;
	fim = novo;
	tam++;
}

void Fila::remover(string placa){
	bool encontrou = false;
	int cont = 0;
	while(!encontrou and cont < tam){
		encontrou = inicio->dado == placa;
		if(!encontrou){
			fim->prox = inicio;
			inicio = fim->prox->prox;
			fim = fim->prox;
			fim->prox = NULL;
		}
		cont++;
	}
	if(!encontrou){//se não encontrou
		cout << "NAO ENCONTRADO" << endl;
	}
	else{
		Noh *aux = inicio;
		inicio = aux->prox;
		delete aux;
		tam--;
		cout << cont << endl;
		mostrarFila();
	}
}

void Fila::mostrarFila(){
	Noh *aux = inicio;
	while(aux != NULL){
		cout << aux->dado << endl;
		aux = aux->prox;
	}
}

int main(){
	Fila fila;
	char opcao;
	cin >> opcao;
	while(opcao != 'S'){
		string placa;
		cin >> placa;
		if(opcao == 'E')
			fila.inserir(placa);
		else if(opcao == 'D')
			fila.remover(placa);
		
		cin >> opcao;
	}
	return 0;
}