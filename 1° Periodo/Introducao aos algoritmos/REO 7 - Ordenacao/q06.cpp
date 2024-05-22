#include<iostream>
using namespace std;

void mostrar(int v[], int t, int p1, int p2, bool troca){
	for(int i=0; i<t; i++){
		if(p1 == i or p2 == i){
			if(troca)
				cout << v[i] << " t\t";
			else
				cout << v[i] << " *\t";
		}
		else
			cout << v[i] << "\t";
	}
	cout << endl;
}

void bubbleSort(int v[], int t){
	for(int i=0; i<t-1; i++)
		for(int j=0; j<t-1-i; j++){
			mostrar(v, t, j, j+1, (v[j] > v[j+1]));
			if(v[j] > v[j+1])
				swap(v[j], v[j+1]);
		}
}

int main(){
	int tam;
	cin >> tam;
	int v[tam];
	for(int i=0; i<tam; i++)
		cin >> v[i];
	
	bubbleSort(v, tam);
	mostrar(v, tam, -1, -1, false);

	return 0;
}