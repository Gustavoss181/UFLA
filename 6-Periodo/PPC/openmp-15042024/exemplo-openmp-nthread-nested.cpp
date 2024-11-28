#include <iostream>
using namespace std;

#include "omp.h"
#include <stdio.h>
#include <stdlib.h>

int main (){
int i,j;
printf("Numero de nucleos de processamento da maquina: %d\n", omp_get_num_procs());
printf("------------------------------------------------------------------------------------------\n");

#pragma omp parallel 
{
   printf("Identificador da Thread: %d  e numero de threads definidas por default pelo sistema: %d \n", omp_get_thread_num(), omp_get_num_threads());
}
printf("------------------------------------------------------------------------------------------\n");
omp_set_num_threads(6);
#pragma omp parallel 
{
printf("Identificador da Thread: %d  e numero de threads setadas dentro do programa: %d\n", omp_get_thread_num(), omp_get_num_threads());
}
printf("------------------------------------------------------------------------------------------\n");
#pragma omp parallel num_threads(3)
{
 printf("Identificador da Thread: %d  e numero maximo de threads: %d\n", omp_get_thread_num(), omp_get_max_threads());
}
printf("------------------------------------------------------------------------------------------\n");

printf("Paralelismo aninhado default (0 indica que nao esta setado e 1 esta setado): %d \n Setando para 1...\n", omp_get_nested());
omp_set_nested(1);
printf("------------------------------------------------------------------------------------------\n");
#pragma omp parallel for num_threads(4)
for (i=0;i<4;i++){
	printf("Primeiro nivel - thread %d - i = %d\n", omp_get_thread_num(), i);
#pragma omp parallel for num_threads(4)
	for (j=0;j<4;j++)
		printf("Segundo nivel - (i=%d, j=%d) thread=%d\n", i, j, omp_get_thread_num());
}
return 0;
}
