#include <pthread.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
using namespace std;

const long N = 10;
const long vetor[N] = {2, 7, 12, 5, 8, 6, 9, 11, 13, 4};
long x = -1000;
long y = -1000;

void* highRunner(void* args){
    for (int i = 0; i < N; i++){
        if(x < vetor[i]){
            x = vetor[i];
            cout << "x = " << x << endl;
            cout << "y = " << y << endl;
        }
    }
    pthread_exit(NULL);
}

void* lowRunner(void* args){
    for (int i = 0; i < N; i++){
        cout << (y == x) << endl;
        if((vetor[i] != x))
            if((y < vetor[i])){
                y = vetor[i];
                cout << "x = " << x << endl;
                cout << "y = " << y << endl;
            }
    }
    pthread_exit(NULL);
}

int main(){

    pthread_t td1, td2;

    pthread_create(&td1, NULL, highRunner, NULL);
    pthread_create(&td2, NULL, lowRunner, NULL);

    pthread_join(td1, NULL);
    pthread_join(td2, NULL);
    cout << x  << " & " << y << endl;

    return 0;
}