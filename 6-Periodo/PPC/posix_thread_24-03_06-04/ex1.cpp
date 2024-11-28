#include <iostream>
#include <pthread.h>
#include <cstdlib>

struct Args{
    int* vet;
    int tam;
    int maior, segMaior;
    float media;
    int somaPares;

    pthread_mutex_t mutex;
};

void* maiores(void* a){
    Args* args = (Args*) a;
    int iMaior = 0, iSegMaior = 0;
    for(int i=1; i<args->tam; i++)
        if(args->vet[i] > args->vet[iMaior])
            iMaior = i;
    if(iMaior == 0)
        iSegMaior = 1;
    for(int i=iSegMaior+1; i<args->tam; i++)
        if(i != iMaior and args->vet[i] > args->vet[iSegMaior])
            iSegMaior = i;
    args->maior = args->vet[iMaior];
    args->segMaior = args->vet[iSegMaior];
    pthread_exit(NULL);
}

void* media(void* a){
    Args* args = (Args*) a;
    int soma = 0;
    for(int i=0; i<args->tam; i++)
        soma += args->vet[i];
    args->media = ((float)soma)/((float)args->tam);
    pthread_exit(NULL);
}

void* somaPares(void* a){
    Args* args = (Args*) a;
    int soma = 0;
    for(int i=0; i<args->tam; i++)
        if(args->vet[i]%2 == 0)
            soma += args->vet[i];
    args->somaPares = soma;
    pthread_exit(NULL);
}

int main(){
    Args* args = new Args();

    args->tam = 20;
    args->vet = new int[args->tam];

    pthread_t id[3];
    
    pthread_mutex_init(&args->mutex, NULL);
    // srand(time(NULL));
	srand(1);
    for (int i=0; i<args->tam; i++)
		args->vet[i] = rand()%100;
    
	pthread_create(&id[0], NULL, maiores, args);
    pthread_create(&id[1], NULL, media, args);
    pthread_create(&id[2], NULL, somaPares, args);

    for (long j=0; j<3;j++){
		pthread_join(id[j], NULL);
    }

    std::cout << "Vetor: ";
    for(int i=0; i<args->tam; i++)
        std::cout << args->vet[i] << " ";
    std::cout << "\nMaior: " << args->maior << std::endl;
    std::cout << "Segundo Maior: " << args->segMaior << std::endl;
    std::cout << "Media: " << args->media << std::endl;
    std::cout << "Soma pares: " << args->somaPares << std::endl;

    pthread_mutex_destroy(&args->mutex);

    return 0;
}