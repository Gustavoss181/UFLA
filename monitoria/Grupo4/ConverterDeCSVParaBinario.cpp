#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <algorithm>
using namespace std;

struct registro{
    long long int campo1;
    char campo2[10];
    char campo3[200];
    float campo4;
    float campo5;
};

int main(){
	ifstream entrada("base9_OK.csv");
	ofstream saida("base9_binario.dat", ios::binary);
    string linha;
    registro campo;

	if (!entrada){
        cout << "Erro ao abrir o arquivo de entrada" << endl;
    return 1;
    }else{

        while(getline(entrada,linha)){

            stringstream linhastream(linha);
            string item;

            getline(linhastream, item, ';');
            campo.campo1 = stoll(item);

            getline(linhastream, item, ';');
            strcpy(campo.campo2, item.c_str());

            getline(linhastream, item, ';');
            strcpy(campo.campo3, item.c_str());

            getline(linhastream, item, ';');
            replace(item.begin(), item.end(), ',', '.');
            campo.campo4 = stof(item);

            getline(linhastream, item, '\n');
            replace(item.begin(), item.end(), ',', '.');
            campo.campo5 = stof(item);         

            saida.write((const char *) (&campo), sizeof(registro));

        }
        cout << "Arquivo convertido!";

    }
    entrada.close();
    saida.close();
return 0;
}