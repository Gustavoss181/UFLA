#include <iostream>
using namespace std;
void selection_sort(int *v, int n){
    int i, j, min, tmp;
	for(i = 0; i < n - 1; i++){
		min = i;
		for (j = i + 1; j < n; j++) 
			if(v[j] < v[min])
				min = j;
		tmp = v[i];
		v[i] = v[min];
		v[min] = tmp;
	}
}


int main(int argc, char** argv){
	
	int tamanho = atoi(argv[1]);
	int* v=new int[tamanho];
	srand(time(NULL));
	for (int i=0;i<tamanho;i++){
		v[i]=rand()%100;
		cout << v[i] << " ";
	}
	cout << endl;
	selection_sort(v, tamanho);
	for (int i=0;i<tamanho;i++)
		cout << v[i] << " ";
	return 0;
}
