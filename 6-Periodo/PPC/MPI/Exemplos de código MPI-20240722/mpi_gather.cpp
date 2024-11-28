#include "mpi.h"
#include <iostream>
using namespace std;
const int SIZE=5;
int main(int argc, char** argv) { 
	int numtasks, rank, sendcount, recvcount, source, i; 
	float recvbuf[SIZE][SIZE]; 
	float sendbuf[SIZE]; 
	MPI_Init(&argc,&argv); 
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks); 
	if (numtasks == SIZE){ 
		for (i=0;i<SIZE;i++) {
			sendbuf[i]=(float) rank * SIZE + i; 
		}
			source = 0; 
			sendcount = SIZE; 
			recvcount = SIZE; 
			MPI_Gather(sendbuf, sendcount, MPI_FLOAT, recvbuf, recvcount, MPI_FLOAT,source, MPI_COMM_WORLD); 
			if (rank==source) 
				for (i=0;i<SIZE;i++) 
					cout << "Results proc "<< rank<< ":\t" << recvbuf[i][0] << "\t" << recvbuf[i][1] << "\t" << recvbuf[i][2] << "\t" << recvbuf[i][3] << endl; 
	} 
	else {
			if (rank == 0) cout <<"Especifique " << SIZE << " processos para executar este exemplo: mpirun -np 5 <nome_arquivo.exe>" << endl; 
	}
	MPI_Finalize(); 
} 
