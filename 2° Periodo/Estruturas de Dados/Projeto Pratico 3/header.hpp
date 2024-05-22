#include <iostream>
#include <fstream>
using namespace std;

const string FILENAME = "data_athlete_event.bin";

struct AthleteEvent{
	//Id,Name,City,Sport,Event,NOC
	int id;
	char name[100];
	char city[100];
	char sport[100];
	char event[100];
	char NOC[5];

	void mostrarCampos(){
		cout << "Id: " << id << endl;
		cout << "Nome: " << name << endl;
		cout << "Cidade: " << city << endl;
		cout << "Esporte: " << sport << endl;
		cout << "Evento: " << event << endl;
		cout << "NOC: " << NOC << endl;
		cout << "- - - - - - - - - - - - " << endl;
	}
};
