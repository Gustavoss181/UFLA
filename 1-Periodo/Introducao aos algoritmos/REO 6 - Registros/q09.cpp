#include<iostream>
using namespace std;

int main(){
    int n, m;
    cin >> n;
    int l1[n], l2[n];
    for(int i=0; i<n; i++)
        cin >> l1[i];
    for(int i=0; i<n; i++)
        cin >> l2[i];
    cin >> m;

    int p1=-1, p2=-1;
    for(int i=0; i<n; i++){
        if(l1[i] == m and p1==-1)
            p1 = i;
        int j = n-1-i;
        if(l2[j] == m and p2==-1)
            p2 = j;
    }

    if(p1 <= p2){
        for(int i=p1; i<p2+1; i++)
            cout << l1[i] << endl;
        for(int i=p1; i<p2+1; i++)
            cout << l2[i] << endl;
    }
    else{
        for(int i=p2; i<p1+1; i++)
            cout << l1[i] << endl;
        for(int i=p2; i<p1+1; i++)
            cout << l2[i] << endl;
    }
    return 0;
}