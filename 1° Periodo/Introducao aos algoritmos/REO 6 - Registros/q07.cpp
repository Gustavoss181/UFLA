#include<iostream>
using namespace std;

struct Funcionario{
    int id;
    int t;
    float* vendas;
};

float* aumentaVetor(float *v, int &t){
    t++;
    float *novoV = new float[t];
    for(int i=0; i<t-1; i++)
        novoV[i] = v[i];
    delete []v;
    return novoV;
}

Funcionario* aumentaVetor(Funcionario *v, int &t){
    t++;
    Funcionario *novoV = new Funcionario[t];
    for(int i=0; i<t-1; i++)
        novoV[i] = v[i];
    delete []v;
    return novoV;
}

int main(){
    float salFixo;
    cin >> salFixo;
    int tam=0, id;
    Funcionario* func;

    cin >> id;
    while(id > 0){
        bool ctrl = true; //variavel de controle pra saber se o funcionario já existe
        //repeticao que procura o funcionario pelo id
        for(int i=0; i<tam and ctrl; i++){
            if(func[i].id == id){
                func[i].vendas = aumentaVetor(func[i].vendas, func[i].t);
                cin >> func[i].vendas[func[i].t-1];
                ctrl = false;
            }
        }
        //caso o funcionario nao exista é criado um novo funcionario
        if(ctrl){
            func = aumentaVetor(func, tam);
            int i = tam-1;
            func[i].id = id;
            func[i].t = 1;
            func[i].vendas = new float[func[i].t];
            cin >> func[i].vendas[func[i].t-1];
        }

        cin >> id;
    }

    int idConsulta;
    cin >> idConsulta;
    int pos;
    cin >> pos;

    for(int i=0; i<tam; i++){
        cout << func[i].id << " ";
        float salFinal = salFixo;
        for(int j=0; j<func[i].t; j++)
            salFinal += func[i].vendas[j]*0.06;
        cout << salFinal << endl;

        if(func[i].id == idConsulta)
            id = i;
    }

    cout << endl;
    for(int i=pos; i<pos+3 and i<func[id].t; i++)
        cout << func[id].vendas[i] << " ";

    for(int i=0; i<tam; i++)
        delete[] func[i].vendas;
    delete[] func;

    return 0;
}