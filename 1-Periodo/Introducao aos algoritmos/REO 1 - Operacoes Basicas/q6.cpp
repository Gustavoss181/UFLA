#include<iostream>
#include<cmath>

using namespace std;

int main(){
    int homens, caravelas;

    cin >> homens;

    homens-=1000;

    caravelas = ceil(homens/80.0);

    cout << caravelas;

    return 0;
}