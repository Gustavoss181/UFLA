#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <climits>
using namespace std;

const string FILENAME = "arquivo.bin";

struct Noh {
	// The element to be stored
	int elemento;
	// index of the array from which the element is taken
	int i;
};

// Prototype of a utility function to swap two min heap nodes
void swap(Noh* x, Noh* y){
	Noh temp = *x;
	*x = *y;
	*y = temp;
}

// A class for Min Heap
class MinHeap {
	// pointer to array of elements in heap
	Noh* heap;
	// size of min heap
	int tamanho;

	public:
		// Constructor: creates a min heap of given size
		MinHeap(Noh a[], int tam);
		// to heapify a subtree with root at given index
		void MinHeapify(int);
		// to get index of left child of node at index i
		int left(int i){
			return (2 * i + 1);
		}
		// to get index of right child of node at index i
		int right(int i){
			return (2 * i + 2);
		}
		// to get the root
		Noh getMin(){
			return heap[0];
		}
		// to replace root with new node x and heapify() new root
		void replaceMin(Noh x){
			heap[0] = x;
			MinHeapify(0);
		}
};

// Constructor: Builds a heap from a given array a[] of given size
MinHeap::MinHeap(Noh a[], int tam){
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
void MinHeap::MinHeapify(int i){
	int l = left(i);
	int r = right(i);
	int smallest = i;
	if (l < tamanho && heap[l].elemento < heap[i].elemento)
		smallest = l;
	if (r < tamanho && heap[r].elemento < heap[smallest].elemento)
		smallest = r;
	if (smallest != i) {
		swap(&heap[i], &heap[smallest]);
		MinHeapify(smallest);
	}
}

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r){
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	int L[n1], R[n2];

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
	while (i < n1 && j < n2) {
		if (L[i] <= R[j])
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
void mergeSort(int arr[], int l, int r){
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

FILE* openFile(char* fileName, char* mode){
	FILE* fp = fopen(fileName, mode);
	if (fp == NULL) {
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}
	return fp;
}

// Merges k sorted files. Names of files are assumed
// to be 1, 2, 3, ... k
void mergeFiles(int n, int k){
	fstream in[k];
	for (int i = 0; i < k; i++) {
		// Open output files in read mode.
		in[i].open(to_string(i), ios::binary | ios::in);
	}

	// FINAL OUTPUT FILE
	fstream bin(FILENAME, ios::binary | ios::out);

	// Create a min heap with k heap nodes.
	// Every heap node has first element of scratch output file
	Noh* heap = new Noh[k];
	int i;
	for (i = 0; i < k; i++) {
		// break if no output file is empty and
		// index i will be no. of input files
		if(!in[i].read((char *) (&heap[i].elemento), sizeof(heap[i].elemento)))
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
		if(!in[root.i].read((char *) (&root.elemento), sizeof(root.elemento))){
			root.elemento = INT_MAX;
			count++;
		}

		// Replace root with next
		// element of input file
		hp.replaceMin(root);
	}

	// close input and output files
	for (int i = 0; i < k; i++){
		in[i].close();
		remove(to_string(i).c_str());
	}

	bin.close();
}

// Using a merge-sort algorithm,
// create the initial runs
// and divide them evenly among
// the output files
void createInitialRuns(int run_size, int num_ways){
	// For big input file
	fstream bin(FILENAME, ios::binary | ios::in);

	// output scratch files
	ofstream out[num_ways];

	for (int i = 0; i < num_ways; i++) {
		// Open output files in write mode.
		out[i].open(to_string(i), ios::binary | ios::out);
	}

	// allocate a dynamic array large enough
	// to accommodate runs of size run_size
	int* arr = new int[run_size];

	bool more_input = true;
	int next_output_file = 0;

	int i;
	while (more_input) {
		// write run_size elements
		// into arr from input file
		for (i = 0; i < run_size; i++) {
			//if (fscanf(in, "%d ", &arr[i]) != 1) {
			if(!bin.read((char *) (&arr[i]), sizeof(arr[i]))){
				more_input = false;
				break;
			}
		}

		// sort array using merge sort
		mergeSort(arr, 0, i - 1);

		// write the records to the
		// appropriate scratch output file
		// can't assume that the loop
		// runs to run_size
		// since the last run's length
		// may be less than run_size
		for (int j = 0; j < i; j++)
			out[next_output_file].write((const char *)(&arr[j]), sizeof(arr[j]));

		next_output_file++;
	}

	// close input and output files
	for (int i = 0; i < num_ways; i++)
		out[i].close();

	bin.close();
}

// For sorting data stored on disk
void externalSort(int num_ways, int run_size){
	// read the input file,
	// create the initial runs,
	// and assign the runs to
	// the scratch output files
	createInitialRuns(run_size, num_ways);

	// Merge the runs using
	// the K-way merging
	mergeFiles(run_size, num_ways);
}

void lerBinario(){
	fstream bin(FILENAME, ios::binary | ios::in);
	if(bin){
		int n;
		
		while(bin.read((char *) (&n), sizeof(n))){
			cout << n << endl;
		}
		
		bin.close();
	}
}

void verificarOrdenacao(){
	ifstream bin(FILENAME, ios::binary | ios::in);
	int a, b;
	bool aux = true;
	bin.read((char *) (&a), sizeof(a));
	while(bin.read((char *) (&b), sizeof(b)) and aux) {
		if(a > b){
			bin.close();
			aux = false;
			cout << "Erro ao ordenar!" << endl;
		}
		a = b;
	}
	if(aux)
		cout << "Ordenacao foi um sucesso!" << endl;
	bin.close();
}

// Driver program to test above
int main(){
	// No. of Partitions of input file.
	int num_ways = 10;
	// The size of each partition
	int run_size = 1000;

	//FILE* in = openFile(input_file, "w");
	fstream bin(FILENAME, ios::binary | ios::out);
	if(bin){
		srand(time(NULL));
		// generate input
		for (int i = 0; i < num_ways * run_size; i++){
			int aux = rand();
			bin.write((const char *)(&aux), sizeof(int));
		}
		bin.close();
	}

	cout << "dados desordenados" << endl;
	lerBinario();
	verificarOrdenacao();

	externalSort(num_ways, run_size);

	cout  << endl << "dados ordenados" << endl;
	lerBinario();
	verificarOrdenacao();

	return 0;
}
