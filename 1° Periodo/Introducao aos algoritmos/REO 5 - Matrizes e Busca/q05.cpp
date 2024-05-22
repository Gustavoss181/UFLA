#include<iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    int pascal[n][n];

    for(int i=0; i<n; i++)
        for(int j=0; j<i+1; j++){
            if(j==0 or j==i)
                pascal[i][j] = 1;
            else
                pascal[i][j] = pascal[i-1][j] + pascal[i-1][j-1];
        }

    for(int i=0; i<n; i++){
        for(int j=0; j<i+1; j++)
            cout << pascal[i][j] << " ";
        cout << endl;
    }
    
    return 0;
}