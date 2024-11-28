#include <pthread.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <time.h>
#define NUM_THREADS     5
using namespace std;

void *PrintHello(void *threadid)
{
   long tid;
   tid = (long)threadid;
   cout << "Sou a thread " << tid << endl;
   pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
   pthread_t threads[NUM_THREADS];
   int rc;
   long t;
   for(t=0; t<NUM_THREADS; t++){
      cout << "Thread principal: criando thread " << t << endl;
      rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
      if (rc){
         cout << "ERROR; return code from pthread_create() is  " << rc << endl;
         exit(-1);
      }
   }
   pthread_exit(NULL);
}

 
