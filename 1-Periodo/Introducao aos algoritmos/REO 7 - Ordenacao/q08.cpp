#include<iostream>
using namespace std;

void mostrar(int v[], int t){
	for(int i=0; i<t; i++)
		cout << v[i] << " ";
	cout << endl;
}

void selectionSort(int v[], int t){
	for(int i=0; i<t-1; i++){
		int pMaior = i;
		for(int j=i+1; j<t; j++)
			if(v[pMaior] < v[j])
				pMaior = j;
		swap(v[pMaior], v[i]);
		mostrar(v, t);
	}
}

int main(){
	int tam;
	cin >> tam;
	int v[tam];
	for(int i=0; i<tam; i++)
		cin >> v[i];

	selectionSort(v, tam);

	return 0;
}