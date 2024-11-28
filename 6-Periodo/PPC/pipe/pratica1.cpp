#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main(){
    pid_t pid;

    if ( (pid=fork()) == 0 ) { // filho
        int soma = 0;
        for(unsigned short i = 1; i<=100; i+=2)
            soma += i;
        cout << "Soma dos impares pelo filho: " << soma << endl;
    }
    else if(pid > 0){ // Pai
        int soma = 0;
        for(unsigned short i = 2; i<=100; i+=2)
            soma += i;
        cout << "Soma dos pares pelo pai: " << soma << endl;
    }
    else{
        cout <<"Processo nao criado"<< endl;
        _exit(0);
    }

    return 0;

}


