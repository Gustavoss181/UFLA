#include<iostream>

using namespace std;

int main(){
    double x1, y1, x2, y2;

    cin >> x1 >> y1 >> x2 >> y2;

    double m = (y2 - y1)/(x2 - x1);
    
    double q = (y1 - m*x1);
    
    char reta;
    double valorReta;

    cin >> reta >> valorReta;

    if(reta == 'x'){
        if(y1 == y2)
            cout << y1 << endl;
        else if(x1 == x2)
            cout << "nenhuma" << endl;
        else
            cout << m*valorReta + q << endl;
    }
    else{
        if(x1 == x2)
            cout << x1 << endl;
        else if(y1 == y2)
            cout << "nenhuma" << endl;
        else
            cout << (valorReta - q)/m << endl;
    }

    return 0;
}

// cout << (((valorReta - x1) / (x2 - x1)) * (y2 - y1)) + y1;