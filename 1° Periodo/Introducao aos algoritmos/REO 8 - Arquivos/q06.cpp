#include<iostream>
#include<fstream>
using namespace std;

struct Navio{
	int id;
	int x;
	int y;
	int tam;
	char dir;//h == horizontal e v == vertical
};

int main(){
	ifstream arq("BatalhaNaval.txt");

	if(arq){
		//inserção dos dados
		int tam;
		arq >> tam;
		int **mapa = new int*[tam];
		for(int i=0; i<tam; i++){
			mapa[i] = new int [tam];
			for(int j=0; j<tam; j++)
				arq >> mapa[i][j];
		}
		int **tiros = new int*[tam];
		for(int i=0; i<tam; i++){
			tiros[i] = new int [tam];
			for(int j=0; j<tam; j++)
				arq >> tiros[i][j];
		}
		
		//resolução
		Navio navios[tam*tam/2];
		int pos = 0;
		for(int i=0; i<tam; i++){
			for(int j=0; j<tam-1; j++){
				//ver se tem um navio em uma linha
				if(mapa[i][j] == mapa[i][j+1] and mapa[i][j] != 0){
					navios[pos].id = mapa[i][j];
					navios[pos].y = i;
					navios[pos].x = j;
					navios[pos].tam = 2;
					navios[pos].dir = 'h';
					while((j+navios[pos].tam) < tam and mapa[i][j] == mapa[i][j+navios[pos].tam])
						navios[pos].tam++;
					j += navios[pos].tam-1;
					pos++;
				}
			}
		}

		for(int j=0; j<tam; j++){
			for(int i=0; i<tam-1; i++){
				//ver se tem um navio em uma coluna
				if(mapa[i][j] == mapa[i+1][j] and mapa[i][j] != 0){
					navios[pos].id = mapa[i][j];
					navios[pos].y = i;
					navios[pos].x = j;
					navios[pos].tam = 2;
					navios[pos].dir = 'v';
					while((i+navios[pos].tam) < tam and mapa[i][j] == mapa[i+navios[pos].tam][j])
						navios[pos].tam++;
					i += navios[pos].tam-1;
					pos++;
				}
			}
		}

		for(int i=0; i<tam; i++)
			for(int j=0; j<tam; j++)
				if(tiros[i][j] == 1)
					mapa[i][j] = 0;

		int naviosDestruidos = 0;
		for(int i=0; i<pos; i++){
			int soma = 0;
			if(navios[i].dir == 'h')
				for(int j=0; j<navios[i].tam; j++)
					soma += mapa[navios[i].y][navios[i].x+j];
			else
				for(int j=0; j<navios[i].tam; j++)
					soma += mapa[navios[i].y+j][navios[i].x];
			if(soma == 0)
				naviosDestruidos++;
		}

		cout << naviosDestruidos << endl;
		
		//exclusão
		for(int i=0; i<tam; i++)
			delete[] mapa[i];
		delete[] mapa;
		for(int i=0; i<tam; i++)
			delete[] tiros[i];
		delete[] tiros;
		arq.close();
	}

	return 0;
}