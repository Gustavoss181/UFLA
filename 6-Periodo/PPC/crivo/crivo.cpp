#include <iostream>
#include <pthread.h>
#include <vector>

bool* vet;
int n;

void* funcao(void *a){
    int k = *(int*)a;

    if(vet[k])
        pthread_exit(NULL);

    for(int i=k*k; i<n; i+=k){
        vet[i] = true;
    }

    delete (int*)a;
    pthread_exit(NULL);
}

int main(int argc, char** argv){
    if(argc == 2){
        std::cout << "entrou" << std::endl;
        try{
            n = std::stoi(argv[1]);
        }
        catch(const std::invalid_argument& e){
            n = 50;
        }
    }
    else{
        n = 50;
    }

    vet = new bool[n];
    for(int i=0; i<n; i++)
        vet[i] = false;
    std::vector<pthread_t> id;

    for(int k=2; k*k<n; k++){
        if(!vet[k]){
            pthread_t idd;
            id.push_back(idd);
            int* kk = new int;
            *kk = k;
            pthread_create(&id[id.size()-1], NULL, funcao, kk);
        }
    }

    for(pthread_t idd : id){
        pthread_join(idd, NULL);
    }
    std::cout << "N de threads: " << id.size() << std::endl;

    for(int i=2; i<n; i++)
        if(!vet[i])
            std::cout << i << " ";
    std::cout << std::endl;

    delete [] vet;

    return 0;
}