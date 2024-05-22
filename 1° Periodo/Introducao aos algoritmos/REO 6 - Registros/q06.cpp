#include<iostream>
using namespace std;

struct Aluno{
    string matricula;
    string nome;
    int nota;
};

int main(){
    int n;
    cin >> n;
    Aluno alunos[n];
    for(int i=0; i<n; i++){
        cin >> alunos[i].matricula;
        cin >> alunos[i].nome;
        cin >> alunos[i].nota;
    }

    float media = 0, porc = 0;
    Aluno maior;
    maior.nota = -1;
    for(Aluno a : alunos){
        media += a.nota;
        if(maior.nota < a.nota)
            maior = a;
    }

    for(Aluno a : alunos)
        if(a.nota < media/n)
            porc += 100.0/n;

    cout << media/n << endl;
    for(Aluno a : alunos)
        if(a.nota == 0)
            cout << a.matricula << endl;
    cout << porc << '%' << endl;
    cout << maior.nome;

    return 0;
}