#include <cmath>
#include <vector>
#include <thread>
#include <iostream>

#include <unistd.h>

#include "Disparo.h"
#include "Coordenada.h"
#include "DibujoTanque.h"

using namespace std;

DibujoTanque::DibujoTanque() { 
	diagonal_ex = sqrt(pow(LARGO_EX, 2) + pow(ANCHO_EX, 2));
	diagonal_in = sqrt(pow(LARGO_IN, 2) + pow(ANCHO_IN, 2));
	initCoords(); 
}

DibujoTanque::DibujoTanque(Coordenada pos) {
	diagonal_ex = sqrt(pow(LARGO_EX, 2) + pow(ANCHO_EX, 2));
	diagonal_in = sqrt(pow(LARGO_IN, 2) + pow(ANCHO_IN, 2));
	initCoords();
	posicion = pos;
	dirTanque = 0;
	dirCanion = 0;
	eleCanion = 0;

	active = true;

	salud = 100;
	velocidad = 0;
	tDes = -1;
	movTanque = thread(&DibujoTanque::desplazamientoTanque, this);
}

DibujoTanque::DibujoTanque(Coordenada pos, double dirT, int dirC) {
	diagonal_ex = sqrt(pow(LARGO_EX, 2) + pow(ANCHO_EX, 2));
	diagonal_in = sqrt(pow(LARGO_IN, 2) + pow(ANCHO_IN, 2));
	initCoords();
	posicion = pos;
	dirTanque = dirT;
	dirCanion = dirC;
	eleCanion = 0;

	active = true;

	salud = 100;
	velocidad = 0;
	tDes = -1;

	movTanque = thread(&DibujoTanque::desplazamientoTanque, this);
}

void DibujoTanque::inicializaDT(Coordenada pos) {
	posicion = pos;
	dirTanque = 0;
	dirCanion = 0;
	eleCanion = 0;

	active = true;

	salud = 100;
	velocidad = 0;
	tDes = -1;
	movTanque = thread(&DibujoTanque::desplazamientoTanque, this);
}

void DibujoTanque::initCoords() {
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

void DibujoTanque::acelerar() {
	//thread aceleracion
	if(velocidad < VEL_LIMIT) {
		velocidad++;
		tDes = (MSEG) * (1.0 / ( (velocidad*MTR_KM) / SEC_HR) );
	}
}

void DibujoTanque::desacelerar() {
	//thread aceleracion	
	if(0 < velocidad) {
		velocidad--;
		if(velocidad == 0) {
			tDes = -1;
		} else {
			tDes = (MSEG) * (1.0 / ( (velocidad*MTR_KM) / SEC_HR) );
		}
	}
}

void DibujoTanque::desplazamientoTanque() {
	double prevDir = -1, angulo;
	double dx, dy;
	while(active) {
		if(tDes == -1) {
			continue;
		} else {
			if(prevDir != dirTanque) {
				prevDir = dirTanque;
				angulo = ((dirTanque+90) * PI)/ 180.0;
				dx = cos(angulo);
				dy = sin(angulo);
				printf("Diff  %lf %lf %lf \n", tDes, dx, dy);;
			}
			posicion.desX(dx);
			posicion.desY(dy);
			usleep(tDes);
		}
	}
}

void DibujoTanque::giraTanqueDer() {
	if(0 < dirTanque) {
		dirTanque-= MOV_TANQUE;
	} else {
		dirTanque = MAX_INC_TANQ;
	}
}

void DibujoTanque::giraTanqueIzq() {
	if(dirTanque < MAX_INC_TANQ) {
		dirTanque += MOV_TANQUE;
	} else {
		dirTanque = 0;
	}
}

void DibujoTanque::giraCanionDer() {
	if(MIN_INC_CANION < dirCanion) {
		dirCanion -= MOV_CANION;
	}
}

void DibujoTanque::giraCanionIzq() {
	if(dirCanion < MAX_INC_CANION) {
		dirCanion += MOV_CANION;
	}
}

void DibujoTanque::elevaCanion() {
	if(eleCanion < MAX_ELE_CANION) {
		eleCanion += ELE_CANION;
	}
}

void DibujoTanque::deciendeCanion() {
	if(0 < eleCanion) {
		eleCanion -= ELE_CANION;
	}
}

void DibujoTanque::setPosicion(Coordenada pos) {

	posicion = pos;
}

void DibujoTanque::setDirTanque(double dirT) {
	
	dirTanque = dirT;
}

void DibujoTanque::setDirCanion(int dirC) {

	dirCanion = dirC;
}

void DibujoTanque::setSalud(int saludTan) {

	salud = saludTan;
}

void DibujoTanque::resetVelocidad() {
	velocidad = 0;
	tDes = -1;

}

Coordenada DibujoTanque::getPosicion() {

	return posicion;
}

double DibujoTanque::getDirTanque() {

	return dirTanque;
}

short DibujoTanque::getDirCanion() {
	return dirCanion;
}

short DibujoTanque::getEleCanion() {
	return  eleCanion;
}

double DibujoTanque::getRadio() {
	return RADIO;
}

int DibujoTanque::getSalud() {
	return salud;
}

int DibujoTanque::getVelocidad() {
	return velocidad;
}

Disparo DibujoTanque::dispara() {
	return Disparo(posicion, dirCanion, eleCanion, dirTanque);
}

vector<Coordenada> DibujoTanque::getCoordenadas() {

	double x;
	double y;

	double posY = posicion.getY(), posX = posicion.getX();

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

vector<Coordenada> DibujoTanque::getCoordGUI(Coordenada origen, double mtrPx) {

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

vector<Coordenada> DibujoTanque::getCoordIntGUI(Coordenada origen, double mtrPx) {

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

DibujoTanque::~DibujoTanque() {
	active = false;
	if(movTanque.joinable())
		movTanque.join();
}
