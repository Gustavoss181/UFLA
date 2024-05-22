#include<iostream>
#include<string>
#include<algorithm>
#include<limits.h>
using namespace std;

main(){
	string a = "@@@@@@";
	string b = "abababa";

	if(a == b)
    	cout << "Sao iguais" << endl;
	else if(a < b)
		cout << a << " e menor do que " << b << endl;
	else if(a > b)
		cout << a << " e maior do que " << b << endl;

	//srand(time(NULL));

	return 0;
}