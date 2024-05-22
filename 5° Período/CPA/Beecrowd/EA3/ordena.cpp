#include <iostream>
#include <iomanip>

using namespace std;

bool bubble(int *a, int n){
    bool nome = true;
    for(int i=0; i<n-1; i++){
        bool troca = false;
        for(int j=0; j<n-i-1; j++)
            if(a[j] > a[j+1]){
                nome = !nome;
                troca = true;
                swap(a[j], a[j+1]);
            }
        if(!troca)
            break;
    }
    return nome;
}

int main(){
    int n;
    cin >> n;
    int *a;

    while(n > 0){
        a = new int[n];
        for(int i=0; i<n; i++)
            cin >> a[i];

        bool nome = bubble(a, n);

        if(!nome)
            cout << "Marcelo" << endl;
        else
            cout << "Carlos" << endl;
        
        delete [] a;

        cin >> n;
    }
    

    return 0;
}