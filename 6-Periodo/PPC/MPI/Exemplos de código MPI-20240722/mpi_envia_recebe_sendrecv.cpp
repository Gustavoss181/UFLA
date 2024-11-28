// Bibliotecas utilizadas
#include <iostream>
#include "mpi.h"
using namespace std;
int main(int argc, char** argv) {
	// declaracao das variaveis locais
	int my_rank; /* identificador do processo*/
	int p; /* número de processos */
	int buffer; /* dado recebido */
	int tag = 0; /* tag para mensagens*/
	MPI_Status status; /* retorna de estado do receive */
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	MPI_Send(&my_rank, 1, MPI_INT, p-1-my_rank, tag, MPI_COMM_WORLD);
	MPI_Recv(&buffer, 1, MPI_INT, p-1-my_rank, tag, MPI_COMM_WORLD, &status);
	cout << "Meu rank:" << my_rank << ". Recebi mensagem do proc "<<  buffer<< endl;
	MPI_Finalize();
	return(0);
}

