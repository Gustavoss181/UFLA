#include<iostream>
using namespace std;

struct Storm {
    string nome;
    string origem;
    int batalhas;
    bool lido = false;
};

void imprime(Storm dados[],int n)
{
    for(int i=0;i<n-1;i++){
        if(!dados[i].lido){
            int cont = 1;
            float media = dados[i].batalhas;
            for(int j=i+1; j<n; j++){
                if(dados[i].origem == dados[j].origem){
                    cont++;
                    media += dados[j].batalhas;
                    dados[j].lido = true;
                }
            }
            cout << dados[i].origem << " " << cont << " " << media/cont << endl;
            dados[i].lido = true;
        }
    }

    if(!dados[n-1].lido)
        cout << dados[n-1].origem << " " << 1 << " " << dados[n-1].batalhas << endl;
}

int main(){

    int n;
    cin>>n;
    Storm dados[n];

    for(int i=0;i<n;i++){
        cin>>dados[i].nome>>dados[i].origem>>dados[i].batalhas;
    }
    imprime(dados,n);

    return 0;

}