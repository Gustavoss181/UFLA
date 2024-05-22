#include<iostream>
using namespace std;

int fatorial(int n){
    if(n==1 or n==0)
        return 1;
    else
        return n * fatorial(n-1);
}

int main(){
    string s;
    cin >> s;
    int n = s.size();

    int den = 1;
    for(int i=0; i<n; i++){
        int cont=1;
        if(s[i] != '#')
            for(int j=i+1; j<n; j++){
                if(s[i] == s[j] ){
                    cont++;
                    s[j] = '#';
                }
            }
        den *= fatorial(cont);
    }

    cout << fatorial(n)/den;

    return 0;
}