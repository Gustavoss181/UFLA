#include<iostream>
#include <string>
using namespace std;

// Minhas Chaves
// #define CHAVE_PUBLICA 6319
// #define CHAVE_PRIVADA 4107

// Chaves Davi
// #define CHAVE_PUBLICA 2911
// #define CHAVE_PRIVADA 1867

// Chaves Bryan
#define CHAVE_PUBLICA 4183
#define CHAVE_PRIVADA 2699


const string tabela = "0123456789 abcdefghijklmnopqrstuvwxyz'-,";

void chavePrivada(){
	int x=0;

	while((3*x)%4048 != 1 and x<4048)
		x++;
	
	cout << x << endl;
}

string codificar(string msg){
	string msgCod = "";
	for(int i=0; i<msg.length(); i++){
		msgCod += to_string(tabela.find(msg[i])+10);
	}
	return msgCod;
}

string criptografarBloco(int bloco){
	int crip = (bloco*bloco) % CHAVE_PUBLICA;
	crip = (crip*bloco) % CHAVE_PUBLICA;

	string strCrip = "";
	int i=1000;
	while(crip<i){
		strCrip += "0";
		i /= 10;
	}
	strCrip += to_string(crip);

	return strCrip;
}

string criptografar(string msg, int tamBloco){
	string msgCodigo = codificar(msg);

	string msgCriptografada = "";
	for(int i=0; i<msgCodigo.length()/tamBloco; i++){
		string bloco = msgCodigo.substr(i*tamBloco, tamBloco);
		msgCriptografada += criptografarBloco(stoi(bloco));
	}
	return msgCriptografada;
}

string decodificar(string msg){
	string msgDecodificada = "";
	for(int i=0; i<msg.length()/2; i++){
		int c = stoi(msg.substr(i*2, 2))-10;
		msgDecodificada += tabela[c];
	}
	return msgDecodificada;
}

string descriptografarBloco(int bloco){
	int descrip = bloco;
	for(int i=1; i<CHAVE_PRIVADA; i++){
		descrip = (descrip*bloco)%CHAVE_PUBLICA;
	}

	string strCrip = "";
	int i=100;
	while(descrip<i){
		strCrip += "0";
		i /= 10;
	}
	strCrip += to_string(descrip);

	return strCrip;
}

string descriptografar(string msg){
	int n = 4; //numero de algarismos chave publica

	string msgDescrip = "";
	for(int i=0; i<msg.length()/n; i++){
		string bloco = msg.substr(i*n, n);
		msgDescrip += descriptografarBloco(stoi(bloco));
	}

	return decodificar(msgDescrip);
}

int main(){
	// chavePrivada();

	int tamBloco = 3;
	string msg;
	getline(cin, msg);

	string msgCrip = criptografar(msg, tamBloco);

	cout << msgCrip << endl;

	string msgDescrip = descriptografar(msgCrip);

	cout << msgDescrip << endl;

	// cout << descriptografar("08671612172515334055118012170331") << endl;

	return 0;
}