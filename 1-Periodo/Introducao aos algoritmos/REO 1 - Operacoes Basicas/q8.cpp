#include<iostream>
#include<cmath>

using namespace std;

int main(){
    float x1, y1, x2, y2, D;

    cin >> x1;
    cin >> y1;
    cin >> x2;
    cin >> y2;

    D = sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));

    cout << D;

    return 0;
}