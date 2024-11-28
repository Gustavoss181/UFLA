#include <iostream>
#include <iomanip>

using namespace std;

int main(){
    double raio;
    cin >> raio;

    const double pi = 3.14159;

    double circ = raio * raio * pi;
    cout << fixed << setprecision(4);
    cout << "A=" << circ << endl;

    return 0;
}