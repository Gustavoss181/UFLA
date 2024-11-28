#include <iostream>
#include <fstream>
#include "header.hpp"
using namespace MeuCabecalho;
using namespace std;

int main(){
	ifstream bin("data_athlete_event.bin");
	
	if(bin){
		AthleteEvent linha;
		
		while(bin.read((char *) (&linha), sizeof(AthleteEvent)))
			linha.mostrarCampos();
		
		bin.close();
	}
    
    return 0;
}
