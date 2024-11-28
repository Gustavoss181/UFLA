#include <iostream>
#include <pthread.h>
#include <cmath>

#define N 5000
#define TAM 30

using namespace std;

bool marcados[N + 1];
double range = ceil((double)N / TAM);

void* crivo(void* x) {
    long id = (long)x;
    int start = range * id + 2;
    int end = range + start + 1;

    for (int k = start; k <= end; k++) {
        for (int i = k * k; i <= N; i++) {
            if (i % k == 0) {
                marcados[i] = true;
            }
        }
        if (k*k > N) break;
    }

    return NULL;
}

int main() {
    pthread_t id[TAM];

    for (int i = 2; i <= N; i++) {
        marcados[i] = false;
    }

    for (long j = 0; j < TAM; j++) {
        pthread_create(&id[j], NULL, crivo, (void *)j);
    }

    for (long j = 0; j < TAM; j++) {
        pthread_join(id[j], NULL);
    }

    for (int i = 2; i <= N; i++) {
        if (marcados[i] == false) {
            cout << i << " ";
        }
    }
    cout << endl;

    return 0;
}