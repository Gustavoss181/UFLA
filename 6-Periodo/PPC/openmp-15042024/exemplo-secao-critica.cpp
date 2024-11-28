#include <iostream>
using namespace std;
#define N 4

int main(){
	int m[N][N], r[N],i, j;
	#pragma omp parallel for shared(m,r) private(i,j)
	for (i=0;i<N;i++)
	{
	  r[i]=0;
	  for (j=0;j<N;j++)
		m[i][j]=j+1;
	}

	#pragma omp master  
	{
	for (i=0;i<N;i++){
	   printf("\n");
	   for (j=0;j<N;j++)
		printf("m[%d][%d]=%d\n", i,j,m[i][j]);
	  }
	}
	#pragma omp parallel for shared(m, r) private(i,j) 
	  for (i=0;i<N;i++){
		 for (j=0;j<N;j++){
			 #pragma omp critical
			 r[i] += m[i][j]*2;  
		}
	  }
	printf("Result vector r: \n[");
	for (j=0;j<N;j++)
	   printf("%d\t",r[j]);
	printf("]\n");
	return 0;
}


