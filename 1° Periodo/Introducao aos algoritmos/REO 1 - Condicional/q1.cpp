#include<iostream>

using namespace std;

int main(){
    int num, den, quo, resto;

    cin >> num;
    cin >> den;

    if(den == 0){
        cout << "erro";
    }
    else{
        quo = num/den;
        resto = num%den;
        cout << quo << endl << resto;
    }

    return 0;
}