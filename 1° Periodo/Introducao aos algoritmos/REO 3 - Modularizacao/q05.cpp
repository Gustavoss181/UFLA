#include<iostream>
using namespace std;

int fatorial(int n){
    int fat=1;

    if(n == 0)
        return 0;

    while(n>1){
        fat *= n;
        n--;
    }

    return fat;
}

int main(){
    int n;

    cin >> n;

    cout << fatorial(n);

    return 0;
}