#include<iostream>
using namespace std;

void somaPorReferencia(int n1, int n2, int &n3){
    n3 = n1+n2;
}

int main(){
    int n1, n2, n3;

    cin >> n1 >> n2;

    somaPorReferencia(n1, n2, n3);

    cout << n3;

    return 0;
}