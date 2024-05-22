#include <iostream>
#include <iomanip>

using namespace std;

void merge(string *l, int n, string *r, int m, string *a, long long int &nSwaps){
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

void merge_sort(string *a, int n, long long int &nSwaps){
    if(n > 1){
        int meio = n/2;
        string *l = new string[meio];
        for(int i=0; i<meio; i++)
            l[i] = a[i];
        string *r = new string[n-meio];
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
    string *a;

    while(cin >> n){
        a = new string[n];
        for(int i=0; i<n; i++)
            cin >> a[i];

        long long int nSwaps = 0;
        merge_sort(a, n, nSwaps);

        cout << nSwaps << endl;
        
        delete [] a;
    }

    return 0;
}