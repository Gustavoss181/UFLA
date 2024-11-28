/* Relacionamento de sincronização first-first entre 2 threads */
#include <iostream>
#include <pthread.h> // biblioteca POSIX thread
using namespace std;
pthread_t ThreadA, ThreadB; // declare threads
pthread_mutex_t Mutex, EventMutex;
pthread_cond_t Event;
float numero;


void *tarefa1(void *X) //define tarefa 
{
	for (int cont = 1; cont < 10; cont++){
		pthread_mutex_lock(&Mutex);
		numero++;
		pthread_mutex_unlock(&Mutex);
		cout << "tarefa1: número é " << numero << endl;
	}
	pthread_mutex_lock(&EventMutex);
	cout << "tarefa1 feita e esperando sinal"<< endl;
	pthread_cond_wait(&Event, &EventMutex);
	pthread_mutex_unlock(&EventMutex);
	return(0);
}



void *tarefa2(void *X) //define tarefa 
{
    for (int cont = 1; cont < 50; cont++){
		pthread_mutex_lock(&Mutex);
		numero = numero*2;
		pthread_mutex_unlock(&Mutex);
		cout << "tarefa2: número é " << numero << endl;
	}
	pthread_cond_signal(&Event);
	cout << "tarefa2 feita e sinalizando"<< endl;
	return(0);
}


int main(int argc, char *argv[]){
	pthread_mutex_init(&Mutex, NULL);
	pthread_mutex_init(&EventMutex, NULL);
	pthread_cond_init(&Event, NULL);
	
	// seta atributos de mutex 
	pthread_create(&ThreadA, NULL, tarefa1, NULL); 
	pthread_create(&ThreadB, NULL, tarefa2, NULL); 
	pthread_mutex_destroy(&Mutex);
	pthread_mutex_destroy(&EventMutex);
	pthread_join(ThreadA,NULL);
	pthread_join(ThreadB,NULL);
	pthread_cond_destroy(&Event);
	return(0);
}
