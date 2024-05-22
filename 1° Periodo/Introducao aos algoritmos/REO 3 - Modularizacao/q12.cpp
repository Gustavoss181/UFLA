#include <iostream>
using namespace std;

int multi(int n1, int n2){
	if(n2 == 0)
		return 0;
	n2--;
	if(n2>0)
		n1 += multi(n1, n2);
	return n1;
}

int main(){
	int n1, n2;
	
	cin >> n1 >> n2;
	
	cout << multi(n1, n2);
    
    return 0;
}
