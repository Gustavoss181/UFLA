#include <iostream>
using namespace std;
namespace MeuCabecalho{
	struct AthleteEvent{
		//Id,Name,City,Sport,Event,NOC
		int id;
		char name[100];
		char city[100];
		char sport[100];
		char event[100];
		char NOC[5];

		void mostrarCampos(){
			cout << id << endl;
			cout << name << endl;
			cout << city << endl;
			cout << sport << endl;
			cout << event << endl;
			cout << NOC << endl;
			cout << "- - - - - - - - - - - - " << endl;
		}
	};
}