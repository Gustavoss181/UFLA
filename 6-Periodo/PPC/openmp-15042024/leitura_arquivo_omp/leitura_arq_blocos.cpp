#include <omp.h>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int main(){
    ifstream arq("leitura.txt");

    if(arq){
        double time_inicio, time_fim;
        time_inicio = omp_get_wtime();

        // conta quantos caracteres têm no arquivo
        arq.seekg(0, arq.end);
        size_t tamArq = arq.tellg();
        arq.seekg(0, arq.beg);

        // traz todo o conteúdo do arquivo e armazena na memória
        char buffer[tamArq]; // E se o buffer tiver consumindo muito espaço na memoria?
        arq.read(buffer, tamArq);
        arq.close();

        // define o numero de maps que serão usados de acordo com o numero de threads disponiveis
        int nBlocos = omp_get_max_threads();
        map<char, int> mapasLocais[nBlocos];

        #pragma omp parallel
        {
            int tid = omp_get_thread_num();
            size_t tamBloco = tamArq/nBlocos;
            size_t inicioBloco = tid * tamBloco;
            size_t finalBloco = (tid == nBlocos-1) ? tamArq : inicioBloco + tamBloco;

            for(size_t i = inicioBloco; i < finalBloco; ++i){
                mapasLocais[tid][buffer[i]]++; // acessa o mapa reservado para aquela thread, acessa a chave pelo caracter do buffer e add 1 no valor
            }
        }

        map<char, int> juncaoMapas;
        for(const auto& mapaLocal : mapasLocais){
            for(const auto& par : mapaLocal){
                juncaoMapas[par.first] += par.second;
            }
        }

        for(const auto& par : juncaoMapas){
            cout << par.first << ": " << par.second << endl;
        }

        time_fim = omp_get_wtime();
        cout << "Tempo: " << time_fim - time_inicio << endl;
    }

    return 0;
}