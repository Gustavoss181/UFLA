#include<iostream>
using namespace std;

int fibonacci(int n){
    if(n==0)
        return 0;
    else if(n==1)
        return 1;
    else
        return fibonacci(n-1) + fibonacci(n-2);
}

int main(){
    int n, cont=0;

    cin >> n;

    while(cont < n){
        cout << fibonacci(cont) << " ";
        cont++;
    }

    return 0;
}