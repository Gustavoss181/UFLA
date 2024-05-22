#include <iostream>

using namespace std;

void merge(int l[], int n, int r[], int m, int *a){
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

void merge_sort(int a[], int n){
    if(n > 1){
        int meio = n/2;
        int l[meio];
        for(int i=0; i<meio; i++)
            l[i] = a[i];
        int r[n-meio];
        for(int j=0; j<n-meio; j++)
            r[j] = a[meio+j];
        merge_sort(l, meio);
        merge_sort(r, n-meio);
        merge(l, meio, r, n-meio, a);
    }
}

int solucao(int n, int k, int v[]){
    int nDist = n-1;
    int vDist[nDist];
    for(int i=0; i<nDist; i++)
        vDist[i] = v[i+1] - v[i];
    
    merge_sort(vDist, nDist);

    int soma = 0;
    for(int i=k-1; i<nDist; i++)
        soma += vDist[i];
    
    return soma;
}

int main(){
    int n, k;

    while(cin >> n >> k){
        int v[n];
        v[0] = 0;
        for(int i=1; i<n; i++)
            cin >> v[i];
        
        cout << solucao(n, k, v) << endl;
    }

    return 0;
}