#include <iostream>
using namespace std;

int main(){
	int n, linha=0, col;
	
	cin >> n;
	
	while(linha<n){
		col=0;
		while(col<n){
			if((linha+col)%2==0)
				cout << '.';
			else
				cout << '#';
			col++;
		}
		linha++;
		cout << endl;
	}
    
    return 0;
}
