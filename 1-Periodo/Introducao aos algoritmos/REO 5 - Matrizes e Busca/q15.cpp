#include<iostream>
using namespace std;

int main(){
    int t1, t2;
    cin >> t1 >> t2;
    int v1[t1];
    for(int i=0; i<t1; i++)
        cin >> v1[i];
    int v2[t2];
    for(int i=0; i<t2; i++)
        cin >> v2[i];

    bool ctrl = false;

    for(int i=0; i<t1; i++){
        for(int j=0; j<t2; j++){
            if(v1[i] == v2[j] and v1[i+1] == v2[j+1]){
                ctrl = true;
                cout << v2[j] << " " << v2[j+1] << " ";
                int k;
                for(k=2; k<t2 and v1[i+k] == v2[j+k]; k++)
                    cout << v2[j+k] << " ";
                cout << endl;
                i += k-1;
            }
        }
    }

    if(!ctrl)
        cout << "ERRO";

    return 0;
}