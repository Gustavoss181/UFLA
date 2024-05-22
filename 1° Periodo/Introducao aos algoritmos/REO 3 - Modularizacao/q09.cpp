#include<iostream>
using namespace std;

int fatorialDuplo(int n){
    int result = 1;
    if(n>0)
        result = n * fatorialDuplo(n-2);
    return result;
}

int main(){
    int n;

    cin >> n;

    cout << fatorialDuplo(n);

    return 0;
}