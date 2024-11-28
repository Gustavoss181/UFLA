/* Relacionamento de sincronização first-start entre 2 threads */
#include <iostream>
#include <pthread.h> // biblioteca POSIX thread
using namespace std;
pthread_t ThreadA, ThreadB; // declare threads
pthread_mutex_t Mutex, EventMutex;
pthread_cond_t Event;
int numero=0;


void *tarefa1(void *X) //define tarefa 
{
	
	for (int cont = 1; cont < 100; cont++){
		pthread_mutex_lock(&Mutex);
		numero++;
		pthread_mutex_unlock(&Mutex);
		cout << "tarefa1: número é " << numero << endl;
	    if (numero == 50){
		    pthread_cond_signal(&Event);
	    }
	}
	cout << "Tarefa 1 feita" << endl;
	return(0);
}



void *tarefa2(void *X) //define tarefa 
{
	pthread_mutex_lock(&EventMutex);
	pthread_cond_wait(&Event, &EventMutex);
	pthread_mutex_unlock(&EventMutex);
	for (int cont = 1; cont < 50; cont++){
		pthread_mutex_lock(&Mutex);
		numero = numero + 20;
		pthread_mutex_unlock(&Mutex);
		cout << "tarefa2: número é " << numero << endl;
	}
	cout << "Tarefa 2 feita" << endl;
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
