#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Minhas Chaves
// #define PRIMO1 593
// #define PRIMO2 929
// #define CHAVE_PUBLICA 550897
// #define CHAVE_PRIVADA 366251

// Chaves Rafa
// #define PRIMO1 593
// #define PRIMO2 929
// #define CHAVE_PUBLICA 759541
// #define CHAVE_PRIVADA 505195

// Chaves Rafa
// #define PRIMO1 449
// #define PRIMO2 857
// #define CHAVE_PUBLICA 384793
// #define CHAVE_PRIVADA 255659


const string tabela = "0123456789 abcdefghijklmnopqrstuvwxyz'-,";

void encontrarPrimos(int chavePublica, int &p1, int &p2){
	vector<int> primos;
	for(int i=200; i<1000; i++){
		int cont = 0;
		for(int j=2; j<i/2+1; j++){
			if(i%j == 0){
				cont++;
				break;
			}
		}
		if(cont == 0)
			primos.push_back(i);
	}

	for(int i=0; i<primos.size()-1; i++){
		for(int j=i+1; j<primos.size(); j++){
			if(primos[i]*primos[j] == chavePublica){
				cout << primos[i] << " " << primos[j] << endl;
				p1 = primos[i];
				p2 = primos[j];
				break;
			}
		}
	}
}

int chavePrivada(int p1, int p2){
	int x=0;
	int fi = (p1-1)*(p2-1);

	while((3*x)%fi != 1 and x<fi)
		x++;
	
	cout << x << endl;
	return x;
}

string codificar(string msg){
	string msgCod = "";
	for(int i=0; i<msg.length(); i++){
		msgCod += to_string(tabela.find(msg[i])+10);
	}
	return msgCod;
}

string criptografarBloco(int chavePublica, long long bloco){
	long long crip = (bloco*bloco) % chavePublica;
	crip = (crip*bloco) % chavePublica;

	string strCrip = "";
	int i=100000; // numero de algarismos da chave publica
	while(crip<i){
		strCrip += "0";
		i /= 10;
	}
	strCrip += to_string(crip);

	return strCrip;
}

string criptografar(string msg, int chavePublica, int tamBloco){
	string msgCodigo = codificar(msg);

	string msgCriptografada = "";
	for(int i=0; i<msgCodigo.length()/tamBloco; i++){
		string bloco = msgCodigo.substr(i*tamBloco, tamBloco);
		msgCriptografada += criptografarBloco(chavePublica, stoi(bloco));
	}

	return msgCriptografada;
}

string decodificar(string msg){
	string msgDecodificada = "";
	for(int i=0; i<msg.length()/2; i++){
		int c = stoi(msg.substr(i*2, 2))-10;
		if(c >= 0 and c < tabela.length())
			msgDecodificada += tabela[c];
	}
	return msgDecodificada;
}

string descriptografarBloco(long long bloco, int chavePublica, int chavePrivada){
	long long descrip = bloco;
	for(int i=1; i<chavePrivada; i++){
		long long aux = descrip*bloco;
		descrip = aux % chavePublica;
	}

	string strCrip = "";
	int i=10000;
	while(descrip<i){
		strCrip += "0";
		i /= 10;
	}
	strCrip += to_string(descrip);

	return strCrip;
}

string descriptografar(string msg, int chavePublica, int chavePrivada){
	int n = 6; //numero de algarismos chave publica

	string msgDescrip = "";
	for(unsigned int i=0; i<msg.length()/n; i++){
		string bloco = msg.substr(i*n, n);
		msgDescrip += descriptografarBloco(stoi(bloco), chavePublica, chavePrivada);
	}

	return decodificar(msgDescrip);
}

int main(){
	int chavePublica;
	cin >> chavePublica;
	
	int p1, p2;
	encontrarPrimos(chavePublica, p1, p2);
	
	int chavePriv = chavePrivada(p1, p2);

	int tamBloco = 5;
	string msg;
	cin >> msg;

	string msgCrip = criptografar(msg, chavePublica, tamBloco);

	cout << msgCrip << endl;

	string msgDescrip = descriptografar(msgCrip, chavePublica, chavePriv);

	cout << msgDescrip << endl;

	return 0;
}