#include<iostream>
using namespace std;

void selectionSort(int v[], int tam){
	for (int i=0; i<tam-1; i++){
		int posMenor = i;
		
		for (int j=i+1; j<tam; j++)
			if (v[j] < v[posMenor])
				posMenor = j;
		
		swap(v[i], v[posMenor]);
	}
}

int main(){
	int tam, n;
	cin >> tam;
	int v[tam];
	for(int i=0; i<tam; i++)
		cin >> v[i];
	cin >> n;

	selectionSort(v, n+1);

	for(int i=0; i<tam; i++)
		cout << v[i] << " ";

	return 0;
}