#include <iostream>
#include <omp.h>
#define N 10
using namespace std;

int main(){
    double a[N]={1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    double b[N]={10.0, 10.0, 10.0, 10.0, 10.0, 10.0,10.0, 10.0,10.0, 10.0}, c[N], d[N];
    int i, tid;
	omp_set_nested(1);
	#pragma omp parallel shared(a,b,c,d) private(i,tid)
	{
		tid = omp_get_thread_num();
		#pragma omp sections nowait
		{
			#pragma omp section
			{
				printf("Thread %d doing section 1\n",tid);
				#pragma omp parallel for
				for (i=0; i<N; i++) {
				   c[i] = a[i] + b[i];
				}
			}
			#pragma omp section
			{
				printf("Thread %d doing section 2\n",tid);
				#pragma omp parallel for
				for (i=0; i<N; i++) {
					d[i] = a[i] * b[i];
				}
			}
		} /* end of sections */
	} /* end of parallel section */
	    
    cout << "Vetor c"<< endl;
	for (int j=0; j<N; j++) {
	    cout << " " << c[j] ;
    }
    cout << endl;
    cout << "Vetor d"<< endl;
    for (int j=0; j<N; j++) {
	    cout << " " << d[j] ;
    }
    cout << endl;
	return 0;
}

