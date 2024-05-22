#include<iostream>

using namespace std;

int achaMaior(int *a, int l, int r){
    if(l < r){
        int meio = (r+l)/2;
        int maiorL = achaMaior(a, l, meio);
        int maiorR = achaMaior(a, meio+1, r);
        if(a[maiorL] > a[maiorR])
            return maiorL;
        else
            return maiorR;
    }
    else
        return l;
}

int main(){
    int *a;

    int n;
    while(cin >> n and n > 0){
        a = new int[n];
        for(int i=0; i<n; i++)
            cin >> a[i];
        
        int maior = achaMaior(a, 0, n-1);

        cout << "a[" << maior << "] -> " << a[maior] << endl;

        delete [] a;
    }

    return 0;
}