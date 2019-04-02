#ifndef DIBUJOTANQUE_H_
#define DIBUJOTANQUE_H_

#include "Coordenada.h"
#include <vector>
using namespace std;

class DibujoTanque {
private:
	const double angulos[4] = {45, 315, 225, 135}; //Angulo vetice con respecto al centro del tanque, sentido horario
	const double largo = 6.5;
	const double ancho = 6.5;
	const double diagonal = 9.192388155425117; //diagonal entre vertices
	Coordenada posicion;	// centro del Tanque
	double dirTanque;		// Direccion (grados) tanque respecto al Norte
	double dirCanion;		// Direccion (grados) canion respecto al tanque
public:
	DibujoTanque(Coordenada, double, int);
	void setPosicion(Coordenada);
	void setDirTanque(double);
	void setDirCanion(int);
	Coordenada getPosicion();
	double getDirTanque();
	int getDirCanion();
	vector<Coordenada> getCoordenadas();
};
#endif