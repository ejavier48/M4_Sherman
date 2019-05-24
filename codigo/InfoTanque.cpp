#include <cmath>
#include <vector>

#include "Coordenada.h"
#include "InfoTanque.h"

using namespace std;



void InfoTanque::initCoords() {
	double x;
	double y;

	double angulo;

	Coordenada aux;

	for(int i = 0; i < 4; i++) {

		//angulo del vertice con respecto al centro del tanque mas angulo del tanque
		angulo = angulos[i];

		//transformacion grados a radianes
		angulo = (angulo * PI)/ 180.0;

		//calculo de las componentes x, y como si el tanque fuera el origen (0, 0)
		x = (diagonal_ex * cos(angulo)) / 2;
		y = (diagonal_ex * sin(angulo)) / 2;

		 //cout << x << " " << y << "\n";

		//se guardan los valores 
		aux = Coordenada(x, y);

		//se agrega coordenada al vector
		contornoEx.push_back(aux);
	}

	for(int i = 0; i < 4; i++) {
		x = contornoEx[i].getX();
		if(x < 0) 
			x += 1;
		else
			x -= 1;
		y = contornoEx[i].getY();
		//se guardan los valores 
		aux = Coordenada(x, y);

		//se agrega coordenada al vector
		contornoIn.push_back(aux);
	}
	return;
}

InfoTanque::InfoTanque() {
	diagonal_ex = sqrt(pow(LARGO_EX, 2) + pow(ANCHO_EX, 2));
	initCoords();
}

InfoTanque::InfoTanque(char idEquipo, short idTanque, short dCanion, double dTanque, Coordenada pos) {
	diagonal_ex = sqrt(pow(LARGO_EX, 2) + pow(ANCHO_EX, 2));
	equipo = idEquipo;
	id = idTanque;
	dirCanion = dCanion;
	dirTanque = dTanque;
	posTanque = pos;
	initCoords();
}

InfoTanque::~InfoTanque() {

}

void InfoTanque::setEquipo(char idEquipo) {
	equipo = idEquipo;
	return ;
}

void InfoTanque::setID(short idTanque) {
	id = idTanque;
	return ;
}


void InfoTanque::setDirCanion(short dCanion) {
	dirCanion = dCanion;
	return ;
}

void InfoTanque::setDirTanque(double dTanque) {
	dirTanque = dTanque;
	return ;
}

void InfoTanque::setPosTanque(Coordenada pos) {
	posTanque = pos;
	return ;
}

char InfoTanque::getEquipo() {
	return equipo;
}

short InfoTanque::getId() {
	return id;
}

short InfoTanque::getDirCanion() {
	return dirCanion;
}

double InfoTanque::getDirTanque() {
	return dirTanque;
}

double InfoTanque::getRadio() {
	return RADIO;
}

Coordenada InfoTanque::getPosTanque() {
	return posTanque;
}


vector<Coordenada> InfoTanque::getCoordenadas() {

	double x;
	double y;

	double posY = posTanque.getY(), posX = posTanque.getX();

	double angulo, cosD, sinD;

	//angulo del vertice con respecto al centro del tanque mas angulo del tanque
	angulo = (dirTanque * PI)/ 180.0;

	Coordenada aux;

	vector< Coordenada> coordenadas;

	cosD = cos(angulo);
	sinD = sin(angulo);

	for(int i = 0; i < 4; i++) {

		//calculo de las componentes x, y como si el tanque fuera el origen (0, 0)
		x = (contornoEx[i].getX() * cosD) - (contornoEx[i].getY() * sinD);
		y = (contornoEx[i].getX() * sinD) + (contornoEx[i].getY() * cosD);

		//se desplazan coordenadas al centro del tanque
		x += posX;
		y += posY;

		 //cout << x << " " << y << "\n";

		//se guardan los valores
		aux.setX(x);
		aux.setY(y);

		coordenadas.push_back(aux);
	}

	return coordenadas;
}

vector<Coordenada> InfoTanque::getCoordGUI(Coordenada origen, double mtrPx) {

	double posX =  origen.getX();
	double posY =  origen.getY();

	double angulo, cosD, sinD;
	double x, y;

	vector<Coordenada> coordenadas;

	Coordenada aux;

	//angulo del vertice con respecto al centro del tanque mas angulo del tanque
	angulo = ((360 - dirTanque) * PI)/ 180.0;

	cosD = cos(angulo);
	sinD = sin(angulo);

	//cout << mtrPx << "\n";

	for(int i = 0; i < 4; i++) {

		//calculo de las componentes x, y como si el tanque fuera el origen (0, 0)
		x = (contornoEx[i].getX() * cosD) - (contornoEx[i].getY() * sinD);
		y = (contornoEx[i].getX() * sinD) + (contornoEx[i].getY() * cosD);

		x =	x/mtrPx;
		y = y/mtrPx;

		//se desplazan coordenadas al centro del tanque
		x += posX;
		y += posY;

		//cout << x << " " << y << "\n";

		//se guardan los valores
		aux.setX(x);
		aux.setY(y);

		coordenadas.push_back(aux);
	}

	coordenadas.push_back(coordenadas[0]);

	return coordenadas;
}

vector<Coordenada> InfoTanque::getCoordIntGUI(Coordenada origen, double mtrPx) {

	double posX =  origen.getX();
	double posY =  origen.getY();

	double angulo, cosD, sinD;
	double x, y;

	vector<Coordenada> coordenadas;

	Coordenada aux;

	//angulo del vertice con respecto al centro del tanque mas angulo del tanque
	angulo = ((360 - dirTanque) * PI)/ 180.0;

	cosD = cos(angulo);
	sinD = sin(angulo);

	//cout << mtrPx << "\n";

	for(int i = 0; i < 4; i++) {

		//calculo de las componentes x, y como si el tanque fuera el origen (0, 0)
		x = (contornoIn[i].getX() * cosD) - (contornoIn[i].getY() * sinD);
		y = (contornoIn[i].getX() * sinD) + (contornoIn[i].getY() * cosD);

		x =	x/mtrPx;
		y = y/mtrPx;

		//se desplazan coordenadas al centro del tanque
		x += posX;
		y += posY;

		//cout << x << " " << y << "\n";

		//se guardan los valores
		aux.setX(x);
		aux.setY(y);

		coordenadas.push_back(aux);
	}

	coordenadas.push_back(coordenadas[0]);

	return coordenadas;
}
