#include<iostream>

using namespace std;

int main(){
    string cor1, cor2, n;

    cin >> cor1 >> cor2 >> n;

    if((n[0] == n[5]) and (n[1] == n[4]) and (n[2] == n[3])){
        cout << cor1;
    }else{
        cout << cor2;
    }

    return 0;
}