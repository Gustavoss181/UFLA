#include <iostream>

using namespace std;

struct Jogo{
	
	int id = 1;
	string nome;
	int ano_lancamento;
	string plataforma;
	string descricao;
	bool valido = true;
};

//funcao ordenar com QuickSort
// void swap(Jogo *a, Jogo *b){
	
// 	Jogo aux = *a;
// 	*a = *b;
// 	*b = aux;
// }

// int particao(Jogo v[], int menor, int maior, int escolha_user){
	
// 	Jogo pivo = v[maior];
	
// 	int i = (menor - 1);
	
// 	for(int j = menor; j <= maior; j++)
// 	{
// 		if(escolha_user == 1)
// 		{
// 			if(v[j].nome < pivo.nome){
// 				i++;
// 				swap(&v[i], &v[j]);
// 			}
// 		}
		
// 		else if(escolha_user == 2)
// 		{
// 			if(v[j].ano_lancamento < pivo.ano_lancamento){
// 				i++;
// 				swap(&v[i], &v[j]);
// 			}
// 		}
		
// 		else if(escolha_user == 3)
// 		{
// 			if(v[j].plataforma < pivo.plataforma){
// 				i++;
// 				swap(&v[i], &v[j]);
// 			}
// 		}
		
// 		else if(escolha_user == 4)
// 		{
// 			if(v[j].descricao < pivo.descricao)	{
// 				i++;
// 				swap(&v[i], &v[j]);
// 			}
// 		}
		
// 		else if(escolha_user == 5)
// 		{
// 			if(v[j].id < pivo.id){
// 				i++;
// 				swap(&v[i], &v[j]);
// 			}
// 		}
// 	}
	
// 	swap(&v[i + 1], &v[maior]);
	
// 	return (i + 1);
// }

// void quickSort(Jogo v[], int menor, int maior, int escolha_user){
	
// 	if(menor < maior){
// 		int pi = particao(v, menor, maior, escolha_user);
		
// 		quickSort(v, menor, pi - 1, escolha_user);
// 		quickSort(v, pi + 1, maior, escolha_user);
// 	}
// }

//funcao excluir
// bool excluir_jogo(Jogo *jogos, int pos){
	
// 	string opcao_delete;
// 	string escolha = " ";
// 	bool encontrado = false, certeza = false;
	
// 	cout << "Por favor insira o id do jogo que deseja deletar: ";
// 	cin >> opcao_delete;
	
// 	for(int i=0; i<pos and !encontrado; i++)
// 		if(opcao_delete == jogos[i].id and jogos[i].valido){
			
// 			encontrado = true;
			
// 			while((!certeza) and (escolha[0] != 'n')){
// 				cout << "Voce tem certeza que quer deletar " << jogos[i].nome << "? (s / n) ";
				
// 				cin >> escolha;
				
// 				if(escolha.size() > 1)
// 					escolha = " ";
				
// 				if(escolha[0] == 's'){
// 					jogos[i].valido = false;
// 					certeza = true;
// 				}
// 			}
// 		}
	
// 	if(!certeza and encontrado)
// 		cout << "O jogo nao foi deletado" << endl << endl;
		
// 	else if(certeza)
// 		cout << "O jogo foi deletado." << endl << endl;
		
// 	else
// 		cout << "O id digitado nao esta presente nos jogos." << endl << endl;
		
// 	return certeza;

// }

//funcao listar
// int listar(Jogo *jogos, int pos){
	
// 	int contador_jogos = 0;
	
// 	for(int i=0; i<pos; i++)
// 		if(jogos[i].valido){
// 			cout << "Id: " << jogos[i].id << endl;
// 			cout << "Nome: " << jogos[i].nome << endl;
// 			cout << "Ano de lancamento: " << jogos[i].ano_lancamento << endl;
// 			cout << "Plataformas: " << jogos[i].plataforma << endl;
// 			cout << "Descricao: " << jogos[i].descricao << endl;
// 			cout << "Posicao: " << i << endl;
// 			cout << endl;
// 			contador_jogos++;
// 		}
		
// 	if(contador_jogos > 0){
// 		if(contador_jogos == 1)
// 			cout << "Voce consegue se divertir com apenas um jogo?" << endl << endl;
			
// 		else
// 			cout << "Que legal! Voce tem " << contador_jogos << " jogos!" << endl << endl;
// 	}
	
// 	else
// 		cout<< "Nenhum jogo no estoque. Compre algum jogo imediatamente!!!" << endl << endl;
		
// 	return contador_jogos;
// }

//aumentar o vetor dinamicamente
// Jogo* aumentaVetor(Jogo *jogos, int &tam){
	
// 	int tam2 = tam + (int)tam*0.2;
	
// 	Jogo* novo = new Jogo[tam2];
	
// 	for(int i = 0;i < tam;i++)
// 		novo[i] = jogos[i];
	
// 	tam = tam2;	
	
// 	delete[] jogos;
	
// 	return novo;
// }

//funcao inserir
// Jogo* inserir(Jogo *jogos, int &tam, int &pos){
	
// 	if(pos == tam)
// 		jogos = aumentaVetor(jogos, tam);
		
// 	jogos[pos].id += pos;
	
// 	cout << "Insira o nome do jogo: ";
// 	cin.ignore();
// 	getline(cin, jogos[pos].nome);
	
// 	cout << "Insira o ano de lancamento do jogo: ";
// 	cin >> jogos[pos].ano_lancamento;
	
// 	cout << "Insira as plataformas do jogo: ";
// 	cin.ignore();
// 	getline(cin, jogos[pos].plataforma);
	
// 	cout << "Insira a descricao sobre o jogo: ";
// 	getline(cin, jogos[pos].descricao);
	
// 	pos++;
	
// 	cout << endl;
	
// 	return jogos;
// }

//funcao main
int main(){
	
	int tam = 5, pos = 0, contador_jogos = 0;
	
	Jogo *jogos = new Jogo[tam];
	
	bool controle = true, controle_inserir = false, escolha_exclusao = false;
	
	do{
		system("cls");
		cout << "Escolha uma opcao:" << endl;
		cout << "1 - Adicionar um jogo. Tamanho atual:" << tam << endl;
		cout << "2 - Excluir um jogo" << endl;
		cout << "3 - Ordenar a lista" << endl;
		cout << "4 - Listar todos os jogos. Voce possui: ";
			if(contador_jogos == 1) 
				cout << contador_jogos << " jogo" << endl;
			else  
				cout << contador_jogos << " jogos" << endl;
		cout << "5 - Sair do programa" << endl;
		
		string escolha = " ";
		cin >> escolha;
		
		if(escolha.size() == 1){
			
			int escolha_int;
			
			escolha_int = escolha[0] - 48;
			
			switch(escolha_int){
				case 1:
					jogos = inserir(jogos, tam, pos);
				
					contador_jogos++;
				
					controle_inserir = true;
					break;
				
				case 2:
					escolha_exclusao = excluir_jogo(jogos, pos);
				
					if(escolha_exclusao)
						contador_jogos--;
					break;
				
				case 3:
					if(contador_jogos == 0)
						cout << "Voce nao tem jogos! Oh, que mundo cruel :(" << endl << endl;
					
					else if(contador_jogos == 1)
						cout << "Por que ordenar apenas 1 jogo?" << endl << endl;
					
					else{
						
						do{
							system("cls");
							cout << "Voce deseja ordenar por:" << endl;
							cout << "1 - nome" << endl;
							cout << "2 - ano_lancamento" << endl;
							cout << "3 - plataforma" << endl;
							cout << "4 - descricao" << endl;
							cout << "5 - id" << endl;
							cout << "6 - cancelar" << endl;
							
							cin >> escolha;
							
							if(escolha.size() == 1){
								
								escolha_int = escolha[0] - 48;
								
								if((escolha_int >= 0) and (escolha_int <= 5)){
									quickSort(jogos, 0, pos - 1, escolha_int);
									cout << "Jogos ordenados!" << endl << endl;
								}
								
								else if(escolha_int == 6){
									
									escolha = " ";
									cout << "Os jogos nao foram ordenados!" << endl << endl;
								}
								
								else
									escolha = "denovo";
							}
							
							else
								escolha = "denovo";
						}while(escolha == "denovo");
					}
					break;
				
				case 4:
					contador_jogos = listar(jogos, pos);
					break;
				
				case 5:
					while((escolha[0] != 'n') and (escolha[0] != 's')){
						cout << "Voce realmente deseja sair? (s / n)" << endl;
						cin >> escolha;
						
						if(escolha.size() > 1)
							escolha = " ";
					}
				
					if(escolha[0] == 's')
						controle = false;
					
					else
						escolha = " ";
				
					break;
				
				default:
					cout << "Digite um inteiro do menu" << endl << endl;
					break;
			}
		
			if((controle) and (!controle_inserir)){
				cout << "Pressione enter para continuar...";
				cin.ignore();
				cin.get();
			}
		
			else if(controle_inserir){
				cout << "Pressione enter para continuar...";
				cin.get();
			
				controle_inserir = false;
			}
		}
		
		else{
			
			escolha = " ";
			cout << "Digite um inteiro do menu" << endl << endl;
			
			cout << "Pressione enter para continuar...";
			cin.ignore();
			cin.get();
		}
	}while(controle);
	
	delete[] jogos;
	
	return 0;
}
/*
Funções para desenvolver:
 - Inserção -> após o quinto item expandir o vetor a cada adição
 - Exclusão -> criar uma flag para indicar que foi excluído
 - Ordenação -> Decidir entre Merge e Quick e qual campo será ordenado (perguntar pro usuário?)
 - Criar o Registro
 - Listar -> Mostrar os dados em que a flag é True
 - Menu de opções para o usuário
 - O código deve ser comentado
*/
