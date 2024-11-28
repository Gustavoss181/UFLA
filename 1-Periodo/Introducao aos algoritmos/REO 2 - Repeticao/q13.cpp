#include <iostream>
using namespace std;

int main(){
	int N;
	
	cin >> N;

	while(N!=0){
		int cont = 0;
		while(cont<N){
			int aux = 1;
			int media;
			char resp = 64;
			while(aux <= 5){
				cin >> media;
				if(media <= 127 and resp == 64)
					resp += aux;
				else if(resp != 64 and media <= 127)
					resp = '*';
				aux++;
			}
			if(resp == 64)
				resp = '*';
			cout << endl << resp;
			cont++;
		}
		cin >> N;
	}
    
    return 0;
}