#ifndef DIBUJOTANQUE_H_
#define DIBUJOTANQUE_H_

#include <vector>
#include <thread>

#include "Disparo.h"
#include "Coordenada.h"

using namespace std;

class DibujoTanque {
private:
	const double PI = 3.14159265359;
	const double MSEG = 1000000; // microsegundos en 1 seg

	const int VEL_LIMIT = 16; //limite velocidad
	
	const double MTR_KM = 1000; // metros en 1 km
	const double SEC_HR = 3600; // segundos en 1 hr

	const int MOV_CANION = 1; // unidad desplazamiento canion
	const int MIN_INC_CANION = -45; //minima inclinacion canion
	const int MAX_INC_CANION = 45; //maxima inclinacion canion

	const int ELE_CANION = 1; //unidad de desplazamiento elevacion canion
	const int MAX_ELE_CANION = 45; //maxima elevacion de canion


	const double MOV_TANQUE = 2.5; // unidad desplazamiento tanque
	const double MAX_INC_TANQ = 357.5; // maxima inclinacion canion

	const double angulos[4] = {45, 315, 225, 135}; //Angulo vetice con respecto al centro del tanque, sentido horario

	//medidas tanque
	const double LARGO_EX = 6.5;
	const double ANCHO_EX = 6.5;

	const double LARGO_IN = 6.5;
	const double ANCHO_IN = 4.5;

	const double RADIO = 1.5;


	double diagonal_ex; //diagonal entre vertices
	double diagonal_in;


	short salud; // indicador de salud entre (0 - 100)

	short velocidad; // indicador de velocidad entre (0 - 16) km/hr

	double tDes; //tiempo para recorer un metro de acuerdo a la velocidad

	Coordenada posicion;	// centro del Tanque
	vector<Coordenada> contornoEx;
	vector<Coordenada> contornoIn;

	double dirTanque;		// Direccion (grados) tanque respecto al Norte
	short dirCanion;		// Direccion (grados) canion respecto al tanque
	short eleCanion;

	thread movTanque; //hilo para funcion de desplazamiento del tanque

	bool active;

	void initCoords();

	//funcion para el desplazamiento automatico del tanque
	void desplazamientoTanque();

public:
	//constructores
	DibujoTanque();
	DibujoTanque(Coordenada);
	DibujoTanque(Coordenada, double, int);

	void inicializaDT(Coordenada);

	//destructor
	~DibujoTanque();

	//incrementar velocidad
	void acelerar();

	//disminuir velocidad
	void desacelerar();

	//Rotacion tanque Derecha
	void giraTanqueDer();

	//Rotacion tanque Izquierda
	void giraTanqueIzq();

	//Rotacion canion derecha
	void giraCanionDer();

	//Rotacion canion izquierda
	void giraCanionIzq();

	void elevaCanion();
	void deciendeCanion();

	void setPosicion(Coordenada);
	void setDirTanque(double);
	void setDirCanion(short);
	void setSalud(short);
	void resetVelocidad();

	Coordenada getPosicion();
	double getDirTanque();
	short getDirCanion();
	short getEleCanion();
	double getRadio();
	int getSalud();
	int getVelocidad();

	Disparo dispara();

	vector<Coordenada> getCoordenadas();
	vector<Coordenada> getCoordGUI(Coordenada, double);
	vector<Coordenada> getCoordIntGUI(Coordenada, double);
};
#endif