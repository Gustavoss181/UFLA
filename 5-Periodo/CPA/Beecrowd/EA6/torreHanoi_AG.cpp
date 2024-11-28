#include <iostream>
#include <cmath>

using namespace std;

bool ehQuadradoPerfeito(int n){
    int n2 = (int) sqrt(n);
    return (n2*n2 == n);
}

int nMaxBolas(int nHastes){
    int hastes[nHastes] = {0};

    int i = 0;
    while(++i){
        int j = 0;
        while(j < nHastes){
            int soma = i + hastes[j];

            if(ehQuadradoPerfeito(soma) or hastes[j] == 0){
                hastes[j] = i;
                break;
            }
            j++;
        }
        
        if(j == nHastes)
            return i-1;
    }
    return -1;
}

int main(){
    int t, nHastes;
    cin >> t;

    while(t--){
        cin >> nHastes;
        cout << nMaxBolas(nHastes) << endl;
    }

    return 0;
}