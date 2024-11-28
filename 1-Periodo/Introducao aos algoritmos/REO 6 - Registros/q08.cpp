#include<iostream>
using namespace std;

struct Cartinha{
    string nome;
    string pedido;
};

struct Brinquedo{
    string nome;
    int qtdDisp;
    int qtdPedida;
};

int main(){
    int nCart;
    cin >> nCart;
    Cartinha cartinhas[nCart];
    for(int i=0; i<nCart; i++)
        cin >> cartinhas[i].nome >> cartinhas[i].pedido;
    
    int nBrin;
    cin >> nBrin;
    Brinquedo brinquedos[nBrin];
    for(int i=0; i<nBrin; i++){
        cin >> brinquedos[i].nome >> brinquedos[i].qtdDisp;
        brinquedos[i].qtdPedida = 0;
    }

    for(int i=0; i<nBrin; i++)
        for(int j=0; j<nCart; j++)
            if(brinquedos[i].nome == cartinhas[j].pedido)
                brinquedos[i].qtdPedida++;

    for(int i=0; i<nBrin; i++)
        if(brinquedos[i].qtdDisp < brinquedos[i].qtdPedida)
            cout << brinquedos[i].nome << " ";
    
    return 0;
}