#include<iostream>
using namespace std;

struct Paciente{
    string nome;
    char sexo;
    float altura;
    float peso;
    float pesoIdeal;
};

int main(){
    int n;
    cin >> n;
    Paciente pacientes[n];
    for(int i=0; i<n; i++){
        cin >> pacientes[i].nome;
        cin >> pacientes[i].sexo;
        cin >> pacientes[i].altura;
        cin >> pacientes[i].peso;
        if(pacientes[i].sexo == 'H')
            pacientes[i].pesoIdeal = 72.7 * pacientes[i].altura - 58;
        else
            pacientes[i].pesoIdeal = 62.1 * pacientes[i].altura - 44.7;
    }

    Paciente maisPesado = pacientes[0];
    for(Paciente p : pacientes)
        if(p.peso > maisPesado.peso)
            maisPesado = p;
    
    cout << maisPesado.nome << endl;

    for(Paciente p : pacientes){
        float acima = p.pesoIdeal - p.peso;
        if(acima < 0)
            cout << p.nome << " " << acima << endl;
    }

    for(Paciente p : pacientes){
        float abaixo = p.pesoIdeal - p.peso;
        if(abaixo > 0)
            cout << p.nome << " " << abaixo << endl;
    }

    return 0;
}