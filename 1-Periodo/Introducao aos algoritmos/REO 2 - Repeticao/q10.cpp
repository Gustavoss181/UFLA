#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;

int main(){
    double raio, angulo;
    int qtdCadeiras;
    double pi = 2*acos(0.0);

    cin >> raio >> qtdCadeiras;
    cout << fixed << setprecision(2);

    angulo = 360/qtdCadeiras;
    
    int i = 0;
    while(i<qtdCadeiras){
        cout << raio * cos((angulo*i)*pi/180) << " ";
        cout << raio * sin((angulo*i)*pi/180) << endl;
        i++;
    }

    return 0;
}