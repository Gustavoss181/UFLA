#include<iostream>
#include<iomanip>

using namespace std;

int main(){
    int codP, pais;
    float pesoKg, pesoG, precoB, imp, precoT;

    cin >> codP >> pesoKg >> pais;

    pesoG = pesoKg*1000;

    if(codP>=1 and codP<=4)
        precoB = pesoG*10;
    else if(codP>=5 and codP<=7)
        precoB = pesoG*25;
    else if(codP>=8 and codP<=10)
        precoB = pesoG*35;

    if(pais == 1)
        imp = 0;
    else if(pais == 2)
        imp = precoB*0.15;
    else if(pais == 3)
        imp = precoB*0.25;
    
    precoT = precoB + imp;

    cout << fixed << setprecision(1);
    cout << pesoG << endl << precoB << endl;
    cout << imp << endl << precoT << endl;

    return 0;
}