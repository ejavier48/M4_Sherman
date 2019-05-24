#ifndef DISPARO_H_
#define DISPARO_H_

#include "Coordenada.h"

class Disparo {
private:
	const double VELOCIDAD = 100;
	Coordenada posTanque;
	short dirCanion;
	short eleCanion;
	double dirTanque;
public:
	Disparo();
	Disparo(Coordenada, short, short, double);
	~Disparo();
	
	void setPosicion(Coordenada);
	void setDirCanion(short);
	void setEleCanion(short);
	void setDirTanque(double);

	Coordenada getPosicion();
	short getDirCanion();
	short getEleCanion();
	double getDirTanque();
	double getVelocidad();
};
#endif