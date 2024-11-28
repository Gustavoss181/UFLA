#include <iostream>
#include <omp.h>

using namespace std;

int main (int argc, char *argv[ ]) {
    int a[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

    #pragma omp parallel for schedule(static,5) shared(a)
    for(int i=0; i<20; i++){
        cout << "Thread " << omp_get_thread_num() << ": " << a[i] << endl;
    }

    return 0;
}
