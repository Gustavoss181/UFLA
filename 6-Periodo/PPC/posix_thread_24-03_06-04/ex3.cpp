#include <iostream>
#include <pthread.h>

#define N 100

int *vet;

void* routine2(void* a){

}

void* routine(void* a){
    
}

void insertion(){
    pthread_t th1, th2;

    pthread_create(&th1, NULL, routine, NULL);
    pthread_create(&th2, NULL, routine2, NULL);
}

int main(int argc, char* argv[]){
    vet = new int[N];
    srand(1);
    for(int i=0; i<N; i++)
        vet[i] = rand() % 1000;

    return 0;
}