#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <fstream>

using namespace std;

int main(){
    int fd[2], fd2[2];

    pid_t pid, pid2; 
    if( (pipe(fd)<0) or (pipe(fd2)<0)) {
        cout << "Pipe nao criado" << endl;
        _exit(0);
    }
    if( (pid=fork())<0 ) {
        cout <<"Processo nao criado"<< endl;
        _exit(0);
    }

    if ( pid == 0 ) { // filho 1
        ifstream arq("arquivo2.txt");
        int cont = 0;
        string aux;
        if(arq){
            while(arq >> aux) cont++;

            arq.close();
        }

        close(fd[0]);
        write(fd[1], &cont, sizeof(cont));
        close(fd[1]);
    }
    else if ( (pid2 = fork()) == 0 ) { // filho 2
        ifstream arq("arquivo3.txt");
        int cont = 0;
        string aux;
        if(arq){
            while(arq >> aux) cont++;

            arq.close();
        }

        close(fd2[0]);
        write(fd2[1], &cont, sizeof(cont));
        close(fd2[1]);
    }
    else if(pid > 0){ // Pai
        close(fd[1]);
        close(fd2[1]);
        ifstream arq("arquivo1.txt");
        int cont = 0;
        string aux;
        if(arq){
            while(arq >> aux) cont++;

            arq.close();
        }

        int qtdArq2, qtdArq3;
        read(fd[0], &qtdArq2, sizeof(qtdArq2));
        read(fd2[0], &qtdArq3, sizeof(qtdArq3));
        cout << "arquivo1 - " << cont << " palavras" << endl;
        cout << "arquivo2 - " << qtdArq2 << " palavras" << endl;
        cout << "arquivo3 - " << qtdArq3 << " palavras" << endl;
    }
    else{
        cout <<"Processo nao criado"<< endl;
        _exit(0);
    }

    return 0;

}


