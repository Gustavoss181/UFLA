#include <iostream>
using namespace std;

int elementosValidos(int v[], int n){
	int cont = 0;
	for(int i=0; i<n; i++){
		if(v[i]%3 == 0 and v[i] != 0)
			v[i] = -1;
        else
            cont++;
	}
	return cont;
}

int main(){
	int n;
	cin >> n;
	int v[n];
	for(int i=0; i<n; i++)
		cin >> v[i];
	
	int validos = elementosValidos(v, n);
	
	for(int i=0; i<n; i++)
		if(v[i] != -1)
			cout << v[i] << " ";
    cout << endl << validos;
    
    return 0;
}