#include <iostream>

using namespace std;

long solucao_PD(long v[], int n){
    long dp[n][2];
    for (int i=0; i < n-1; i++)
        dp[i][0] = max(v[i], v[i+1]);

    int rodada = 0, rodadaAnt = 1;
    for (int tamIntervalo = 4; tamIntervalo <= n; tamIntervalo += 2){
        rodadaAnt = rodada;
        rodada = rodada ? 0 : 1;
        for (int i = 0, j = tamIntervalo - 1; j < n; i++, j++) {
            dp[i][rodada] = max(v[i] + min(dp[i+1][rodadaAnt], dp[i+2][rodadaAnt]),
                                v[j] + min(dp[i][rodadaAnt], dp[i+1][rodadaAnt]));
        }
    }
    return dp[0][rodada];
}

int main(){
    int n;

    while(cin >> n){
        long v[n];
        for(int i=0; i<n; i++)
            cin >> v[i];
        
        cout << solucao_PD(v, n) << endl;
    }

    return 0;
}