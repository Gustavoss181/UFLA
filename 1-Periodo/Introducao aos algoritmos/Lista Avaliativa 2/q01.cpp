#include<iostream>
using namespace std;

bool vogal(char l){
    if(l == 'A' or l == 'E' or l == 'I' or l == 'O' or l == 'U')
        return true;
    return false;
}

int main(){
    int n;
    cin >> n;
    char m[n][n], resp[2][2];
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> m[i][j];
    
    bool ctrl = false;
    for(int i=0; i<n-1; i++)
        for(int j=0; j<n-1; j++)
            if(vogal(m[i][j]) and vogal(m[i+1][j]) and vogal(m[i][j+1]) and vogal(m[i+1][j+1])){
                resp[0][0] = m[i][j];
                resp[1][0] = m[i+1][j];
                resp[0][1] = m[i][j+1];
                resp[1][1] = m[i+1][j+1];
                i=n;
                j=n;
                ctrl = true;
            }

    if(ctrl){
        cout << resp[0][0] << " " << resp[0][1] << endl;
        cout << resp[1][0] << " " << resp[1][1];
    }
    else
        cout << "submatriz nao encontrada";

    return 0;
}