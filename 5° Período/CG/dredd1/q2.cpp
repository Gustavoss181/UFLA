#include<iostream>

using namespace std;

int main(){
    int largura, altura, x, y;

    cin >> largura >> altura >> x >> y;

    double metadeL = largura/2, metadeA = altura/2;

    cout << (x - metadeL) / metadeL << endl;

    cout << (metadeA - y) / metadeA << endl;

    return 0;
}