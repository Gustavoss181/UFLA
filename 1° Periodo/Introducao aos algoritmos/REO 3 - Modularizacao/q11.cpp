#include <iostream>
using namespace std;

int ricci(int f0, int f1, int n){
	if(n == 0)
		return f0;
	else if(n == 1)
		return f1;
	else
		return ricci(f0, f1, n-1) + ricci(f0, f1, n-2);
}

int main(){
	int f0, f1, n, cont=0;
	
	cin >> f0 >> f1 >> n;
	while(cont < n){
		cout << ricci(f0, f1, cont) << " ";
		cont++;
    }
    return 0;
}
