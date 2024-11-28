#include<iostream>
using namespace std;

struct Aluno{
    int matricula;
    string nome;
};

int buscaBin(Aluno a[], int i, int f, int p){
    while(i <= f){
        int m = (i+f)/2;
        cout << a[m].matricula << endl;
        if(a[m].matricula == p)
            return m;
        else if(a[m].matricula > p)
            f = m-1;
        else
            i = m+1;
    }
    return -1;
}

int main(){
    int n, procurado;
    cin >> n;
    Aluno alunos[n];
    for (int i=0; i<n; i++)
        cin >> alunos[i].matricula >> alunos[i].nome;
    cin >> procurado;

    int pos = buscaBin(alunos, 0, n-1, procurado);
    
    if(pos != -1)
        cout << alunos[pos].nome;

    return 0;
}