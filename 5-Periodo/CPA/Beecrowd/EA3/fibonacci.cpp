#include <iostream>
#include <iomanip>

using namespace std;

int fibonacci(int x, int &cont){
    cont++;
    
    if(x == 0) return 0;

    else if(x == 1) return 1;

    else return fibonacci(x-1, cont) + fibonacci(x-2, cont);
}

int main(){
    int n;
    cin >> n;

    for(int i=0; i<n; i++){
        int x, cont = 0;
        cin >> x;

        int r = fibonacci(x, cont);

        cout << "fib(" << x << ") = " << cont-1 << " calls = " << r << endl;
    }
    

    return 0;
}