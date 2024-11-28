#include<iostream>
using namespace std;

int main(){
    int nLinhas, i = 0, c = 97;

    cin >> nLinhas;

    while (i < nLinhas){
        i++;
        int j = 0;
        while(j < i){
            cout << (char)(c+j) << " ";
            j++;
        }
        cout << endl;
    }

    return 0;
}