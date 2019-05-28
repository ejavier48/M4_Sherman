#ifndef INFOTANQUE_H_
#define INFOTANQUE_H_

#include <vector>

#include "Coordenada.h"

using namespace std;

class InfoTanque {
private:
	const double PI = 3.14159265359;
	const double angulos[4] = {45, 315, 225, 135};

	//medidas tanque
	const double LARGO_EX = 6.5;
	const double ANCHO_EX = 6.5;

	const double DIF_INTR = 1;

	const double RADIO = 1.5;

	double diagonal_ex;


	char equipo;
	short id;
	short salud;
	short dirCanion;
	double dirTanque;
	Coordenada posTanque;
	vector<Coordenada> contornoEx;
	vector<Coordenada> contornoIn;

	void initCoords();

public:

	InfoTanque();
	InfoTanque(char, short, short, short, double, Coordenada);
	~InfoTanque();

	void setEquipo(char);
	void setID(short);
	void setSalud(short);
	void setDirCanion(short);
	void setDirTanque(double);
	void setPosTanque(Coordenada);

	char getEquipo();
	short getId();
	short getSalud();
	short getDirCanion();
	double getDirTanque();
	double getRadio();
	Coordenada getPosTanque();

	vector<Coordenada> getCoordenadas();
	vector<Coordenada> getCoordGUI(Coordenada, double);
	vector<Coordenada> getCoordIntGUI(Coordenada, double);
};
#endif
