#include "cabecalho.hpp"
#include <climits>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>

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

void lerBinario(string filename) {
  ifstream bin(filename, ios::binary);
  if (bin) {
	AthleteEvent n;

	while (bin.read((char *)(&n), sizeof(n))) {
	  cout << n;
	}

	bin.close();
  }
}

void verificarOrdenacao() {
  ifstream bin(FILENAME, ios::binary);
  AthleteEvent a, b;
  bool aux = true;

  bin.read((char *)(&a), sizeof(a));

  while (bin.read((char *)(&b), sizeof(b)) and aux) {
	if (a < b) {
	  bin.close();
	  aux = false;
	  cout << "Erro ao ordenar!" << endl;
	}
	a = b;
  }

  if (aux)
	cout << "Ordenacao foi um sucesso!" << endl;

  bin.close();
}

void imprimirNumRange(int ini, int fim) { // imprime de uma posição inicial até uma posição final
  ifstream bin(FILENAME);

  if (bin) {
	// lidando com inputs incorretos
	if (ini < 0)
	  ini = 0;
	int tam = nElementos(bin) - 1;
	if (fim > tam)
	  fim = tam;

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
  bin.seekg(0, bin.beg);
  if (bin) {
	AthleteEvent linha;

	while (bin.read((char *)(&linha), sizeof(AthleteEvent))) {
	  cout << linha;
	}

	bin.close();
  }
}

// faz a conversão do arquivo csv para binario
bool csvToBin() {
  ofstream bin(FILENAME, ios::binary);
  // abre o csv COM ESSE NOME para leitura
  // ifstream csv("data_athlete_event.csv");
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
		str += a; // cada caractere é armazenado na string para fazer a
				  // conversão correta em cada campo
	}

	csv.close();
	bin.close();

	return true;
  } else
	return false;
}

// inicia o código de ordenação
struct Noh {
  // The element to be stored
  AthleteEvent elemento;
  // index of the array from which the element is taken
  int i;
};

// Prototype of a utility function to swap two min heap nodes
void swap(Noh *x, Noh *y) {
  Noh temp = *x;
  *x = *y;
  *y = temp;
}

// A class for Min Heap
class MinHeap {
  // pointer to array of elements in heap
  Noh *heap;
  // size of min heap
  int tamanho;

	public:
	  // Constructor: creates a min heap of given size
	  MinHeap(Noh a[], int tam);
	  // to heapify a subtree with root at given index
	  void MinHeapify(int);
	  // to get index of left child of node at index i
	  int left(int i) { return (2 * i + 1); }
	  // to get index of right child of node at index i
	  int right(int i) { return (2 * i + 2); }
	  // to get the root
	  Noh getMin() { return heap[0]; }
	  // to replace root with new node x and heapify() new root
	  void replaceMin(Noh x) {
		heap[0] = x;
		MinHeapify(0);
	  }
};

// Constructor: Builds a heap from a given array a[] of given size
MinHeap::MinHeap(Noh a[], int tam) {
  tamanho = tam;
  heap = a; // store address of array
  int i = (tamanho - 1) / 2;
  while (i >= 0) {
	MinHeapify(i);
	i--;
  }
}

// A recursive method to heapify a subtree with root at given index.
// This method assumes that the subtrees are already heapified
void MinHeap::MinHeapify(int i) {
  int l = left(i);
  int r = right(i);
  int smallest = i;
  if (l < tamanho && heap[l].elemento > heap[i].elemento)
	smallest = l;
  if (r < tamanho && heap[r].elemento > heap[smallest].elemento)
	smallest = r;
  if (smallest != i) {
	swap(&heap[i], &heap[smallest]);
	MinHeapify(smallest);
  }
}

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(AthleteEvent arr[], int l, int m, int r) {
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;

  /* create temp arrays */
  AthleteEvent L[n1], R[n2];

  /* Copy data to temp arrays L[] and R[] */
  for (i = 0; i < n1; i++)
	L[i] = arr[l + i];
  for (j = 0; j < n2; j++)
	R[j] = arr[m + 1 + j];

  /* Merge the temp arrays back into arr[l..r]*/
  // Initial index of first subarray
  i = 0;

  // Initial index of second subarray
  j = 0;

  // Initial index of merged subarray
  k = l;
  while ((i < n1) and (j < n2)) {
	if (L[i] >= R[j])
	  arr[k++] = L[i++];
	else
	  arr[k++] = R[j++];
  }

  /* Copy the remaining elements of L[],
		  if there are any */
  while (i < n1)
	arr[k++] = L[i++];

  /* Copy the remaining elements of R[],
		  if there are any */
  while (j < n2)
	arr[k++] = R[j++];
}

/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(AthleteEvent arr[], int l, int r) {
  if (l < r) {
	// Same as (l+r)/2, but avoids overflow for
	// large l and h
	int m = l + (r - l) / 2;

	// Sort first and second halves
	mergeSort(arr, l, m);
	mergeSort(arr, m + 1, r);

	merge(arr, l, m, r);
  }
}

// Merges k sorted files. Names of files are assumed
// to be 1, 2, 3, ... k
void mergeFiles(int k) {
  ifstream in[k];
  for (int i = 0; i < k; i++) {
	// Open output files in read mode.
	in[i].open(to_string(i), ios::binary);
		//cout << "-----------------------------------------------------" << endl;
		//lerBinario(to_string(i));
  }
	//cout << "-----------------------------------------------------" << endl;

  // FINAL OUTPUT FILE
  ofstream bin(FILENAME, ios::binary);

  // Create a min heap with k heap nodes.
  // Every heap node has first element of scratch output file
  Noh *heap = new Noh[k];
  int i;
  for (i = 0; i < k; i++) {
	// break if no output file is empty and
	// index i will be no. of input files
	if (!in[i].read((char *)(&heap[i].elemento), sizeof(heap[i].elemento)))
	  break;

	// Index of scratch output file
	heap[i].i = i;
  }
  // Create the heap
  MinHeap hp(heap, i);

  int count = 0;

  // Now one by one get the
  // minimum element from min
  // heap and replace it with
  // next element.
  // run till all filled input
  // files reach EOF
  while (count != i) {
	// Get the minimum element
	// and store it in output file
	Noh root = hp.getMin();
	bin.write((const char *)(&root.elemento), sizeof(root.elemento));

	// Find the next element that
	// will replace current
	// root of heap. The next element
	// belongs to same
	// input file as the current min element.
	if (!in[root.i].read((char *)(&root.elemento), sizeof(root.elemento))) {
	  // root.elemento = INT_MAX;
	  root.elemento.name[0] = SCHAR_MIN;
	  count++;
	}

	// Replace root with next
	// element of input file
	hp.replaceMin(root);
  }

  // close input and output files
  for (int i = 0; i < k; i++) {
	in[i].close();
	remove(to_string(i).c_str());
  }

  bin.close();
}

// Using a merge-sort algorithm,
// create the initial runs
// and divide them evenly among
// the output files
void createInitialRuns(int nLinhas, int nArquivos) {
  // For big input file
  ifstream bin(FILENAME, ios::binary);

  // output scratch files
  ofstream out[nArquivos];

  for (int i = 0; i < nArquivos; i++) {
	// Open output files in write mode.
	out[i].open(to_string(i), ios::binary);
  }

  // allocate a dynamic array large enough
  // to accommodate runs of size nLinhas
  AthleteEvent *arr = new AthleteEvent[nLinhas];

  bool more_input = true;
  int next_output_file = 0;

  int i;
  while (more_input) {
	// write nLinhas elements
	// into arr from input file
	for (i = 0; i < nLinhas; i++) {
	  // if (fscanf(in, "%d ", &arr[i]) != 1) {
	  if (!bin.read((char *)(&arr[i]), sizeof(arr[i]))) {
		more_input = false;
		break;
	  }
	}

	// sort array using merge sort
	mergeSort(arr, 0, i - 1);

	// write the records to the
	// appropriate scratch output file
	// can't assume that the loop
	// runs to nLinhas
	// since the last run's length
	// may be less than nLinhas
	for (int j = 0; j < i; j++)
	  out[next_output_file].write((const char *)(&arr[j]), sizeof(arr[j]));

	next_output_file++;
  }

  // close input and output files
  for (int i = 0; i < nArquivos; i++)
	out[i].close();

  bin.close();
}

// For sorting data stored on disk
void externalSort(int nArquivos, int nLinhas) {
  // read the input file,
  // create the initial runs,
  // and assign the runs to
  // the scratch output files
  createInitialRuns(nLinhas, nArquivos);

  // Merge the runs using
  // the K-way merging
  mergeFiles(nArquivos);
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
  ifstream bin(FILENAME, ios::binary);

  if (!bin) {
	bin.close();
	csvToBin();
  }

  int opcao, n = 1000;
  chrono::_V2::system_clock::time_point start, finish;

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
		cout << "Aguarde alguns instantes..." << endl;
		start = chrono::high_resolution_clock::now();
	  	externalSort((nElementos()/n)+1, n);
		finish = chrono::high_resolution_clock::now();
		cout << "Operacao finalizada!" << endl;
		cout << nElementos() << endl;
	  	verificarOrdenacao();
		cout << "Tempo gasto para ordenacao: " << chrono::duration_cast<chrono::seconds>(finish-start).count() << "s" << endl;
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

  } while (opcao != 5);

  return 0;
}