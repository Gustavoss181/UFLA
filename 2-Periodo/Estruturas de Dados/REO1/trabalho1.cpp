#include <iostream>

using namespace std;

//struct para armazenar pokemon
struct Pokemon{
	string nome;
	string tipo;
	int posPokedex;
	int vel;
	int atk;
	int def;
	int atkEsp;
	int defEsp;
};

//struct para armazenar ginasio/treinador
struct Ginasio{
	string nomeGinasio;
	string nomeTreinador;
	string tipoUsado;
	string fraqueza;
};

//classe Jogador para controlar o acesso dos pokemons e ginasios existentes
class Jogador{
	private:
		Ginasio *ginasios;//vetor de ginasios
		Pokemon *pokedex;//vetor de pokemons
		int qtdPok;
		int qtdGin;
	public:
		Jogador(int nPok, int nGin);//construtor
		~Jogador();//destrutor
		void batalhar(string nomeGin);
		void listarTipo(string tipo);
		void cadastrarGinasio();
		void cadastrarPokemon();
};

//construtor que aloca os vetores e inicializa as quantidades de ambos em 0
Jogador::Jogador(int nPok, int nGin){
	pokedex = new Pokemon[nPok];
	ginasios = new Ginasio[nGin];
	qtdPok = 0;
	qtdGin = 0;
}

//desaloca os vetores
Jogador::~Jogador(){
	delete ginasios;
	delete pokedex;
}

//cadastra um novo pokemon
void Jogador::cadastrarPokemon(){
	cout << "cadastrar pokemon" << endl;
	cin >> pokedex[qtdPok].nome;
	cin >> pokedex[qtdPok].tipo;
	cin >> pokedex[qtdPok].posPokedex;
	cin >> pokedex[qtdPok].vel;
	cin >> pokedex[qtdPok].atk;
	cin >> pokedex[qtdPok].def;
	cin >> pokedex[qtdPok].atkEsp;
	cin >> pokedex[qtdPok].defEsp;
	qtdPok++;
}

//cadastra um novo ginasio/treinador
void Jogador::cadastrarGinasio(){
	cout << "cadastrar ginasio" << endl;
	cin >> ginasios[qtdGin].nomeGinasio;
	cin >> ginasios[qtdGin].nomeTreinador;
	cin >> ginasios[qtdGin].tipoUsado;
	cin >> ginasios[qtdGin].fraqueza;
	qtdGin++;
}

//lista todos os pokemons presentes na pokedex que tem o tipo especificado
void Jogador::listarTipo(string tipo){
	bool aux = true;
	for(int i=0; i<qtdPok; i++){
		if(pokedex[i].tipo == tipo){
			aux = false;
			cout << pokedex[i].nome << endl;
		}
	}
	if(aux)
		cout << "sem pokemons desse tipo na sua pokedex" << endl;
}

//lista os pokemons presentes na pokedex que tem o tipo igual a fraqueza do oponente especificado
void Jogador::batalhar(string nomeTreinador){
	bool treinadorNaoEncontrado = true;
	string fraqueza;
	int i=0;
	while(i<qtdGin and treinadorNaoEncontrado){
		if(ginasios[i].nomeTreinador == nomeTreinador){
			treinadorNaoEncontrado = false;
			fraqueza = ginasios[i].fraqueza;
		}
	}
	if(treinadorNaoEncontrado)
		cout << "Treinador nao encontrado" << endl;
	else{
		bool aux = true;
		for(i=0; i<qtdPok; i++){
			if(pokedex[i].tipo == fraqueza){
				aux = false;
				cout << pokedex[i].nome << endl;
			}
		}
		if(aux)
			cout << "sem pokemons fortes para lutar" << endl;
	}
}

int main(){
	int nPok, nGin;
	cout << "escreva a qtd de pokemons e ginasios para cadastrar" << endl;
	cin >> nPok >> nGin;
	Jogador *antoniel = new Jogador(nPok, nGin);
	
	for(int i=0; i<nPok; i++)
		antoniel->cadastrarPokemon();
	for(int i=0; i<nGin; i++)
		antoniel->cadastrarGinasio();
	
	string tipo;
	cout << "Escreva o tipo do pokemon pra ser listado: ";
	cin >> tipo;
	antoniel->listarTipo(tipo);
	
	string nomeGinasio;
	cout << "Escreva o nome do treinador com que voce ira batalhar: ";
	cin >> nomeGinasio;
	antoniel->batalhar(nomeGinasio);
	
	delete antoniel;

	return 0;
}