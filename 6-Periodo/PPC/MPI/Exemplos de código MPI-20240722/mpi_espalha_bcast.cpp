#include "mpi.h"
#include <iostream>
using namespace std;
int main(int argc, char** argv){

	int n=0, myid, numprocs;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	if (myid==0){
		n=90;
	}
	MPI_Bcast(&n, 1, MPI_INT,0, MPI_COMM_WORLD);
	
	cout << "O processo " << myid << " recebeu o valor n=" <<  n << endl;
	MPI_Finalize();
	return 0;
}
