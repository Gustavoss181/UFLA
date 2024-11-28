#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv){
    int numprocs, rank;
    const int SIZE=10;
    float sendbuf[SIZE];

    MPI_Init(&argc,&argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    float recvbuf[SIZE*numprocs];

    srand(time(NULL));
    for (int i=0;i<SIZE;i++) {
	    sendbuf[i]= (rand()%100) / 3.0;
    }

    //função para juntar os dados
    MPI_Gather(sendbuf, SIZE, MPI_FLOAT, recvbuf, SIZE, MPI_FLOAT,0, MPI_COMM_WORLD);

    if (rank==0) {
       for (int i=0;i<SIZE*numprocs;i++) 
           cout << recvbuf[i] << " "; 
    }

    MPI_Finalize();

    return 0;
}