#include<iostream>

using namespace std;

int main(){
    float mat, nat, lin, red, hum, media;

    cin >> mat >> nat >> lin >> red >> hum;

    if(red < 200){
        cout << -1;
    }else{
        media = (3*mat + 2*nat + 2*lin + 2*red + hum)/10;
        cout << media;
    }

    return 0;
}