#include<iostream>
using namespace std;

int buscaBin(int v[], int ini, int fim, int p){
	if(ini <= fim){
		int meio = (ini+fim)/2;
		if(v[meio] == p)
			return meio;
		else if(v[meio] > p)
			return buscaBin(v, ini, meio-1, p);
		else
			return buscaBin(v, meio+1, fim, p);
	}
	return -1;
}

int main(){
	int teste[5] = {1, 2, 3, 4, 5};

	cout << teste[buscaBin(teste, 0, 4, 4)];

	return 0;
}