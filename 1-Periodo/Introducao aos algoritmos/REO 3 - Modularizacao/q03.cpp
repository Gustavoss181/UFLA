#include<iostream>
using namespace std;

float cmParaM(float d){
    return d/100;
}

float mParaCm(float d){
    return d*100;
}

int main(){
    float distancia;
    string unidade;

    cin >> distancia >> unidade;

    if(unidade == "metro")
        cout << cmParaM(distancia) << " m";
    else if(unidade == "centimetro")
        cout << mParaCm(distancia) << " cm";

    return 0;
}