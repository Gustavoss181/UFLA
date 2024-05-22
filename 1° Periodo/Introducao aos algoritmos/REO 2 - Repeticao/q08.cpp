#include<iostream>
using namespace std;

int main(){
    float maior, segMaior, num, media = 0;
    int i = 0;

    while(i < 7){
        i++;

        cin >> num;

        if(i == 0){
            maior = num;
        }
        else if(i == 1){
            if(num > maior){
                segMaior = maior;
                maior = num;
            }
            else
                segMaior = num;
        }
        else{
            if(num > maior){
                segMaior = maior;
                maior = num;
            }
            else if(num > segMaior){
                segMaior = num;
            }
        }

        media += num;
    }
    cout << maior << endl;
    cout << segMaior << endl;
    cout << (media - (maior + segMaior))/5;

    return 0;
}