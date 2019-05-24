#include "Disparo.h"

Disparo::Disparo() {}

Disparo::Disparo(Coordenada pos, short dCanion, short eCanion, double dTanque) {
	posTanque = pos;
	dirCanion = dCanion;
	eleCanion = eCanion;
	dirTanque = dTanque;
}

Disparo::~Disparo() {

}

void Disparo::setPosicion(Coordenada pos) {
	posTanque = pos;
	return ;
}

void Disparo::setDirCanion(short dCanion) {
	dirCanion = dCanion;
	return ;
}

void Disparo::setEleCanion(short eCanion) {
	eleCanion = eCanion;
	return ;
}

void Disparo::setDirTanque(double dTanque) {
	dirTanque = dTanque;
	return ;
}

Coordenada Disparo::getPosicion() {
	return posTanque;
}

short Disparo::getDirCanion() {
	return dirCanion;
}

short Disparo::getEleCanion() {
	return eleCanion;
}

double Disparo::getDirTanque() {
	return dirCanion;
}

double Disparo::getVelocidad() {
	return VELOCIDAD;
}
