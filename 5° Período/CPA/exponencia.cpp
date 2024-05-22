#include<iostream>

using namespace std;

int exponenciador(int a, int n){
    if(n > 1){
        int meio = n/2;
        int l = exponenciador(a, meio);
        int r = exponenciador(a, n-meio);
        return l*r;
    }
    return a;
}

int main(){
    int a, n;
    while(cin >> a >> n and n > 0){
        int e = exponenciador(a, n);
        cout << e << endl;
    }

    return 0;
}