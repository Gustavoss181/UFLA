/*
    MaxHeap, para alteração de prioridade
    by joukim & bruno, 2019
*/

#include <iostream>
#include <utility> // para usar swap
#include <stdexcept> // para usar exceção com runtime_error

using namespace std;

struct dado {
    int prioridade;
    int valor;
};

bool operator>(dado d1, dado d2) {
    return d1.prioridade > d2.prioridade;
}

bool operator<(dado d1, dado d2) {
    return d1.prioridade < d2.prioridade;
}

ostream& operator<<(ostream& output,const dado& d) {
    output << "[" << d.valor << "/" << d.prioridade << "]"; 
    return output;
}

class MaxHeap {
private:
    dado* heap;
    int capacidade;
    int tamanho;
    inline int pai(int i);
    inline int esquerdo(int i);
    inline int direito(int i); 
    void corrigeDescendo(int i); 
    void corrigeSubindo(int i);
public:
    MaxHeap(int cap);
    ~MaxHeap();
    void imprime();
    dado retiraRaiz();
    void insere(dado d);
    void alteraPrioridade(int umValor, int novaPrioridade);
};

MaxHeap::MaxHeap(int cap) {
// implemente este método
	capacidade = cap;
	heap = new dado[capacidade];
	tamanho = 0;
}

MaxHeap::~MaxHeap() {
// implemente este método
	delete [] heap;
}

int MaxHeap::pai(int i) {
// implemente este método
	return (i-1)/2;
}
    
int MaxHeap::esquerdo(int i) {
// implemente este método
	return 2*i + 1;
}
    
int MaxHeap::direito(int i) {
// implemente este método
	return 2*i + 2;
}
    
void MaxHeap::corrigeDescendo(int i) {
// implemente este método
	int esq = esquerdo(i);
	int dir = direito(i);
	int maior = i;
	if(esq < tamanho and heap[esq] > heap[maior])
		maior = esq;
	if(dir < tamanho and heap[dir] > heap[maior])
		maior = dir;
	if(maior != i){
		swap(heap[i], heap[maior]);
		corrigeDescendo(maior);
	}
}

void MaxHeap::corrigeSubindo(int i) {
// implemente este método
	int p = pai(i);
	if(p >= 0 and heap[i] > heap[p]){
		swap(heap[i], heap[p]);
		corrigeSubindo(p);
	}
}
        
void MaxHeap::imprime() {
// implemente este método
	for(int i=0; i<tamanho; i++)
		cout << heap[i] << " ";
	cout << endl;
}

dado MaxHeap::retiraRaiz() {
// implemente este método
	if(tamanho < 1){
		dado erro;
		erro.valor = -1;
		erro.prioridade = -1;
		return erro;
	}
	dado aux = heap[0];
	swap(heap[0], heap[tamanho-1]);
	tamanho--;
	corrigeDescendo(0);
	return aux;
}


void MaxHeap::insere(dado d){
// implemente este método
	if(tamanho < capacidade){
		heap[tamanho] = d;
		corrigeSubindo(tamanho);
		tamanho++;
	}
}

void MaxHeap::alteraPrioridade(int umValor, int novaPrioridade) {
    // 1. primeira tarefa: encontrar o dado no vetor de dados
	int i=0;
	while(i < tamanho and umValor != heap[i].valor){
		i++;
	}
    // 2. segunda tarefa: altera prioridade do dado encontrado, 
    // armazenando prioridade antiga para comparação
	if(i < tamanho){
		heap[i].prioridade = novaPrioridade;
		// 3. terceira tarefa: sobe ou desce o dado, de acordo com 
		// a mudança de prioridade
		corrigeDescendo(i);
		corrigeSubindo(i);
	}
}

int main () {
    int capacidade;
    cin >> capacidade;
    MaxHeap meuHeap(capacidade);
   
    char opcao;
    cin >> opcao;
    
    dado umDado;
    int valor, novaPrioridade;

    while (opcao != 'Q') {
        switch(opcao) {
            case 'I':
                cin >> umDado.valor;
                cin >> umDado.prioridade;
                meuHeap.insere(umDado);
                break;
            case 'R':
                cout << meuHeap.retiraRaiz().valor << endl;
                break;
            case 'A':
                cin >> valor >> novaPrioridade;
                meuHeap.alteraPrioridade(valor,novaPrioridade); 
                break;               
            case 'P':
                meuHeap.imprime();
                break;
            default:
                cout << "Opção inválida!" << endl;
        }
        cin >> opcao;
    }
    
    return 0;
}