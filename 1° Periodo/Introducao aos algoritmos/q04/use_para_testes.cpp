#include<iostream>
#include<fstream>
using namespace std;

int main(){
    ifstream numeros("numeros");
	ofstream pares("pares");
	ofstream impares("impares");

	if(numeros and pares and impares){
		int num;
		while(numeros >> num){
			if(num%2 == 0)
				pares << num << " ";
			else
				impares << num << " ";
		}

		numeros.close();
		pares.close();
		impares.close();
	}

	return 0;
}