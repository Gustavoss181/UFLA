#include <iostream>

using namespace std;

void merge(long l[], int n, long r[], int m, long a[]){
    int i=0, j=0, k=0;
    while(i < n and j < m){
        if(l[i] > r[j]){
            a[k] = l[i];
            i++;
        }
        else{
            a[k] = r[j];
            j++;
        }
        k++;
    }
    while(i < n){
        a[k] = l[i];
        i++;
        k++;
    }
    while(j < m){
        a[k] = r[j];
        j++;
        k++;
    }
}

void merge_sort(long a[], int n){
    if(n > 1){
        int meio = n/2;
        long l[meio];
        for(int i=0; i<meio; i++)
            l[i] = a[i];
        long r[n-meio];
        for(int j=0; j<n-meio; j++)
            r[j] = a[meio+j];
        merge_sort(l, meio);
        merge_sort(r, n-meio);
        merge(l, meio, r, n-meio, a);
    }
}

long solucao(long v[], int n){
    merge_sort(v, n);

    long soma = 0;
    for(int i=0; i<n; i+=2)
        soma += v[i];
    
    return soma;
}

int main(){
    int n;

    while(cin >> n){
        long v[n];
        for(int i=0; i<n; i++)
            cin >> v[i];
        
        cout << solucao(v, n) << endl;
    }

    return 0;
}