#include "Coordenada.h"

Coordenada::Coordenada() {}

Coordenada::Coordenada(double xx, double yy) {
	x = xx;
	y = yy;
}

void Coordenada::setX(double xx) {
	x = xx;
}

void Coordenada::setY(double yy) {
	y = yy;
}

double Coordenada::getX() {
	return x;
}

double Coordenada::getY() {
	return y;
}