#include<iostream>

using namespace std;

int main(){
    char letra;

    cin >> letra;

    if(letra <= 'Z'){
        cout << "MAIUSCULA";
    }else{
        cout << "MINUSCULA";
    }

    return 0;
}