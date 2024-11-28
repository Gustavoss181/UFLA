#include <iostream>
#include <iomanip>

using namespace std;

void merge(int *l, int n, int *r, int m, int *a, int &nSwaps){
    int i=0, j=0, k=0;
    while(i < n and j < m){
        if(l[i] < r[j]){
            a[k] = l[i];
            i++;
        }
        else{
            a[k] = r[j];
            nSwaps += n - i;
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

void merge_sort(int *a, int n, int &nSwaps){
    if(n > 1){
        int meio = n/2;
        int *l = new int[meio];
        for(int i=0; i<meio; i++)
            l[i] = a[i];
        int *r = new int[n-meio];
        for(int j=0; j<n-meio; j++)
            r[j] = a[meio+j];
        merge_sort(l, meio, nSwaps);
        merge_sort(r, n-meio, nSwaps);
        merge(l, meio, r, n-meio, a, nSwaps);

        delete [] l;
        delete [] r;
    }
}

int main(){
    int n;
    cin >> n;
    int *a;

    while(n > 0){
        a = new int[n];
        for(int i=0; i<n; i++)
            cin >> a[i];

        int nSwaps = 0;
        merge_sort(a, n, nSwaps);

        string vencedor = (nSwaps%2 == 0) ? "Carlos" : "Marcelo"; 

        cout << vencedor << endl;
        
        delete [] a;

        cin >> n;
    }

    return 0;
}