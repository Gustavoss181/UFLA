#include<iostream>
#include<iomanip>

using namespace std;

int main(){
    int mili, hrs, min;
    float seg;

    cin >> mili;

    hrs = mili/3600000;
    mili %= 3600000;
    min = mili/60000;
    mili %= 60000;
    seg = mili/1000.0;

    cout << fixed << setprecision(1);
    cout << hrs << " : " << min << " : " << seg;

    return 0;
}