#include<iostream>
using namespace std;

int main(){
    int divisor, dividendo, cont = -1;

    cin >> dividendo >> divisor;
    
    while(dividendo >= 0){
        dividendo -= divisor;
        cont++;
    }

    cout << cont;

    return 0;
}