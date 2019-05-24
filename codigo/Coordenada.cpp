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

void Coordenada::desX(double dx) {
	x += dx;
}

void Coordenada::desY(double dy) {
	y += dy;
}

double Coordenada::getX() {
	return x;
}

double Coordenada::getY() {
	return y;
}