#include <iostream>
using namespace std;

int main(){
	int n, primeiroDigito=10, tamanhoNum = 1, ultimoDigito, meio;
	
	cin >> n;
	
	while(primeiroDigito/10 != 0){
		tamanhoNum *= 10;
		primeiroDigito = n/tamanhoNum;
	}
	
	ultimoDigito = n%10;
	
	meio = (n - ((primeiroDigito-1)*tamanhoNum)) / 10;
	
	cout << (ultimoDigito*tamanhoNum/10)-(tamanhoNum/10) + meio << primeiroDigito;
    
    return 0;
}

// O CÓDIGO ABAIXO FUNCIONA 100% NA QUESTÃO (UTILIZANDO REPETIÇÃO) MAS EU UTILIZO STRING COMO VETOR

// #include <iostream>
// using namespace std;

// int main(){
//     string n;
// 	int tamanhoNum = 0;
	
// 	cin >> n;
	
// 	while(n[tamanhoNum] != '\0')
// 		tamanhoNum++;

//     char aux = n[0];
//     n[0] = n[tamanhoNum-1];
//     n[tamanhoNum-1] = aux;

//     cout << n;
    
//     return 0;
// }