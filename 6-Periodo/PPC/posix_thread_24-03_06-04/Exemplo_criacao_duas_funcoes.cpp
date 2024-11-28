/* Programa cria duas threads tid1 e tid2. tid1 executa a funcao runner que realiza a soma dos numeros */
/* de 1 até o valor passado como argumento. tid2 imprime o identificador da thread */
#include <pthread.h>
#include <cstdlib>
#include <iostream>
const int N = 100;
using namespace std;

int sum;
void *runner(void *param);
void *print_message_function(void* args);

int main(int argc, char **argv)
{
   pthread_t tid1, tid2;
   pthread_attr_t attr;
   pthread_attr_init(&attr);
   /*Cria thread tid1*/
   pthread_create(&tid1,&attr,runner,(void *) N);
   /*Cria thread tid2*/
   pthread_create(&tid2,&attr,print_message_function,NULL);
   /*Thread principal espera até thread tid1 terminar execução*/
   pthread_join(tid1,NULL);
   /*Thread principal espera até thread tid2 terminar execução*/
   pthread_join(tid2,NULL);
   cout << "Soma = " << sum << endl;
   exit(0);
}

void *print_message_function( void* args )
{
   
   cout << "Thread filha. " << endl;
   pthread_exit(NULL);
}

void *runner(void *param)
{
   long upper = (long)(param);
   long i;

   sum = 0;
   if (upper > 0) {
   /* Soma os valores de 1 até o valor upper inclusive*/
   for (i = 1; i <= upper; i++)
       sum += i;
   }
  
   pthread_exit(NULL);
}





