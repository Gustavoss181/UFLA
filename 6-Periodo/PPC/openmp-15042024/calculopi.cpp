#include <iostream>
#include <omp.h>
using namespace std;

long long num_passos = 1000000000;
double passo;

int main(){
   long long i;
   double x, pi, soma=0.0;

   passo = 1.0/(double)num_passos;
   
   #pragma omp parallel for private(x,i) reduction(+:soma)
   for(i=0; i < num_passos; i++){
      x = (i + 0.5)*passo;
      soma = soma + 4.0/(1.0 + x*x);
   }

   pi = soma*passo;

   cout << "O valor de PI é: " << pi << endl;
   return 0;
}
