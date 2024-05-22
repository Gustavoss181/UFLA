#include "cabecalho.hpp"
#include <climits>
#include <fstream>
#include <iostream>

using namespace std;
using namespace MeuCabecalho;

int nElementos(ifstream &bin) { // retorna a quantidade de registros do arquivo
	bin.seekg(0, ios::end);
	return bin.tellg() / sizeof(AthleteEvent);
}

int nElementos() { // sobrecarga da função nElementos quando o arquivo não foi aberto (main)
  	ifstream bin(FILENAME);
  	if (bin) {
		bin.seekg(0, ios::end);
		int tam = bin.tellg() / sizeof(AthleteEvent);
		bin.close();
		return tam;
	} else
		return 0;
}

int limitarEntrada(int min, int max) { // limita que a posição passada esteja dentro de um limite
  	int aux;
 	while (!(cin >> aux) or aux < min or aux > max) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Digite um valor valido: ";
  	}
  	return aux;
}

void verificarOrdenacao() { //usada para testes para verificar se a ordenação ocorreu corretamente
	ifstream bin(FILENAME, ios::binary);

  	AthleteEvent a, b;
  	bool aux = true;

	bin.read((char *)(&a), sizeof(a));

  	while (bin.read((char *)(&b), sizeof(b)) and aux) {
		if (a < b)
	  		aux = false;
		
		a = b;
  	}

  	if (aux)
		cout << "Ordenacao foi um sucesso!" << endl;
	else
		cout << "Erro ao ordenar!" << endl;

  	bin.close();
}

void imprimirNumRange(int ini, int fim) { // imprime de uma posição inicial até uma posição final
  ifstream bin(FILENAME);

  if (bin) {
	// move o ponteiro de leitura até uma posição específica
	bin.seekg(ini * sizeof(AthleteEvent), ios::beg);
	AthleteEvent linha;

	for (int i = 0; i < fim - ini + 1; i++) {
	  bin.read((char *)(&linha), sizeof(AthleteEvent));
	  cout << linha;
	}

	bin.close();
  }
}

void imprimirTudo() { // imprime, do início do arquivo até o final dele, todos os elementos
  	ifstream bin(FILENAME);
  	if (bin) {
  		bin.seekg(0, bin.beg);
		AthleteEvent linha;

		while (bin.read((char *)(&linha), sizeof(AthleteEvent))) {
	  		cout << linha;
		}

		bin.close();
  	}
}

bool csvToBin() { // faz a conversão do arquivo csv para binario
	ofstream bin(FILENAME, ios::binary);
	// abre o csv COM ESSE NOME para leitura
	ifstream csv("data_athlete_event.csv");

	if (csv and bin) {
		string str;
		char a;
		int campo = 0;
		bool aspasDuplas = true;
		AthleteEvent linha;

		getline(csv, str); // ignora a primeira linha
		str = "";

		// o csv é lido caractere por caractere
		while (csv.get(a)) {
		// se o caractere for " o caractere , (separador dos campos) é ignorado
		if (a == '"')
			aspasDuplas = !aspasDuplas;

		// verifica se o caractere lido é o separador dos campos
		if ((a == ',' or (a == '\n' and campo == 5)) and aspasDuplas) {
			switch (campo + 1) {
			case 1:
			linha.id = stoi(str); // converte string para inteiro
			break;
			case 2:
			strcpy(linha.name, str.c_str()); // converte string para vetor de char
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
			// quando é armazenado o último campo o registro é escrito no arquivo
			// binário
			bin.write((const char *)(&linha), sizeof(AthleteEvent));
			default:
			break;
			}
			str = ""; // a string é resetada depois de armazenar cada campo
			campo = (campo + 1) % 6; // campos de 0-5
		} else if (a != ' ' or str != "")
			str += a; // cada caractere é armazenado na string para fazer a conversão correta em cada campo
		}

		csv.close();
		bin.close();

		return true;
	} else
		return false;
}

// inicia o código de ordenação

struct Noh { // o nó usado no maxheap
	AthleteEvent elemento; // o elemento armazenado
	int i; // o índice do vetor que ele foi tirado
};

void swap(Noh *x, Noh *y) { // função para troca de 2 nós
	Noh aux = *x;
	*x = *y;
	*y = aux;
}

class MaxHeap { // classe para o MaxHeap
	Noh *heap;
	int tamanho;

	public:
		MaxHeap(Noh a[], int tam);
		void heapify(int);
		int esq(int i) { return (2 * i + 1); } // posição do filho à esquerda
		int dir(int i) { return (2 * i + 2); } // posição do filho à direita
		Noh getMax() { return heap[0]; } // retorna a raiz
		void heapifyRaiz(Noh x) { // troca a raiz por um novo nó e chama heapify para o nova raiz
			heap[0] = x;
			heapify(0);
		}
};

MaxHeap::MaxHeap(Noh vetor[], int tam) { // construtor que cria um heap com o vetor de um certo tamanho
	tamanho = tam;
	heap = vetor;
	int i = (tamanho - 1) / 2;
	while (i >= 0) {
		heapify(i);
		i--;
	}
}

void MaxHeap::heapify(int i) { // método de heapify do heap
	int e = esq(i);
	int d = dir(i);
	int maior = i;
	if (e < tamanho and heap[e].elemento > heap[i].elemento)
		maior = e;
	if (d < tamanho and heap[d].elemento > heap[maior].elemento)
		maior = d;
	if (maior != i) {
		swap(&heap[i], &heap[maior]);
		heapify(maior);
	}
}

void merge(AthleteEvent vetor[], int e, int m, int d) { // método para fazer o merge em dois vetores
	int i, j, k;
	int n1 = m - e + 1;
	int n2 = d - m;

	// cria vetores temporários
	AthleteEvent E[n1], D[n2];

	// copia os dados para os dois vetores
	for (i = 0; i < n1; i++)
		E[i] = vetor[e + i];
	for (j = 0; j < n2; j++)
		D[j] = vetor[m + 1 + j];
	
	i = 0;
	j = 0;
	k = e;

	while((i < n1) and (j < n2)){
		if (E[i] >= D[j])
			vetor[k++] = E[i++];
		else
			vetor[k++] = D[j++];
	}

	//copia os elementos restantes para os vetores se tiver algum
	while (i < n1)
		vetor[k++] = E[i++];

	while (j < n2)
		vetor[k++] = D[j++];
}

void mergeSort(AthleteEvent vetor[], int e, int d) { // método de mergesort para um vetor
	if (e < d) {
		int m = e + (d - e) / 2;

		// ordena a primeira e depois a segunda metade
		mergeSort(vetor, e, m);
		mergeSort(vetor, m + 1, d);

		merge(vetor, e, m, d);
	}
}

void mergeArquivos(int nArquivos) { // método para juntar os arquivos que foram gerados anteriormente 
	// abre os arquivos nomeados de 0 à nArquivos em modo de leitura
	ifstream tempArq[nArquivos];
	for (int i = 0; i < nArquivos; i++)
		tempArq[i].open(to_string(i), ios::binary);

	// abre o arquivo original no modo de escrita
	ofstream bin(FILENAME, ios::binary);

	// cria um maxheap com nArquivos nós. Cada nó recebe o primeiro elemento de cada arquivo
	Noh *heap = new Noh[nArquivos];
	
	// lê primeiro elemento de cada arquivo e armazena no vetor para o heap
	int i = 0;
	while(i < nArquivos and tempArq[i].read((char *)(&heap[i].elemento), sizeof(heap[i].elemento))){
		heap[i].i = i;
		i++;
	}
	// cria o heap
	MaxHeap hp(heap, i);

	// um por um é armazenado no arquivo principal o maior elemento do maxheap 
	// e então é substituído pelo proximo elemento do arquivo no qual esse elemento foi retirado
	int cont = 0;
	while (cont < i) {
		// pega o maior elemento e armazena no arquivo principal
		Noh raiz = hp.getMax();
		bin.write((const char *)(&raiz.elemento), sizeof(raiz.elemento));

		// pega o próximo elemento do arquivo no qual o maior elemento foi retirado
		if(!tempArq[raiz.i].read((char *)(&raiz.elemento), sizeof(raiz.elemento))) {
			// caso tenha chegado no final da leitura de um arquivo esse elemento do heap
			// é jogado para o final dele colocando o campo nome como a "menor" string que irá ocorrer
			for(int x=0; x<10; x++)
				raiz.elemento.name[x] = '@';
			cont++;
		}

		hp.heapifyRaiz(raiz);
	}

	// fecha e deleta os arquivos temporários criados
	for (int i = 0; i < nArquivos; i++) {
		tempArq[i].close();
		remove(to_string(i).c_str());
	}

	bin.close();
}

int criarArquivosIniciais(int nLinhas) { // método que cria os arquivos temporários
	ifstream bin(FILENAME, ios::binary);
	ofstream tempArq;

	// aloca um vetor dinamicamente com o tamanho nLinhas
	// essa variável nLinhas é o número de registros que terão em cada arquivo temporário
	AthleteEvent *vetor = new AthleteEvent[nLinhas];

	int nArquivos = 0;
	bool lendo = true;
	while(lendo){
		int i=0;
		// escreve as nLinhas no vetor de struct
		while(i<nLinhas and lendo){
			if(!bin.read((char *)(&vetor[i]), sizeof(vetor[i])))
				lendo = false;
			else
				i++;
		}
		// essas nLinhas são ordenadas pelo método mergeSort
		// note que não é o arquivo todo que é ordenado, apenas nLinhas decididas anteriormente
		// para não utilizar muito espaço na memória
		mergeSort(vetor, 0, i - 1);

		// após serem ordenadas, essas nLinhas são escritas num arquivo temporário nomeado de 0 à nArquivos
		tempArq.open(to_string(nArquivos), ios::binary);
		for (int j = 0; j < i; j++)
			tempArq.write((const char *)(&vetor[j]), sizeof(vetor[j]));
		tempArq.close();
		nArquivos++;
	}

	bin.close();
	delete[] vetor;

	return nArquivos;
}

void externalSort(int nLinhas) { // método principal para a ordenação do arquivo
	// lê o arquivo principal, cria os arquvos temporarios e retorna o numero de arquivos temporários criados
	int nArquivos = criarArquivosIniciais(nLinhas);

	// junta os arquivos temporários usando o método K-way merging
	mergeArquivos(nArquivos);
}

// finaliza o código de ordenação

void telinha(){
	cout << "                   ,----,            \n"
		 << "                 ,/   .`|            \n"
		 << "  ,----..      ,`   .'  :   ,---,.   \n"
		 << " /   /   \\   ;    ;     / ,'  .'  \\ \n"
		 << "|   :     :.'___,/    ,',---.' .'  | \n"
		 << ".   |  ;. /|    :     | |   |  |:  | \n"
		 << ".   ; /--` ;    |.';  ; :   :  :  /  \n"
		 << ";   | ;    `----'  |  | :   |    ;   \n"
		 << "|   : |        '   :  ; |   :     \\ \n"
		 << ".   | '___     |   |  ' |   |   .  | \n"
		 << "'   ; : .'|    '   :  | '   :  ';  | \n"
		 << "'   | '/  :    ;   |.'  |   |  |   ; \n"
		 << "|   :    /     '---'    |   :     /  \n"
		 << " \\ \\   .'               |   |   ,' \n"
		 << "  `---`                 `------'     \n";
}

void menu() {
 	cout << "+-------------------------------+" << endl
	   	 << "| Escolha uma das opcoes:       |" << endl
	   	 << "| [1] Resetar                   |" << endl
	   	 << "| [2] Ordenar                   |" << endl
	   	 << "| [3] Imprimir tudo             |" << endl
	   	 << "| [4] Imprimir apenas uma parte |" << endl
	   	 << "| [5] Sair                      |" << endl
	   	 << "+-------------------------------+" << endl;
}

int main() {

	telinha();
	
	ifstream bin(FILENAME, ios::binary);

	if (!bin) {
		bin.close();
		cout << "Aguarde alguns instantes..." << endl;
		csvToBin();
	}

	int opcao;
	int nLinhas;

	do {
		menu();

		while (!(cin >> opcao)) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Digite um numero inteiro: ";
		}

		switch (opcao) {
			case 1:
				cout << "Aguarde alguns instantes..." << endl;
				csvToBin();
				cout << "Operacao finalizada!" << endl;
				break;

			case 2:
				nLinhas = 1000;
				cout << "Aguarde alguns instantes..." << endl;
				externalSort(nLinhas);
				cout << "Operacao finalizada!" << endl;
				verificarOrdenacao();
				break;

			case 3:
				imprimirTudo();
				break;

			case 4:
				int inicio, fim;
				cout << "Passe a posicao inicial: ";
				inicio = limitarEntrada(0, nElementos() - 1);
				cout << "Passe a posicao final: ";
				fim = limitarEntrada(inicio, nElementos());
				imprimirNumRange(inicio, fim);
				break;

			case 5:
				cout << "Ate mais.. <0.->" << endl;
				break;

			default:
				cout << "Opcao incorreta, digite algo valido." << endl;
				break;
		}

		cout << "Pressione <ENTER> para continuar . . . ";
		cin.ignore();
		getchar();
		system("cls||clear");
	} while (opcao != 5);

	return 0;
}