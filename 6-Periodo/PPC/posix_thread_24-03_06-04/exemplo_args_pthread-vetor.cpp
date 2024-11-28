#include <iostream>

#include "pthread.h"
using namespace std;

void* primo(void* b){
	
	int *elemento = (int*) b;
	cout <<elemento[0] << " " << elemento[1] << " " << elemento[2] << endl;
	
}

int main(){
	pthread_t tid=10;
    int a[3]={1, 10, 5};
   
    pthread_create(&tid, NULL, primo, &a);
    pthread_join (tid, NULL);
    return 0;
}

