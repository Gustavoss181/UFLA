#include <iostream>

using namespace std;

int main(){
    int n;
    while(cin >> n){
        string matriculas[n];
        for(int i=0; i<n; i++){
            cin >> matriculas[i];
        }

        int cont = 0;
        for(int i=0; i<n-1; i++)
            for(int j=i+1; j<n; j++)
                if(matriculas[i] > matriculas[j])
                    cont++;

        cout << cont << endl;
    }

    return 0;
}