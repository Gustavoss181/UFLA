#include <omp.h>
#include <iostream>
#include <fstream>
#include <map>
#include <mutex>

using namespace std;

#define N 50

int main(){
    ifstream arqLeitura("leitura.txt");

    if(arqLeitura){
        double time_inicio, time_fim;
        time_inicio = omp_get_wtime();

        char linha[N];
        map<char, int> mapa_caracter2qtd;
        //mutex mtx;

        while(!arqLeitura.eof()){
            arqLeitura.read(linha, N);
            int lidos = arqLeitura.gcount();

            //#pragma omp parallel for shared(linha,mapa_caracter2qtd, mtx)
            for(int i=0; i<lidos; i++){
                //#pragma omp critical
                if(mapa_caracter2qtd.find(linha[i]) == mapa_caracter2qtd.end()){
                    mapa_caracter2qtd[linha[i]] = 1;
                }
                else{
                    mapa_caracter2qtd[linha[i]]++;
                }
            }
        }

        arqLeitura.close();

        for(const auto& par : mapa_caracter2qtd){
            cout << par.first << ": " << par.second << endl;
        }
        
        time_fim = omp_get_wtime();
        cout << "Tempo: " << time_fim - time_inicio << endl;
    }

    return 0;
}