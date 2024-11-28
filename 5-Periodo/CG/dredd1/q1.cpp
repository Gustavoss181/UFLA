#include<iostream>

using namespace std;

int main(){
    double x1, y1, x2, y2;

    cin >> x1 >> y1 >> x2 >> y2;

    double m = (y2 - y1)/(x2 - x1);
    
    double q = (y1 - m*x1);

    cout << m << endl << q << endl;

    return 0;
}