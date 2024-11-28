//Exercício - somar os elementos de um vetor usando Pthread
#include <iostream>
#include <pthread.h>
#include <cstdlib>
#define n 4
#define tam 10
//g++ -pthread arq.cpp -o arq.o
using namespace std;

// variaveis globais acessadas por todas as threads
int soma=0;
int vet[tam];
pthread_mutex_t mutex; // semáforo para controle de acesso a variável

// funcao passada nos argumentos da criação das threads
void* funcao(void* x){
	int somaParcial=0, chunk, chunk2, inicio, fim;
	long id= (long) x;
	chunk = tam/n;
	if (tam%n!=0){
		chunk2= chunk + tam%n;
	}
	inicio =id*chunk;
	
	if (id==n-1){
		chunk=chunk2;
	}
	fim = inicio+chunk;
	printf("%ld %d %d \n",id, inicio, fim);
	for (int i=inicio;i < fim;i++){
		somaParcial += vet[i];
	}

	pthread_mutex_lock(&mutex);
	soma += somaParcial;
	pthread_mutex_unlock(&mutex);
	
	pthread_exit(NULL);
 }

int main()
{
	pthread_t id[n];
    
    pthread_mutex_init(&mutex, NULL);
    // srand(time(NULL));
	srand(1);
    for (int i=0; i<tam; i++)
		vet[i] = rand()%100;
	for (long j=0; j<n;j++){
		pthread_create(&id[j], NULL, funcao, (void*)j);
    }
    for (long j=0; j<n;j++){
		pthread_join(id[j], NULL);
    }
    cout << soma << endl;
    pthread_mutex_destroy(&mutex);
    return 0;
}
