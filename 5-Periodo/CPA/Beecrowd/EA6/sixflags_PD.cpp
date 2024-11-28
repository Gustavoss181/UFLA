#include <iostream>

using namespace std;

int mochila_PD(int t, int d[], int p[], int n){
    int c[t+1] = {0};
    
    for(int i=0; i<=t; i++)
        for(int j=0; j<n; j++)
            if(i >= d[j])
                c[i] = max(c[i], c[i-d[j]] + p[j]);
    
    return c[t];
}

int main(){
    int n, t, cont = 0;

    while(cin >> n >> t and n and t){
        int d[n];
        int p[n];
        for(int i=0; i<n; i++)
            cin >> d[i] >> p[i];
        
        cout << "Instancia " << ++cont << endl;
        cout << mochila_PD(t, d, p, n) << endl << endl;
    }

    return 0;
}