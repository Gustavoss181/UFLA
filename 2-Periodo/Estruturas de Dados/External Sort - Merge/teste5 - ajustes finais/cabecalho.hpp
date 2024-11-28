#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
using namespace std;
//nome do arquivo binario usado no programa
const string FILENAME = "data_athlete_event.bin";

namespace MeuCabecalho{
	struct AthleteEvent{
		//friend function 
		//Id,Name,City,Sport,Event,NOC
		int id;
		char name[100];
		char city[100];
		char sport[100];
		char event[100];
		char NOC[5];

		string formatar(const char vecChar[]){
			string str = vecChar;
			str.erase(remove(str.begin(), str.end(), '"'), str.end());
			while(str[0] == ' '){
				str = str.substr(1, str.size());
			}
			for(unsigned i=0; i<str.size(); i++)
				str[i] = tolower(str[i]);

			return str;
		}

		bool operator<(AthleteEvent &r2){
			if(formatar(name) == formatar(r2.name))
				return id < r2.id;
			else
				return formatar(name) < formatar(r2.name);
		}
		bool operator>(AthleteEvent &r2){
			if(formatar(name) == formatar(r2.name))
				return id > r2.id;
			else
				return formatar(name) > formatar(r2.name);
		}
		bool operator<=(AthleteEvent &r2){
			if(formatar(name) == formatar(r2.name))
				return id <= r2.id;
			else
				return formatar(name) < formatar(r2.name);
		}
		bool operator>=(AthleteEvent &r2){
			if(formatar(name) == formatar(r2.name))
				return id >= r2.id;
			else
				return formatar(name) > formatar(r2.name);
		}

		friend ostream & operator << (ostream &out, const AthleteEvent &r);
	};
	
	ostream & operator << (ostream &out, const AthleteEvent &r){
		out << "Id: " << r.id << endl
			<< "Nome: " << r.name << endl
			<< "Cidade: " << r.city << endl
			<< "Esporte: " << r.sport << endl
			<< "Evento: " << r.event << endl
			<< "NOC: " << r.NOC << endl
			<< "- - - - - - - - - - - - " << endl;
		
		return out;
	}
}