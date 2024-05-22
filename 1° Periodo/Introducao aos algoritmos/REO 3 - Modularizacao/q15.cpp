#include<iostream>
using namespace std;

long fatorial(int n){
    if(n==1 or n==0)
        return 1;
    else
        return n * fatorial(n-1);
}
long combinacao(int n, int k){
    return fatorial(n) / (fatorial(k) * fatorial(n-k));
}

long somatorio(int n){
    long soma = 0;
    int k=1;
    while(k <= n){
        soma += combinacao(n, k);
        k++;
    }
    return soma;
}

int main(){
    int n;

    cin >> n;

    cout << somatorio(n);

    return 0;
}