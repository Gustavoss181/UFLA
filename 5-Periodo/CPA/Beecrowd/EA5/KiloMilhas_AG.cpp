#include <iostream>
#include <vector>

using namespace std;

vector<int> fibonacci_PD(int x){
    vector<int> fib;
    fib.push_back(1); // [0] <- 1
    fib.push_back(1); // [1] <- 1
    int i = 1;
    while(fib.back() < x){
        fib.push_back(fib[i] + fib[i-1]);
        i++;
    }
    return fib;
}

// algoritmo de Bruce
int conversor_km_milhas(int x){
    vector<int> fib = fibonacci_PD(x);

    int i = fib.size() - 1;
    int milha = 0;
    while(x > 0 and i > 1){
        if(x >= fib[i]){
            x -= fib[i];
            milha += fib[i-1];
        }
        i--;
    }

    return milha;
}

int main(){
    int t, a;

    cin >> t;
    for(int i=0; i<t; i++){
        cin >> a;
        cout << conversor_km_milhas(a) << endl;
    }

    return 0;
}