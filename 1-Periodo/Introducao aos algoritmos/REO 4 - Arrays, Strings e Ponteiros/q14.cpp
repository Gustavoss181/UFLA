#include<iostream>
using namespace std;

int* aumentaVetor(int *v, int &t){
    t+=5;
    int *novoV = new int[t];
    for(int i=0; i<t-5; i++)
        novoV[i] = v[i];
    delete []v;
    return novoV;
}

int main(){
    int t = 5;
    int *v = new int[t];

    int i=0, n;
    cin >> n; 
    while(n > 0){
        if(i==t)
            v = aumentaVetor(v, t);
        v[i] = n;
        i++;
        cin >> n;
    }

    for(int j=0; j<i; j++){
        cout << v[j] << " ";
    }
    cout << endl << t << endl << t/5 - 1;

    delete []v;

    return 0;
}