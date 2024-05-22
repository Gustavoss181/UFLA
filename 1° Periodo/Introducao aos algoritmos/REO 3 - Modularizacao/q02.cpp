#include<iostream>
using namespace std;

string retornaMes(int num){
    if(num == 1)
        return "janeiro";
    else if(num == 2)
        return "fevereiro";
    else if(num == 3)
        return "marco";
    else if(num == 4)
        return "abril";
    else if(num == 5)
        return "maio";
    else if(num == 6)
        return "junho";
    else if(num == 7)
        return "julho";
    else if(num == 8)
        return "agosto";
    else if(num == 9)
        return "setembro";
    else if(num == 10)
        return "outubro";
    else if(num == 11)
        return "novembro";
    else if(num == 12)
        return "dezembro";
    else
        return "erro";
}

int main(){
    int numMes;

    cin >> numMes;

    cout << retornaMes(numMes);

    return 0;
}