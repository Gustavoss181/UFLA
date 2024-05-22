#include <iostream>

using namespace std;

void prova(string *a, int n, int k){
    for(int i=0; i<n-1; i++){
        int menor = i;
        for(int j=1; j<=k and i+j<n; j++){
            if(a[menor] > a[i+j]){
                menor = i+j;
            }
        }
        if(menor != i){
            for(int j=menor; j>i; j--)
                swap(a[j], a[j-1]);
            k -= menor - i;
        }
    }
}

int main(){
    int n, k;
    string *a;

    cin >> n >> k;

    int instancia = 1;
    while(!(n == 0 and k == 0)){
        a = new string[n];
        for(int i=0; i<n; i++)
            cin >> a[i];
        
        prova(a, n, k);

        cout << "Instancia " << instancia << endl;
        for(int i=0; i<n; i++){
            cout << a[i] << " ";
        }
        cout << endl << endl;
        instancia++;

        delete [] a;

        cin >> n >> k;
    }

    return 0;
}