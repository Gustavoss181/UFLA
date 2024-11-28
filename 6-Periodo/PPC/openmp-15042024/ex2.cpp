#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    int i =11;
    #pragma omp atomic{
        if (i> 10){
            dot += aux_dot;
        }
    }

    return 0;
}