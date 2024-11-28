#include <pthread.h>
#include <cstdlib>
#include <iostream>
#define NUM_THREADS     100

using namespace std;

int valor=0;
pthread_mutex_t foo_mutex;

void *Test_semaforo(void* args)
{            
    pthread_mutex_lock(&foo_mutex);
    valor = valor+1;
    pthread_mutex_unlock(&foo_mutex);
    printf("Thread filha incrementou valor para %d\n",valor);
}

int main(){
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&foo_mutex, NULL);

    int rc;
    long t, y;
     
    
   for(y=0; y<NUM_THREADS; y++){
        printf("Criando thread %ld\n", y);
        rc = pthread_create(&threads[y], NULL, Test_semaforo, NULL);
        if (rc){
            printf("ERRO: código de retorno pthread_create() é %d\n", rc);
            exit(-1);
        }
    }
    
   
    printf("Thread mestre ID: pthread_join bloqueia a thread mestre até que a thread chegue neste ponto de execucao\n");
    for(t=0; t<NUM_THREADS; t++){
             pthread_join(threads[t],NULL);
    }
   
    printf("\n\nResultado - Thread mestre: Valor=%d\n", valor);
    pthread_mutex_destroy(&foo_mutex);
   
    pthread_exit(NULL);
    
    return 0;   
}
