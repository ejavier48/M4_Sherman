#include "DibujoTanque.h"
#include "Coordenada.h"
#include <cmath>
#include <vector>

#define PI 3.14159265359

using namespace std;

DibujoTanque::DibujoTanque(Coordenada pos, double dirT, int dirC) {
	posicion = pos;
	dirTanque = dirT;
	dirCanion = dirC;

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

Coordenada DibujoTanque::getPosicion() {
	return posicion;
}

double DibujoTanque::getDirTanque() {
	return dirTanque;
}

int DibujoTanque::getDirCanion() {
	return dirCanion;
}

vector<Coordenada> DibujoTanque::getCoordenadas() {

	double x;
	double y;

	double angulo;

	Coordenada aux;

	vector< Coordenada> coordenadas;

	for(int i = 0; i < 4; i++) {

		//angulo del vertice con respecto al centro del tanque mas angulo del tanque
		angulo = angulos[i] + dirTanque; 

		//verificar que el angulo no sea mayor a 360
		if(360 <= angulo) {
			angulo -= 360.0;
		}
		//transformacion grados a radianes
		angulo = (angulo * PI)/ 180.0;


		//calculo de las componentes x, y como si el tanque fuera el origen (0, 0)
		x = (diagonal/2) * cos(angulo);
		y = (diagonal/2) * sin(angulo);

		//se desplazan coordenadas al centro del tanque
		x += posicion.getX();
		y += posicion.getY();

		//se guardan los valores 
		aux = Coordenada(x, y);

		//se agrega coordenada al vector
		coordenadas.push_back(aux);
	}

	return coordenadas;
}
