#include <iostream>
#include <cmath>
using namespace std;

int main(){
	double n, pi=1, i=1;
	
	cin >> n;
	
	while(i<=n){
		double num=0;
		int cont=0;
		while(cont < i){
			num = sqrt(2+num);
			cont++;
		}
		pi *= num/2;
		i++;
	}
    
    cout << 2/pi;
    return 0;
}