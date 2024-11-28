#include<iostream>
using namespace std;

void horasMinutos(int mnts, int *h, int *m){
    *h = mnts/60;
    *m = mnts%60;
}

int main(){
    int mnts, h, m;
    cin >> mnts;

    horasMinutos(mnts, &h, &m);

    cout << h << endl << m;

    return 0;
}