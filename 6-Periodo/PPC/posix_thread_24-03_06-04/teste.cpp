#include <stdio.h>

int main(){
    int i = 1000000;
    while(--i);
    printf("%d\n", i);

    return 0;
}