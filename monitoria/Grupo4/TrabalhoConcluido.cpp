#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

using namespace std;

struct registro{
    long long int campo1;
    char campo2[10];
    char campo3[200];
    float campo4;
    float campo5;
};

void imprime_arquivo(fstream& arquivo) {
    registro campo;
    while (arquivo.read((char *) (&campo),sizeof(registro))){
        if(campo.campo1 > 0){
            cout << campo.campo1 << ";";
            cout << campo.campo2 << ";";
            cout << campo.campo3 << ";";
            cout << campo.campo4 << ";";
            cout << campo.campo5 << endl;
        }
    }
    arquivo.close();
}

void swap(registro &a, registro &b){
    registro aux = a;
    a = b;
    b = aux;
}

int particionamentoCampo1(registro vetor[], int c, int f){
	registro pivo = vetor[c];
	int i = c+1;
	int j = f;
	while(i <= j){
		if(vetor[i].campo1 <= pivo.campo1){
			i++;
		}else if(pivo.campo1 <= vetor[j].campo1){
			j--;
		}else{
			swap(vetor[i], vetor[j]);
			i++;
			j--;
		}
	}
	vetor[c] = vetor[j];
	vetor[j] = pivo;
	return j;
}

void quickSortCampo1(registro vetor[], int comeco, int fim){
    if (comeco < fim){
        int IndicePivo = particionamentoCampo1(vetor, comeco, fim);
        quickSortCampo1(vetor, comeco, IndicePivo - 1);
        quickSortCampo1(vetor, IndicePivo + 1, fim);
    }
}

void ordenaCampo1(fstream& arquivo, int& elementos_excluidos){
    registro campos;
    arquivo.seekg(0, ios::end);
    int tamanho_vetor = arquivo.tellg();
    int num_regs = tamanho_vetor / sizeof(registro);
    arquivo.clear();
    arquivo.seekg(0, ios::beg);
    registro vetor[num_regs];
    int pos = 0;
    for(int i = 0; i < num_regs; i++){
        arquivo.seekg(i*sizeof(registro));
        arquivo.read((char *) (&campos),sizeof(registro));
        if (campos.campo1 > 0){
            vetor[pos] = campos;
            pos++;
        } else {
            num_regs--;
        }
    }
    quickSortCampo1(vetor, 0, num_regs - 1);
    elementos_excluidos = 0;
    arquivo.close();
    arquivo.open("base9_binario.dat", ios::binary | ios::in | ios::out | ios::trunc);
    for(int i = 0; i < pos; i++){
        arquivo.write((const char *) (&vetor[i]), sizeof(registro));
    }
    cout << "Arquivo ordenado com sucesso!!" << endl;
}

int particionamentoCampo4(registro vetor[], int c, int f){
	registro pivo = vetor[c];
	int i = c+1;
	int j = f;
	while(i <= j){
		if(vetor[i].campo4 <= pivo.campo4){
			i++;
		}else if(pivo.campo4 <= vetor[j].campo4){
			j--;
		}else{
			swap(vetor[i], vetor[j]);
			i++;
			j--;
		}
	}
	vetor[c] = vetor[j];
	vetor[j] = pivo;
	return j;
}

void quickSortCampo4(registro vetor[], int comeco, int fim){
    if (comeco < fim){
        int IndicePivo = particionamentoCampo4(vetor, comeco, fim);
        quickSortCampo4(vetor, comeco, IndicePivo - 1);
        quickSortCampo4(vetor, IndicePivo + 1, fim);
    }
}

void ordenaCampo4(fstream& arquivo, int& elementos_excluidos){
     registro campos;
    arquivo.seekg(0, ios::end);
    int tamanho_vetor = arquivo.tellg();
    int num_regs = tamanho_vetor / sizeof(registro);
    arquivo.clear();
    arquivo.seekg(0, ios::beg);
    registro vetor[num_regs];
    int pos = 0;
    for(int i = 0; i < num_regs; i++){
        arquivo.seekg(i*sizeof(registro));
        arquivo.read((char *) (&campos),sizeof(registro));
        if (campos.campo1 > 0){
            vetor[pos] = campos;
            pos++;
        } else {
            num_regs--;
        }
    }
    quickSortCampo4(vetor, 0, num_regs - 1);
    elementos_excluidos = 0;
    arquivo.close();
    arquivo.open("base9_binario.dat", ios::binary | ios::in | ios::out | ios::trunc);
    for(int i = 0; i < pos; i++){
        arquivo.write((const char *) (&vetor[i]), sizeof(registro));
    }
    cout << "Arquivo ordenado com sucesso!!" << endl;
}

void excluir(fstream& arquivo, int num_regs, int posicao, int &elementos_excluidos) {
    registro campos;
    if ((posicao >= 0) and (posicao < num_regs)) {
        arquivo.seekg(posicao * sizeof(campos));
        arquivo.read(reinterpret_cast<char*>(&campos), sizeof(registro));
        campos.campo1 = -campos.campo1;
        arquivo.seekg(posicao * sizeof(registro));
        arquivo.write(reinterpret_cast<const char*>(&campos), sizeof(registro));
    }
    arquivo.seekg(0, ios::beg);
    cout << "Elemento exclído com sucesso!!" << endl;
    elementos_excluidos++;
}

void inserir_elemento(fstream& arquivo, int& elementos_excluidos){
    registro campos;
    int posicao = 0;
    bool insere_apenas_um = false;
    if(elementos_excluidos > 0){
        while (((arquivo.read(reinterpret_cast<char*>(&campos), sizeof(registro)))) and (!insere_apenas_um)){
            if(campos.campo1 < 0){
                posicao = arquivo.tellp();
                posicao = posicao - sizeof(registro);
                cout << "Digite os valores a serem inseridos :" << endl;
                cout << "Digite o campo 1:" << endl;
                cin.ignore(1000, '\n');
                cin >> campos.campo1;

                cout << "Digite o campo 2:" << endl;
                string aux;
                getline(cin, aux);
                strcpy(campos.campo2, aux.c_str());

                cout << "Digite o campo 3:" << endl;
                getline(cin, aux);
                strcpy(campos.campo3, aux.c_str());

                cout << "Digite o campo 4:" << endl;
                cin >> campos.campo4;

                cout << "Digite o campo 5:" << endl;
                cin >> campos.campo5;
                arquivo.seekp(posicao);
                arquivo.write(reinterpret_cast<char*>(&campos), sizeof(registro));
                insere_apenas_um = true;
            }
        }
        insere_apenas_um = false;
        elementos_excluidos--;
    }else{
        arquivo.seekp(0, ios::end);
        cout << "Digite os valores a serem inseridos :" << endl;
        cout << "Digite o campo 1:" << endl;
        cin >> campos.campo1;

        cout << "Digite o campo 2:" << endl;
        string aux;
        cin.ignore(1000, '\n');
        getline(cin, aux);
        strcpy(campos.campo2, aux.c_str());

        cout << "Digite o campo 3:" << endl;
        getline(cin, aux);
        strcpy(campos.campo3, aux.c_str());

        cout << "Digite o campo 4:" << endl;
        cin >> campos.campo4;

        cout << "Digite o campo 5:" << endl;
        cin >> campos.campo5;
        arquivo.write(reinterpret_cast<char*>(&campos), sizeof(registro));
    }
    arquivo.close();
}

void buscarElementoCampo1(fstream& arquivo, long long int elemento_buscar, int tamanho_arquivo_por_registro){
    int cont =0;
    registro campos;
    int posicao=-1;
    while ((cont < tamanho_arquivo_por_registro) and (posicao ==-1)){
        arquivo.seekp(cont*sizeof(registro));
        arquivo.read((char*) &campos, sizeof(registro));
        if (campos.campo1 == elemento_buscar) {
            posicao = cont;
        }
        cont++;
    }
    if (posicao !=-1){
        cout << "Elemento encontrado na posição " << posicao << " do arquivo!"<< endl;
        cout << campos.campo1 << ";";
        cout << campos.campo2 << ";";
        cout << campos.campo3 << ";";
        cout << campos.campo4 << ";";
        cout << campos.campo5 << endl;
    } else {
    cout << "Elemento não encontrado." << endl;
    }
    arquivo.close();
}

void imprimeTrecho(fstream& arquivo, int posicao_inicial, int posicao_final){
    int tamanho_registro = sizeof(registro);
    int posicao_atual = posicao_inicial * tamanho_registro;
    int registros_lidos = posicao_final - posicao_inicial;
    bool para = false;
    arquivo.seekg(posicao_atual, ios::beg);
    int i = 0;
    while((i < registros_lidos) and (!para)){
        registro campos;
        arquivo.read(reinterpret_cast<char*>(&campos), sizeof(registro));
        cout << campos.campo1 << ";";
        cout << campos.campo2 << ";";
        cout << campos.campo3 << ";";
        cout << campos.campo4 << ";";
        cout << campos.campo5 << endl;
        posicao_atual += tamanho_registro;
        if(posicao_inicial > posicao_final){
            para = true;
        }
        i++;
        posicao_inicial++;
        arquivo.seekg(posicao_atual, ios::beg);
    }
}

void importaParaArquivoCSV(fstream& arquivo){
    ofstream saida("ArquivoImportadoDeBinarioParaCSV.csv");
    registro campo;
    while (arquivo.read((char *) (&campo),sizeof(registro))){
        if(campo.campo1 > 0){
            saida << campo.campo1 << ";";
            saida << campo.campo2 << ";";
            saida << campo.campo3 << ";";
            saida << campo.campo4 << ";";
            saida << campo.campo5 << endl;
        }
    }
    saida.close();
    cout << "Arquivo criado com sucesso!!" << endl;

}

int main (){
    int opcao, elementos_excluidos = 0;
    bool fecha = false;
    fstream arquivo;

    while((opcao != 0) and !fecha){
        cout << "|--------------------------------MENU-------------------------------|" << endl;
        cout << "|                                                                   |" << endl;
        cout << "|              Digite [1] para imprimir                             |" << endl;
        cout << "|              Digite [2] para ordenar                              |" << endl;
        cout << "|              Digite [3] para remover um elemento                  |" << endl;
        cout << "|              Digite [4] para inserir um novo elemento             |" << endl;
        cout << "|              Digite [5] para buscar um elemento                   |" << endl;
        cout << "|              Digite [6] para imprimir um trecho                   |" << endl;
        cout << "|              Digite [7] para exportar os dados para CSV           |" << endl;
        cout << "|              Digite [0] para fechar o programa                    |" << endl; 
        cout << "|-------------------------------------------------------------------|" << endl;
        cin >> opcao;
        if(opcao == 0){
            cout << "Encerrando o programa !!";
            fecha = true;
        }else if(opcao == 1){
            arquivo.open("base9_binario.dat", ios::binary | ios::in | ios::out);
            imprime_arquivo(arquivo);
            arquivo.close();
        }else if(opcao == 2){
            cout << "Digite qual dos campos você deseja ordenar, digite [1] para o campo 1, [4] para o campo 4" << endl;
            int escolha;
            cin >> escolha;
            if(escolha == 1){
                arquivo.open("base9_binario.dat", ios::binary | ios::in | ios::out | ios::ate);
                ordenaCampo1(arquivo, elementos_excluidos);
                arquivo.close();
            }else if(escolha == 4){
                arquivo.open("base9_binario.dat", ios::binary | ios::in | ios::out | ios::ate);
                ordenaCampo4(arquivo, elementos_excluidos);
                arquivo.close();
            }
        }else if(opcao == 3){
            arquivo.open("base9_binario.dat", ios::binary | ios::in | ios::out | ios::ate);
            arquivo.seekg(0, ios::end);
            int tamanho_arquivo = arquivo.tellg();
            int num_regs = tamanho_arquivo / sizeof(registro);
            int posicao;
            cout << "Lembrando que a posição mínima para remover é '0' e a posição máxima é '" << num_regs-1 << "' !!"<< endl;
            cout << "Digite a posição do elemento no arquivo que deseja excluir: ";
            cin >> posicao;
            excluir(arquivo, num_regs, posicao, elementos_excluidos);
            arquivo.close();
        }else if (opcao == 4){
            arquivo.open("base9_binario.dat", ios::binary | ios::in | ios::out);
            inserir_elemento(arquivo, elementos_excluidos);
            arquivo.close();
        }else if (opcao == 5){
            arquivo.open("base9_binario.dat", ios::binary | ios::in | ios::out | ios::ate);
            cout << "Digite o ID (Campo 1) do elemento que deseja realizar a busca: " << endl;

            long long int elemento_buscar;
            arquivo.seekg(0, ios::end);
            int tamanho_arquivo = arquivo.tellg();
            int tamanho_arquivo_por_registro =  tamanho_arquivo / sizeof(registro);
            arquivo.seekg(0, ios::beg);

            cout << endl;
            cin >> elemento_buscar;
            cout << endl;
            buscarElementoCampo1(arquivo, elemento_buscar, tamanho_arquivo_por_registro);
            arquivo.close();
        }else if (opcao == 6){
            arquivo.open("base9_binario.dat", ios::binary | ios::in | ios::ate);
            arquivo.seekg(0, ios::end);
            int tamanho = arquivo.tellg();
            arquivo.seekg(0, ios::beg);

            cout << "Digite o trecho que deseja imprimir " << endl;
            cout << "Digite a posição inicial " << endl;
            int posicao_incial;
            cin >> posicao_incial;
            if((posicao_incial < 0) and (posicao_incial > tamanho)){
                cout << "Posição inválida!" << endl;
            }
            cout << "Digite a posição final. OBS. não pode ser maior que o tamanho do arquivo!" << endl;
            int posicao_final;
            cin >> posicao_final;
            if((posicao_final < 0) and (posicao_incial > tamanho)){
                cout << "Posição inválida!" << endl;
            }
            imprimeTrecho(arquivo, posicao_incial, posicao_final);
            arquivo.close();
        }else if (opcao == 7){
            arquivo.open("base9_binario.dat", ios::binary | ios::in);
            importaParaArquivoCSV(arquivo);
            arquivo.close();
        }
    }
    return 0;
}