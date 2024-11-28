#include <iostream>
#include <fstream>
#include <cstring>
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

		bool operator<(AthleteEvent &r2){
			int comp = strcasecmp(name, r2.name);
			if(comp == 0)
				return id < r2.id;
			else if(comp < 0)
				return true;
			else
				return false;
		}
		bool operator>(AthleteEvent &r2){
			int comp = strcasecmp(name, r2.name);
			if(comp == 0)
				return id > r2.id;
			else if(comp > 0)
				return true;
			else
				return false;
		}
		bool operator<=(AthleteEvent &r2){
			int comp = strcasecmp(name, r2.name);
			if(comp == 0)
				return id <= r2.id;
			else if(comp < 0)
				return true;
			else
				return false;
		}
		bool operator>=(AthleteEvent &r2){
			int comp = strcasecmp(name, r2.name);
			if(comp == 0)
				return id >= r2.id;
			else if(comp >= 0)
				return true;
			else
				return false;
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