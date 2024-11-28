#include <iostream>

using namespace std;

class noh{
	friend class lista;
	friend class tabela_hash;
	private:
		int dado;
		int chave;
		noh* proximo;
		noh* anterior;
	public:
		noh(int d, int c);
};

noh::noh(int d, int c){
	dado = d;
	chave = c;
	proximo = NULL;
	anterior = NULL;
}

class lista{
	friend class tabela_hash;
	private:
		noh* primeiro;
		noh* ultimo;
		int tamanho;
	public:
		lista();
		~lista();
		void inserir(int valor, int chave);
		void removerNaPosicao(int posicao);
		int procurar(int chave);
		void imprimir();
		inline bool vazia();
};

lista::lista(){
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;
}

lista::~lista(){
	noh* aux = primeiro;
	noh* temp;
	
	while(aux != NULL){
		temp = aux;
		aux = aux->proximo;
		delete temp;
	}
	
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;
}

inline bool lista::vazia(){
	return (tamanho == 0);
}

void lista::imprimir(){
	noh* aux = primeiro;
	
	while(aux != NULL){
		cout << aux->dado << " " << aux->chave << " ";
		aux = aux->proximo;
	}
	
	cout << endl;
}

void lista::inserir(int valor, int chave){
	noh* novo = new noh(valor, chave);
	
	if(vazia()){
		primeiro = novo;
		ultimo = novo;
	}
	
	else{
		ultimo->proximo = novo;
		novo->anterior = ultimo;
		ultimo = novo;
	}
	
	tamanho++;
}

void lista::removerNaPosicao(int posicao){
	if(!vazia()){
		noh* aux = NULL;
		
		if((posicao < tamanho) and (posicao >= 0)){
			
			if(posicao == 0){
				aux = primeiro;
				
				primeiro = primeiro->proximo;
				if(primeiro != NULL)
					primeiro->anterior = NULL;
				delete aux;
			}
			
			else if(posicao == tamanho - 1){
				aux = ultimo;
				
				ultimo = ultimo->anterior;
				if(ultimo != NULL)
					ultimo->proximo = NULL;
				delete aux;
			}
			
			else{
				
				aux = primeiro;
				noh* antecessor = NULL;
				int posAux = 0;
				
				while(posAux < posicao){
					
					antecessor = aux;
					aux = aux->proximo;
					posAux++;
				}
				
				antecessor->proximo = aux->proximo;
				aux->proximo->anterior = antecessor;
				delete aux;
			}
			
			tamanho--;
		}
	}
}

int lista::procurar(int chave){
	
	noh* aux = primeiro;
	int posAux = 0;
	
	while((aux != NULL) and (aux->chave != chave)){
		posAux++;
		aux = aux->proximo;
	}
	
	if(aux == NULL)
		posAux = -1;
	
	return posAux;
}

class tabela_hash{
	private:
		int capacidade;
		int tamanho;
		lista* tabela;
		
	public:
		tabela_hash(int cap);
		~tabela_hash();
		int calcularHash(int chave);
		void inserirElemento(int valor, int chave);
		int recuperarValor(int chave);
		void alterarElemento(int chave, int novoValor);
		void removerElemento(int chave);
		void redimensionar(int novaCapacidade);
		void depuracao();
};

tabela_hash::tabela_hash(int cap){
	capacidade = cap;
	tamanho = 0;
	tabela = new lista[cap];
}

tabela_hash::~tabela_hash(){
	delete[] tabela;
}

int tabela_hash::calcularHash(int chave){
	return (chave % capacidade);
}

void tabela_hash::inserirElemento(int valor, int chave){
	if(tamanho == capacidade){
		cout << "hash cheio" << endl;
	}
	else{
		int posicao = calcularHash(chave);
		// ao criar um ponteiro a tabela[posicao] recebe as operações feitas com a variável list
		lista *list = &tabela[posicao];
		
		if(list->procurar(chave) == -1){
			// cria um elemento e o insere no final da lista
			list->inserir(valor, chave);
			
			tamanho++;
		}
		
		// neste programa não se permite dois elementos com a mesma chave
		else
			cout << "Item já na tabela!" << endl;
	}
}

int tabela_hash::recuperarValor(int chave){
	
	int posicao = calcularHash(chave);
	int posAux = tabela[posicao].procurar(chave);
	noh* aux;
	
	if(posAux == -1)
		return -1;
	
	else{
		
		aux = tabela[posicao].primeiro;
		
		for(int i = 0; i < posAux; i++)
			aux = aux->proximo;
			
		return aux->dado;
	}
}

void tabela_hash::alterarElemento(int chave, int novoValor){
	
	int posicao = calcularHash(chave);
	int posAux = tabela[posicao].procurar(chave);
	noh* aux;
	
	if(posAux == -1)
		cout << "Item não encontrado" << endl;
		
	else{
		
		aux = tabela[posicao].primeiro;
		
		for(int i = 0; i < posAux; i++)
			aux = aux->proximo;
			
		aux->dado = novoValor;
		
		cout << "Item alterado com sucesso" << endl;
	}
}

void tabela_hash::removerElemento(int chave){
	
	if(tamanho == 0)
		cout << "hash vazio" << endl;
		
	else{
		
		int posicao = calcularHash(chave);
		int posAux = tabela[posicao].procurar(chave);
		lista *list = &tabela[posicao];
		
		if(posAux == -1)
			cout << "Item não encontrado" << endl;
			
		else{
			
			list->removerNaPosicao(posAux);
			
			tamanho--;
			
			cout << "Item removido com sucesso" << endl;
		}
	}
}

void tabela_hash::redimensionar(int novaCapacidade){
	
	if(novaCapacidade <= capacidade)
		cout << "erro de redimensionamento" << endl;
		
	else{
		
		lista* tabelaAux = new lista[novaCapacidade];
		noh* aux;
		
		int novaPos;
		
		for(int i = 0; i < capacidade; i++){
			
			if(tabela[i].primeiro != NULL){
				
				aux = tabela[i].primeiro;
				
				while(aux != NULL){
					
					novaPos = aux->chave % novaCapacidade;
					
					tabelaAux[novaPos].inserir(aux->dado, aux->chave);
					
					aux = aux->proximo;
				}
			}
		}
		
		capacidade = novaCapacidade;
		
		delete[] tabela;
		
		tabela = tabelaAux;
	}
}

void tabela_hash::depuracao(){
	
	for(int i = 0; i < capacidade; i++){
		
		cout << i << ": ";
		tabela[i].imprimir();
	}
}

int main(){
	
	int quant;
	cout << "capacidade da tabela hash por encadeamento: " << flush;
	cin >> quant;
	
	tabela_hash hash(quant);
	int valor, chave;
	
	char opcao;
	
	do{
		
		cout << "digite uma opcao (i, n, b, a, r ou d): " << flush;
		
		cin >> opcao;
		
		switch(opcao){
			
			case 'i':
				cout << "preencha no padrão: valor chave" << endl;
				cin >> valor >> chave;
				
				hash.inserirElemento(valor, chave);
				break;
				
			case 'n':
				cout << "digita a nova capacidade: " << flush;
				cin >> quant;
				
				hash.redimensionar(quant);
				break;
				
			case 'b':
				cout << "insira uma chave para buscar: " << flush;
				cin >> chave;
				
				valor = hash.recuperarValor(chave);
				
				if(valor == -1)
					cout << "Item não encontrado" << endl;
					
				else
					cout << valor << endl;
				break;
				
			case 'a':
				cout << "insira a chave no qual se deseja mudar o valor: " << flush;
				cin >> chave;
				cout << "insira o novo valor: " << flush;
				cin >> valor;
				
				hash.alterarElemento(chave, valor);
				break;
				
			case 'r':
				cout << "insira a chave no qual se deseja apagar: " << flush;
				cin >> chave;
				
				hash.removerElemento(chave);
				break;
				
			case 'd':
				hash.depuracao();
				break;
		}
		
	}while(opcao != 's');
	
	return 0;
}
