/*
Integrantes:
Bruno Crespo Ferreira - 202120489
Gustavo Soares Silva - 202120103
Vinícius de Oliveira Fabiano - 202120494
*/
#include <iostream>
using namespace std;

// O registro Jogo é a base para o nosso programa, criamos um vetor dele para armazenarmos quantos jogos quisermos (seguindo as regras de alocação) e outras funções; todo o trabalho envolve tal vetor e o registro
struct Jogo{
	// id é o identificador do jogo, tal número é crescente, 1 por 1
	int id = 1;
	// Demais campos que representam algumas características dos jogos
	string nome;
	int ano_lancamento;
	string plataforma;
	string descricao;
	// O bool valido é a flag, representa que um jogo não existe se for false e que existe se for true. No caso, embora pareça inicialmente que o jogo com id = 1 exista, isso não afeta o programa, tal jogo é sobrescrito
	bool valido = true;
};

// Função para listar o vetor de jogos
void listar(Jogo *jogos, int pos){
cout << "------ SEUS JOGOS ------" << endl;
// Um jogo do vetor só é válido se sua flag for true, logo não serão mostrados jogos excluídos pelo usuário (com flag = false)
	for(int i=0; i<pos; i++)
		if(jogos[i].valido){
			cout << "Id: " << jogos[i].id << endl;
			cout << "Nome: " << jogos[i].nome << endl;
			cout << "Ano de lancamento: " << jogos[i].ano_lancamento << endl;
			cout << "Plataforma: " << jogos[i].plataforma << endl;
			cout << "Descricao: " << jogos[i].descricao << endl;
			cout << "Posicao: " << i << endl;
			cout << endl;
		}
}

//essa função serve para retornar como o vetor será ordenado, dependendo do campo selecionado
bool ordenarPorCampo(Jogo jogo1, Jogo jogo2, string campo){
	// o trecho ...and jogo1.valido) serve para colocar os jogos excluidos ao final do vetor
	if(campo == "identificador")
		return ((jogo1.id < jogo2.id and jogo1.valido) or (!jogo2.valido));
	else if(campo == "nome")
		return ((jogo1.nome < jogo2.nome and jogo1.valido) or (!jogo2.valido));
	else if(campo == "ano de lancamento")
		return ((jogo1.ano_lancamento < jogo2.ano_lancamento and jogo1.valido) or (!jogo2.valido));
	else
		return ((jogo1.plataforma < jogo2.plataforma and jogo1.valido) or (!jogo2.valido));
}
//essa função faz parte da ordenação Quicksort para repartir o vetor
int particao(Jogo *jogos, int ini, int fim, string campo){
	int i = ini-1;

	for(int j=ini; j<fim; j++)
		if(ordenarPorCampo(jogos[j], jogos[fim], campo)){
			i++;
			swap(jogos[i], jogos[j]);
		}
	i++;
	swap(jogos[i], jogos[fim]);

	return i;
}
//essa é a função principal do método de ordenação quicksort que funciona recursivamente
void quicksort(Jogo *jogos, int ini, int fim, string campo){
	if(ini >= fim) return;

	int pivo = particao(jogos, ini, fim, campo);

	quicksort(jogos, ini, pivo-1, campo);
	quicksort(jogos, pivo+1, fim, campo);
}

// Esta função muda por qual campo que será ordenado o vetor jogos, de acordo com a opção escolhida pelo usuário
string alterarOrdenacao(Jogo *jogos, int pos, string atual){
	bool controle = true;
	cout << "Escolha um campo para ordenar a lista:" << endl;
	cout << "1 - Identificador" << endl;
	cout << "2 - Nome" << endl;
	cout << "3 - Ano de Lancamento" << endl;
	cout << "4 - Plataforma" << endl;
	do{
		int opcao;
		while(!(cin >> opcao)){
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Digite uma opcao valida: ";
		}
		switch(opcao){
			case 1:
				atual = "identificador";
				controle = false;
				break;
			case 2:
				atual = "nome";
				controle = false;
				break;
			case 3:
				atual = "ano de lancamento";
				controle = false;
				break;
			case 4:
				atual = "plataforma";
				controle = false;
				break;
			default:
				cout << "Opcao invalida. Escolha novamente" << endl;
				break;
		}
	}while(controle);

	quicksort(jogos, 0, pos-1, atual);

	return atual;
}
//essa função padroniza a busca de um id no vetor
int procuraId(Jogo *jogos, int pos){
	int idProcurado;
	cout << "Por favor insira o id do jogo: ";
	while(!(cin >> idProcurado)){
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Digite um inteiro: ";
	}
	for(int i=0; i<pos; i++)
		if(idProcurado == jogos[i].id and jogos[i].valido)
			return i;

	cout << "O id digitado nao esta presente nos jogos." << endl;
	return -1;
}

//Função que padroniza a leitura de uma string
string lerString(bool ignore){
	string str;
	if(ignore) cin.ignore(10000, '\n');
	getline(cin, str);
	while(str.empty()){
		getline(cin, str);
	}
	//Linha para colocar a primeira letra como maiuscula
	if(str[0] >= 97 and str[0] <= 122)
		str[0] -= 32;
	return str;
	}

// Função para alterar uma das caracteristicas de um jogo
bool alterar(Jogo *jogos, int pos, string atual){
	int id = procuraId(jogos, pos);
	if(id == -1) return false;

	bool controle = true;
	//esse loop permite que o usuário altere mais de um campo
	do{
		cout << "Voce escolheu o jogo " << jogos[id].nome << endl;
		cout << "Escolha um campo para alterar:" << endl;
		cout << "1 - Nome" << endl;
		cout << "2 - Ano de Lancamento" << endl;
		cout << "3 - Plataforma" << endl;
		cout << "4 - Descricao" << endl;
		int opcao;
		while(!(cin >> opcao) or !(opcao > 0 and opcao < 5)){
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Digite uma opcao valida: ";
		}
		switch(opcao){
			case 1:
				cout << "Insira o novo nome do jogo: ";
				jogos[id].nome = lerString(true);
				cout << "Alteracao feita! Nome atual: " << jogos[id].nome << endl;
				if(atual == "nome") quicksort(jogos, 0, pos-1, atual);
				controle = false;
				break;
			case 2:
				cout << "Insira o novo ano de lancamento do jogo: ";
				while(!(cin >> jogos[id].ano_lancamento)){
					cin.clear();
					cin.ignore(10000, '\n');
					cout << "Insira um ano valido: ";
				}
				cin.ignore(10000, '\n');
				cout << "Alteracao feita! Ano de lancamento atual: " << jogos[id].ano_lancamento << endl;
				if(atual == "ano de lancamento") quicksort(jogos, 0, pos-1, atual);
				controle = false;
				break;
			case 3:
				cout << "Insira a nova plataforma do jogo: ";
				jogos[id].plataforma = lerString(true);
				cout << "Alteracao feita! Plataforma atual: " << jogos[id].plataforma << endl;
				if(atual == "plataforma") quicksort(jogos, 0, pos-1, atual);
				controle = false;
				break;
			case 4:
				cout << "Insira a nova descricao sobre o jogo: ";
				jogos[id].descricao = lerString(true);
				cout << "Alteracao feita! Descricao atual: " << jogos[id].descricao << endl;
				controle = false;
				break;
			default:
				cout << "Opcao invalida. Escolha novamente: ";
				break;
		}
		if(opcao > 0 and opcao < 5){
			cout << "Gostaria de fazer mais alguma alteracao no jogo " << jogos[id].nome << "? (s/n)";
			string novaAlteracao;
			cin >> novaAlteracao;
			if(novaAlteracao == "s")
				controle = true;
		}
	}while(controle);

	return true;
}

// Função para excluir um jogo
bool excluir(Jogo *jogos, int pos, string atual){

	int id = procuraId(jogos, pos);

	if(id == -1) return false;

	string escolha;
	cout << "Voce tem certeza que quer deletar " << jogos[id].nome << "? (s / n) ";
	cin >> escolha;

	if(escolha == "s"){
		// Se o usuário realmente quer deletar o jogo, a flag dele será colocada como false
		jogos[id].valido = false;
		cout << "O jogo foi deletado" << endl;
		quicksort(jogos, 0, pos-1, atual);
		return true;
	}
	else{
		cout << "O jogo nao foi deletado" << endl;
		return false;
	}
}

// Função para aumentar o vetor jogos dinamicamente
Jogo* aumentaVetor(Jogo *jogos, int &tam){
	// tam2 representa o novo tamanho do vetor, no caso um aumento de 20%
	int tam2 = tam + (int)tam*0.2;

	// É criado um novo vetor dinamicamente com o novo tamanho (tam2)
	Jogo* novo = new Jogo[tam2];
	// Os jogos são transferidos para o novo vetor aumentado
	for(int i = 0;i < tam;i++)
		novo[i] = jogos[i];

	// tam recebe o valor do novo tamanho. Como está sendo passado por referência, essa alteração é válida para todo o código. Logo, é feita a desalocação do vetor de jogos antigo
	tam = tam2;	
	delete[] jogos;
	// Retorno do vetor jogos realocado
	return novo;
}

// Funcão para inserir um novo jogo ao vetor jogos
Jogo* inserir(Jogo *jogos, int &tam, int &pos, string campoAtual){
	//Essa condição serve para verificar se tem algum item que foi excluido e está localizado no final do vetor (pela ordenação). Se sim o proximo item é inserido nessa posição.
	if(pos != 0 and !jogos[pos-1].valido){
		pos--;
		jogos[pos].valido = true;
	}
	else{
		if(pos == tam)
			jogos = aumentaVetor(jogos, tam);
		jogos[pos].id += pos;
	}
	// A partir daqui são inseridos todos os dados requeridos do novo jogo (representado pela posição), cada campo é preenchido por vez
	cout << "Insira o nome do jogo: ";
	jogos[pos].nome = lerString(true);

	cout << "Insira o ano de lancamento do jogo: ";
	while(!(cin >> jogos[pos].ano_lancamento)){
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Insira um ano valido: ";
	}

	cout << "Insira a plataforma do jogo: ";
	jogos[pos].plataforma = lerString(true);

	cout << "Insira a descricao sobre o jogo: ";
	jogos[pos].descricao = lerString(false);

	// É feito a adição em 1 unidade para a pos (para outro jogo ser inserido futuramente)
	pos++;

	// O vetor jogos é ordenado após a inserção do novo jogo à ele, tal ordenação depende do campo atual selecionado, do próprio vetor e a posição inicial e final dele
	quicksort(jogos, 0, pos-1, campoAtual);

	// Retorna o novo vetor jogos com o novo jogo inserido e ordenado corretamente
	return jogos;
}

int main() {
	// tam é o tamanho atual do vetor jogos do registro Jogo
	// pos é a posição do jogo que o usuário irá inserir, a cada jogo inserido seu valor é somado em 1
	//nJogos é o numero de jogos que o usuário tem atualmente
	int tam = 5, pos = 0, nJogos=0;
	// campoOrdenacaoAtua é a ordenação atual do vetor jogos, o usuário pode alterá-la
	string campoOrdenacaoAtual = "identificador";
	// jogos é um vetor do registro Jogo, alocado dinamicamente
	Jogo *jogos = new Jogo[tam];
	// controle serve para encerrar o programa caso o usuário desejar
	bool controle = true;
	// Menu para o usuário, dependendo da opção dele realiza-se uma função específica
	do{
		system("clear");//essa linha funciona apenas em um sistema operacional linux para "limpar" o terminal
		cout << "Tamanho do vetor atual: " << tam << endl;
		cout << "Escolha uma opcao:" << endl;
		cout << "1 - Adicionar um jogo" << endl;
		cout << "2 - Excluir um jogo" << endl;
		cout << "3 - Listar todos os jogos. Numero de jogos atualmente: "<< nJogos << endl;
		cout << "4 - Alterar um dos dados de algum jogo" << endl;
		cout << "5 - Alterar a ordem da lista. Campo de ordenacao atual: " << campoOrdenacaoAtual << endl;
		cout << "6 - Sair do programa" << endl;
		int opcao = -1;
		bool aux = true, excluido;
		while(!(cin >> opcao) or !(opcao > 0 and opcao <= 6)){
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Digite uma opcao valida: ";
		}
		switch(opcao){
			case 1://incluir
				jogos = inserir(jogos, tam, pos, campoOrdenacaoAtual);
				aux = false;
				nJogos++;
				break;
			case 2://excluir
				excluido = excluir(jogos, pos, campoOrdenacaoAtual);
				if(excluido) nJogos--;
				break;
			case 3://listar
				// Piadinhas mostradas ao usuário e a quantidade de jogos atuais dele
				if(nJogos == 0)
					cout<< "Nenhum jogo no estoque. Compre algum jogo imediatamente!!!" << endl << endl;
				else{
					listar(jogos, pos);
					if(nJogos == 1)
						cout << "Voce consegue se divertir com apenas um jogo?" << endl << endl;
					else
						cout << "Que legal! Voce tem " << nJogos << " jogos!" << endl << endl;
				}
				break;
			case 4://alterar
				if(nJogos == 0)
					cout<< "Nenhum jogo no estoque. Compre algum jogo imediatamente!!!" << endl << endl;
				else
					if(alterar(jogos, pos, campoOrdenacaoAtual)) aux = false;
				break;
			case 5://ordenar / alterar ordenacao
				campoOrdenacaoAtual = alterarOrdenacao(jogos, pos, campoOrdenacaoAtual);
				if(nJogos > 0) listar(jogos, pos);
				break;
			case 6:
				cout << "Obrigado por utilizar nosso programa!" << endl;
				controle = false;
				break;
			default:
				cout << "Selecione uma opcao valida!" << endl;
				break;
		}
		//esse trecho de código serve para o código ter uma pausa na execução para o usuário poder ler os dados mostrados
		cout << "Pressione enter para continuar...";
		if(aux) cin.ignore();
		cin.get();

	}while(controle);

	// Aqui o vetor jogos é desalocado da memória
	delete[] jogos;

	return 0;
}