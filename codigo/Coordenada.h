#ifndef COORDENADA_H_
#define COORDENADA_H_

class Coordenada {
private:
	double x;
	double y;
public:
	Coordenada();
	void setX(double);
	void setY(double);
	void desX(double);
	void desY(double);
	double getX();
	double getY();
	Coordenada(double xx, double yy);
};
#endif