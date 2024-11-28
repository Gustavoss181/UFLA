#include<iostream>
using namespace std;

struct Funcionario{
    int id;
    float venda;
	bool flag;
};

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
        func = aumentaVetor(func, tam);
		int i = tam-1;
		func[i].id = id;
		cin >> func[i].venda;
		func[i].flag = true;
        cin >> id;
    }

	int idConsulta;
    cin >> idConsulta;
    int pos;
    cin >> pos;

	for(int i=0; i<tam; i++){
		if(func[i].flag){
			float sal = salFixo + func[i].venda*0.06;
			for(int j=i+1; j<tam; j++){
				if(func[j].id == func[i].id){
					sal += func[j].venda*0.06;
					func[j].flag = false;
				}
			}
			cout << func[i].id << " " << sal << endl;
		}
	}

	cout << endl;

	int cont = 0, cont2 = 0;
	for(int i=0; i<tam and cont2 < 3; i++){
		if(func[i].id == idConsulta){
			if(cont == pos){
				cout << func[i].venda << " ";
				cont2++;
				pos++;
			}
			cont++;
		}
	}

    delete[] func;

    return 0;
}