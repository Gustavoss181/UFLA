#include<iostream>
using namespace std;

struct Funcionario{
	int id;
	float hrsTrab;
	float valorHrTrab;
	float salario;
};

void inserir(Funcionario v[], int tam){
	for(int i=0; i<tam; i++){
		cin >> v[i].id;
		cin >> v[i].hrsTrab;
		cin >> v[i].valorHrTrab;
		v[i].salario = v[i].hrsTrab * v[i].valorHrTrab;
	}
}

void bubbleSort(Funcionario v[], int t){
	for(int i=0; i<t-1; i++)
		for(int j=0; j<t-1-i; j++)
			if(v[j].salario > v[j+1].salario)
				swap(v[j], v[j+1]);
}

int main(){
	int tam;
	cin >> tam;
	Funcionario func[tam];
	inserir(func, tam);

	bubbleSort(func, tam);

	for(int i=0; i<tam; i++)
		cout << func[i].id << " " << func[i].salario << endl;

	return 0;
}