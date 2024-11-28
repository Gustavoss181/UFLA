#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv){
    int numprocs, rank;
    int N;

    MPI_Init(&argc,&argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    if(argc != 2){
        cout << "Uso 'mpirun -np NP ex3.o N'" << endl;
        return 1;
    }
    N = atoi(argv[1]);
    
    int range = N/numprocs;
    float somaParc = 0;

    for(int i=rank+1; i<=N; i+=numprocs){
        if(i%2 == 0)
            somaParc -= 1.0/i;
        else
            somaParc += 1.0/i;
    }

    float somaTotal = 0;
    MPI_Reduce(&somaParc, &somaTotal, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0){
        cout << somaTotal << endl;
    }

    MPI_Finalize();

    return 0;
}