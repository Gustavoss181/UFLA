#include<iostream>
#include<cmath>
using namespace std;

struct Habitante{
    float salario;
    int idade;
    int nFilhos;
};

int main(){
    int n;
    cin >> n;
    Habitante habitantes[n];
    for(int i=0; i<n; i++){
        cin >> habitantes[i].salario;
        cin >> habitantes[i].idade;
        cin >> habitantes[i].nFilhos;
    }

    float mediaSal = 0, mediaNFi = 0, maiorSal = habitantes[0].salario;
    int porc = 0;

    for(Habitante h : habitantes){
        mediaSal += h.salario;
        mediaNFi += h.nFilhos;
        if(maiorSal < h.salario)
            maiorSal = h.salario;
        if(h.salario > 1000)
            porc++;
    }

    cout << mediaSal/n << endl;
    cout << mediaNFi/n << endl;
    cout << maiorSal << endl;
    cout << round(porc*(100.0/n)) << '%' << endl;

    return 0;
}