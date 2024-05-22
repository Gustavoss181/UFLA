#include<iostream>
using namespace std;

void soma(int N, float &S){
    float n = 1;

    while(n<=N){
        S += (n*(n+1))/(n+3);
        n++;
    }
}

int main(){
    int N;
    float S = 0;

    cin >> N;

    soma(N, S);

    cout << S;

    return 0;
}