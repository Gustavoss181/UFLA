#include<iostream>
using namespace std;

int menor(int v[], int n, int &pos){
    pos = n-1;
    if(n-1==0)
        return v[0];
    else{
        int m = menor(v, n-1, pos);
        if(m <= v[n-1])
            return m;
        else{
            pos = n-1;
            return v[n-1];
        }
    }
}

int main(){
    int n;
    cin >> n;
    int v[n];
    for(int i=0; i<n; i++)
        cin >> v[i];

    int pos;
    int me = menor(v, n, pos);

    cout << me << " " << pos;

    return 0;
}