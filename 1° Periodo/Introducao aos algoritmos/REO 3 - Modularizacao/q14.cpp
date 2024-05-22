#include<iostream>
using namespace std;

float calculaDistancia(float s0, float v, float t){
    return s0 + v*t;
}

int main(){
    float distanciaKm, velMediaKmH, qtdTempoH;

    cin >> distanciaKm;

    while(distanciaKm >= 0){
        cin >> velMediaKmH >> qtdTempoH;

        float deltaS = calculaDistancia(distanciaKm, velMediaKmH, qtdTempoH);
        
        cout << deltaS/1.852 << " " << deltaS/velMediaKmH << endl;

        cin >> distanciaKm;
    }

    return 0;
}