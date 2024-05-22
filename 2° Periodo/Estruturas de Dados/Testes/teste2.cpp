#include<iostream>
using namespace std;

class Ponto2{
	public:
		int a1;
		float a2;
		string fds;
		Ponto2(int a1, float a2, string fds);
		int getA1(){
			return a1;
		}
};

Ponto2::Ponto2(int a1, float a2, string fds){
	this->a1 = a1;
	this->a2 = a2;
	this->fds = fds;
}

class Ponto{
	private:
		int x;
		int y;
	public:
		Ponto();
		Ponto(int x, int y);
		void mostrar();
		Ponto operator+(const Ponto &outro);
		Ponto operator+(const Ponto2 &p2);
		void operator+=(const Ponto &outro);
};

Ponto::Ponto(){

}

Ponto::Ponto(int x, int y){
	this->x = x;
	this->y = y;
}

void Ponto::mostrar(){
	cout << x << ", " << y << endl;
}

Ponto Ponto::operator+(const Ponto &outro){
	return Ponto(x + outro.x, y + outro.y);
}

Ponto Ponto::operator+(const Ponto2 &p2){
	return Ponto(x + p2.a1, y + p2.a2);
}

void Ponto::operator+=(const Ponto &outro){
	x += outro.x;
	y += outro.y;
}

main(){
	Ponto A(3, 5);
	Ponto B = Ponto(2, 4);
	A = A + B;

	A.mostrar();

	return 0;
}