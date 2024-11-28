#include "mpi.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#define SIZE 5 
using namespace std; 

int main(int argc, char *argv[]) { 
	int numtasks, rank, sendcount, recvcount, source; 
	string arquivo="saida";
	
	float sendbuf[SIZE][SIZE] = { 
	{1.1, 2.0, 3.0, 4.0, 5.0}, 
	{5.0, 6.2, 7.0, 8.0, 4.0}, 
	{9.0, 10.0, 11.0, 12.4, 2.0}, 
	{10.0, 1.0, 11.0, 13.2, 4.2},
	{13.5, 14.0, 15.9, 16.1, 3.0}}; //buffer de envio 
	float recvbuf[SIZE];//buffer de recebimento 
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	arquivo = arquivo+to_string(rank);
	ofstream arq(arquivo.c_str());
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks); 
	if (numtasks == SIZE){ 
 		source = 0; 
 		sendcount = SIZE; 
 		recvcount = SIZE; 
 		MPI_Scatter(sendbuf, sendcount, MPI_FLOAT, recvbuf, recvcount, MPI_FLOAT, source,  MPI_COMM_WORLD); 
 		for (int i=0;i<SIZE;i++)
  		   arq << recvbuf[i] << "\t " ; 
  		
	    
	}else 
		cout <<"Must specify " << SIZE << " processors. Terminating."; 
	MPI_Finalize(); 
} 
