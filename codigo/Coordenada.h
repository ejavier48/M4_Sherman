#ifndef COORDENADA_H_
#define COORDENADA_H_

class Coordenada {
private:
	double x;
	double y;
public:
	Coordenada();
	Coordenada(double xx, double yy);
	void setX(double);
	void setY(double);
	double getX();
	double getY();
};
#endif