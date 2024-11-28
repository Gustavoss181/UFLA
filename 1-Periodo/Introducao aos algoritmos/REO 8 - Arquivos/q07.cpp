#include<iostream>
#include<fstream>
using namespace std;

float* aumentaVetor(float *v, int &t, float n){
    t++;
    float *novoV = new float[t];
    for(int i=0; i<t-1; i++)
        novoV[i] = v[i];
	novoV[t-1] = n;
    delete []v;
    return novoV;
}

int main(){
	string nomeArq;
	cin >> nomeArq;
	ifstream arq(nomeArq);
	if(arq){
		int tam=1;
		bool ctrl = true;
		float n;
		float *v = new float[tam];
		arq >> v[tam-1];
		while(arq >> n){
			if(ctrl){
				v[tam-1] += n;
				v[tam-1] /= 2;
				ctrl = false;
			}
			else{
				v = aumentaVetor(v, tam, n);
				ctrl = true;
			}
		}
		for(int i=0; i<tam; i++)
			cout << v[tam-i-1] << " ";
		
		delete[] v;
		arq.close();
	}

	return 0;
}