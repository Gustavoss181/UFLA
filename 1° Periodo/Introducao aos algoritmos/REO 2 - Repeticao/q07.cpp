#include<iostream>
using namespace std;

int main(){
    int nFichas, contM = 0, contF = 0;
    float H, maiorH = -1, menorH = 999999, mediaF = 0, mediaM = 0, mediaGeral = 0;
    char sexo;

    cin >> nFichas;

    while(nFichas > 0){
        nFichas--;
        cin >> H >> sexo;

        if(H > maiorH)
            maiorH = H;

        if(H < menorH)
            menorH = H;

        if(sexo == 'm'){
            mediaM += H;
            contM++;
        }

        if(sexo == 'f'){
            mediaF += H;
            contF++;
        }

        mediaGeral += H;
    }

    cout << maiorH << endl;
    cout << menorH << endl;
    if(mediaF == 0)
        cout << "erro" << endl;
    else
        cout << mediaF/contF << endl;
    if(mediaM == 0)
        cout << "erro" << endl;
    else
        cout << mediaM/contM << endl;
    cout << mediaGeral/(contF+contM) << endl;

    return 0;
}