#include<iostream>

using namespace std;

int main(){
    float B, b, h, area;

    cin >> B;
    cin >> b;
    cin >> h;

    area = ((B+b)*h)/2;

    cout << area;

    return 0;
}