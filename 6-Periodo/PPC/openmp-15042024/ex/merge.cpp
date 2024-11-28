#include <iostream>
using namespace std;


void intercala(int* a, int inicio, int meio, int fim) {
	int i = inicio, j = meio + 1;
	int tamanho = fim - inicio + 1;
	int aux[tamanho]; // vetor auxiliar
	for (int k=0; k < tamanho; k++) {
		if ((i <= meio) and (j <= fim)){ 
			if (a[i] <= a[j]){ 
				aux[k] = a[i]; // copia trecho1 em aux[]
				i++; 			// avança em trecho1
			} else { // 
				aux[k] = a[j]; // copia trecho2 em aux[]
				j++;	 		// avanca em trecho2
 			}
 		} else if (i > meio) { // terminou o trecho1	
			aux[k] = a[j];
			j++;
		} else { 				 // terminou o trecho2
			aux[k] = a[i];
			i++;
		}		
	}	
	// terminando: copiar de aux[] em a[inicio:fim]
	for (int k=0; k < tamanho; k++){ 
		a[inicio + k] = aux[k];
	}
}



void mergesort(int a[], int inicio, int fim){
	int meio;
	if (inicio < fim) {
		meio = (inicio + fim)/2; 
		mergesort(a, inicio, meio);
		mergesort(a, meio+1, fim);
		intercala(a, inicio, meio, fim);
	}
}


int main(int argc, char** argv){
	int tamanho = atoi(argv[1]);
	int* v=new int[tamanho];
	srand(time(NULL));
	for (int i=0;i<tamanho;i++){
		v[i]=rand()%100;
		cout << v[i] << " ";
	}
	cout << endl;

	mergesort(v,0,tamanho-1);
	for (int i=0;i<tamanho;i++)
		cout << v[i] << " ";
	return 0;
}
