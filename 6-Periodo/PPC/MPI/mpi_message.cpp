#include <mpi.h>
#include <iostream>

#define SIZE 20

using namespace std;

void gerarVetorAleatorio(int* vet, int tam, int seed = time(NULL), int min = 0, int max = 100){
    srand(seed);
    for(int i=0; i<tam; i++){
        vet[i] = (rand() % max) + min;
    }
}

int encontrarMin(int* vet, int tam){
    int min = vet[0];
    for(int i=1; i<tam; i++)
        if(min > vet[i])
            min = vet[i];
    return min;
}

int main(int argc, char**argv){
    int size, rank, rc, sendcount, reccount;

    MPI_Init(&argc,&argv);
	MPI_Comm_size (MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int* vet = new int[SIZE];
    int sub_tam = SIZE/size;
    int* subvet = new int[sub_tam];

    if(rank == 0){
        gerarVetorAleatorio(vet, SIZE, time(NULL), 1, 100);
        for(int i=0; i<SIZE; i++)
            cout << vet[i] << " ";
        cout << endl;
    }

    MPI_Scatter(vet, sub_tam, MPI_INT, subvet, sub_tam, MPI_INT, 0,  MPI_COMM_WORLD);

    int local_min = encontrarMin(subvet, sub_tam);
    int global_min;

    if(rank == 1){
        int* vet_min = new int[size];
        MPI_Gather(&local_min, 1, MPI_INT, vet_min, 1, MPI_INT, 1, MPI_COMM_WORLD);
        global_min = encontrarMin(vet_min, size);
        delete [] vet_min;
        cout << global_min << endl;
    }
    else{
        MPI_Gather(&local_min, 1, MPI_INT, nullptr, 0, MPI_INT, 1, MPI_COMM_WORLD);
    }

    MPI_Bcast(&global_min, 1, MPI_INT, 1, MPI_COMM_WORLD);

    for(int i=0; i<sub_tam; i++)
        subvet[i] *= global_min;
    
    MPI_Gather(subvet, sub_tam, MPI_INT, vet, sub_tam, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0){
        for(int i=0; i<SIZE; i++)
            cout << vet[i] << " ";
        cout << endl;
    }
    
    delete [] vet;
    delete [] subvet;

    MPI_Finalize();

    return 0;
}