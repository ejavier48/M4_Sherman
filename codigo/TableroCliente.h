#ifndef TABLEROCLIENTE_H_
#define TABLEROCLIENTE_H_

#include <vector>
#include <thread>

#include "Disparo.h"
#include "Coordenada.h"
#include "InfoTanque.h"
#include "DibujoTanque.h"
//#include "Tanque.h"

using namespace std;

class TableroCliente {
private:
	const double XMIN = 0;
	const double YMIN = 0;
	const double XMAX = 1000;
	const double YMAX = 1000;


	const int ALTO = 600;
	const int LARGO = 800;

	const double ZOOM = .025;
	const double MAX_ZOOM = 1.275;
	const double MIN_ZOOM = 0.025;

	const short SHOW_POS_X[4] = {270, 545, 270, 5};
	const short SHOW_POS_Y[4] = {  15, 300, 590, 300};

	const short COORD_X[4] = {0, 300, 0, -300};
	const short COORD_Y[4] = {300, 0, -300, 0};

	char* ip;
	int port;
	int team; 

	bool status;

	char* text;
	char* speed;
	char* tanqDir;

	string str;

	short xs;
	short ys;
	double mtrPx;

	thread acciones;

	short prevVel;
	short prevSalud;
	double prevDirTanq;
	short prevDirCanion;
	short prevEleCanion;

	InfoTanque infoT;
	DibujoTanque tanq;

	InfoTanque* tanques;

	vector<InfoTanque> visibles;

	void initTablero();
	void dibujaTanque(DibujoTanque&, Coordenada);
	void dibujaTanque(InfoTanque&, Coordenada);

	void aumentaZoom();
	void disminuyeZoom();

	void muestraSalud();
	void muestraMiTanque();
	void muestraVelocidad();
	void muestraDirTanque();
	void muestraDirCanion();
	void muestraEleCanion();
	void muestraDispEstado();

	void panelControl();
	
	bool checkTanques();
	void dibujaTanques();
	
	void enviaDisparo();
	void enviaPosicion();
	
	bool unirJuego();
	void recibeInformacion();
	void enviaDisparo(Disparo);

	void event(long);

public:
	TableroCliente(char*, int, int);
	~TableroCliente();

	bool getStatus();
	
	void dibujaTablero();

	void checkAcciones();
};
#endif
