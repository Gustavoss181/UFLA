#include<iostream>
using namespace std;

void insertionSort(int v[], int t){
	for(int i=1; i<t; i++){
		int pivo = v[i];
		int j;
		for(j=i-1; j>=0 and v[j] < pivo; j--)
			v[j+1] = v[j];
		v[j+1] = pivo;
	}
}

int main(){
	int tam, k;
	cin >> tam;
	int v[tam];
	for(int i=0; i<tam; i++)
		cin >> v[i];
	cin >> k;

	insertionSort(v, tam);

	int soma = 0;
	for(int i=0; i<k; i++)
		soma += v[i];
	
	cout << soma;

	return 0;
}