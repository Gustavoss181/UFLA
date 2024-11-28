#include <iostream>
#include <pthread.h>

#define N 1000
#define NTH 8

int *vet;
int search;
bool found = false;

void* routine(void *a){
    int id = *(int*)a;

    int init = N/NTH * id;
    int end = N/NTH * (id+1);

    int *result = NULL;
    for(int i=init; i<end; i++){
        if(found){
            delete (int*)a;
            return (void*) result;
        }
        if(vet[i] == search){
            found = true;
            result = new int;
            *result = i;
            delete (int*)a;
            return (void*) result;
        }
    }
    delete (int*)a;
    return (void*) result;
}

int main(int argc, char *argv[]){
    search = 327;

    vet = new int[N];
    srand(1);
    for(int i=0; i<N; i++)
        vet[i] = rand() % 1000;
    
    pthread_t thid[NTH];
    for(int i=0; i<NTH; i++){
        int *id = new int;
        *id = i;
        pthread_create(thid+i, NULL, routine, id);
    }

    int **res = new int*[NTH];
    for(int i=0; i<NTH; i++){
        pthread_join(thid[i], (void**)(&res[i]));
    }

    for(int i=0; i<NTH; i++){
        if(res[i] != NULL)
            printf("Valor %d encontrado na thread %d na posicao %d\n", search, i+1, *res[i]);
    }
    if(!found)
        std::cout << "Valor nao encontrado" << std::endl;

    for(int i=0; i<NTH; i++)
        delete res[i];
    delete [] res;
    delete [] vet;

    return 0;
}