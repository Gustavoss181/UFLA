#include <iostream>
#include <omp.h>
using namespace std;

long long num_passos = 1000000000;
int nThreads = 8;
double passo;

int main(int argc, char* argv[]){

	if(argc == 3){
		num_passos = atoll(argv[1]);
		nThreads = atoi(argv[2]);
	}

	long long i;
	double x, pi, soma=0.0, time_inicio, time_fim;
	time_inicio = omp_get_wtime();
	passo = 1.0/(double)num_passos;

	#pragma omp parallel for num_threads(nThreads) private(i,x) reduction(+:soma)
	for(i=0; i < num_passos; i++){
		x = (i + 0.5)*passo;
		soma = soma + 4.0/(1.0 + x*x);
	}

	pi = soma*passo;
	time_fim = omp_get_wtime();
	printf(" %.6f", time_fim - time_inicio);

	return 0;
}
