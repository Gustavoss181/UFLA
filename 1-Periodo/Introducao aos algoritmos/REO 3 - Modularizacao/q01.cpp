#include<iostream>
using namespace std;

void triangulo(int n){
    int linha = 1;
    while(linha <= n){
        int c = 1;
        while(c <= linha){
            cout << c << " ";
            c++;
        }
        linha++;
        cout << endl;
    }
}

int main(){
    int n;

    cin >> n;

    triangulo(n);

    return 0;
}