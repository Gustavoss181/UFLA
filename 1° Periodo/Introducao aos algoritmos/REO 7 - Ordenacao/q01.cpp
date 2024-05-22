#include<iostream>
#include<cmath>
using namespace std;

struct Cliente{
	string nome;
	float x;
	float y;
	float valorPizza;
	float distancia;
};

void insertion_sort(Cliente v[], int tam){
	Cliente pivo;
	int j;
	for (int i = 1; i < tam; i++) {
		pivo = v[i];
		j = i - 1;
		while ((j >= 0) and (pivo.distancia < v[j].distancia)){
			v[j+1] = v[j];
			j--;
		}
		v[j+1] = pivo;
	}
}


int main(){
	int nAtendidos, nClientesTotal;
	float x, y;
	cin >> nAtendidos >> x >> y >> nClientesTotal;
	Cliente clientes[nClientesTotal];

	for(int i=0; i<nClientesTotal; i++){
		cin >> clientes[i].nome;
		cin >> clientes[i].x;
		cin >> clientes[i].y;
		cin >> clientes[i].valorPizza;
		clientes[i].distancia = sqrt(pow(x-clientes[i].x, 2) + pow(y-clientes[i].y, 2));
	}

	insertion_sort(clientes, nClientesTotal);
	float soma=0;
	for(int i=0; i<nAtendidos; i++)
		soma += clientes[i].valorPizza;

	cout << soma;
	return 0;
}