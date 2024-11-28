#include <iostream>

#include "pthread.h"
using namespace std;

struct argum{
int e;
int k;
};

void* imprime(void* b){
	
	argum *elemento = (argum*) b;
	cout <<elemento->e << " " << elemento->k << endl;
	return 0;
}

int main(){
	pthread_t tid[2];
	for (int i=0;i<2;i++){
		argum *a = new argum;
		a->e=i;
		a->k=20;
		pthread_create(&tid[i], NULL, imprime, a);
	}
	for (int i=0;i<2;i++)
		pthread_join (tid[i], NULL);
    return 0;
}

