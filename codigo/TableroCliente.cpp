#include <thread>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>

#include <unistd.h>
#include <X11/Xlib.h>

#include "gfxModified.h"

#include "Disparo.h"
#include "Coordenada.h"
#include "InfoTanque.h"
#include "DibujoTanque.h"
#include "TableroCliente.h"

using namespace std;

TableroCliente::TableroCliente(char* ipServidor, int portServidor, int myteam) {
	ip = new char(16);
	memcpy(ip, ipServidor, 16);
	port = portServidor;
	
	team = myteam;

	if(!unirJuego()) {
		status = false;
		return;
	}
	status = true;
	initTablero();

	prevSalud = -1;
	prevVel = -1;
	prevDirTanq = -1;
	prevDirCanion = -1;
	prevEleCanion = -1;

	mtrPx = .75;
	speed = new char(2);
	tanqDir = new char(4);

	text = new char(100);
	
	for(unsigned int i = 0; i < 100; i++)
		text[i] = '\0';
	//free(text);
	//acciones = thread(&TableroCliente::checkAcciones, this);
}

void TableroCliente::checkAcciones() {
	//while(1) {
	if(gfx_event_waiting2()) {
		event(gfx_keyPress());

	}
	//}
}

void TableroCliente::aumentaZoom() {
	if(mtrPx < MAX_ZOOM)
		mtrPx = mtrPx + ZOOM;
}

void TableroCliente::disminuyeZoom() {
	if(MIN_ZOOM < mtrPx)
		mtrPx = mtrPx - .025;
}

void TableroCliente::initTablero() {
	gfx_open(LARGO, ALTO, "Tablero");
	gfx_clear();

	//control panel
	gfx_color(192, 192, 192);
	gfx_fill_rectangle(600, 0, 200, 600);
	gfx_flush();
}

void TableroCliente::muestraSalud() {
	if(prevSalud != tanq.getSalud()) {
		 
		
		gfx_color(192, 192, 192);
		gfx_fill_rectangle(600, 0, 200, 100);

		prevSalud = tanq.getSalud();

		char aux[20];
		strcpy(aux, "Vida: ");
		strcat(aux, to_string(prevSalud).c_str() );
		
		gfx_color(0, 10, 20);
		gfx_text(655, 40, aux);

		//healty bar perimeter
		gfx_color(0, 0, 0);
		gfx_fill_rectangle(649, 49, 102, 52);	

		//healty bar inside
		gfx_color(0, 102, 0);
		gfx_fill_rectangle(650, 50, prevSalud, 50);
		gfx_flush();
	}

	return;
}

void TableroCliente::muestraVelocidad() {
	if(prevVel != tanq.getVelocidad()) {

		gfx_color(192, 192, 192);
		gfx_fill_rectangle(600, 130, 200, 90);	

		prevVel = tanq.getVelocidad();
		
		char aux[20];
		strcpy(aux, "Velocidad (km/hr)");
		
		gfx_color(0, 10, 20);
		gfx_text(650, 130, aux);

		//speed display
		gfx_color(0, 0, 0);
		gfx_fill_rectangle(650, 140, 100, 85);
		
		speed[0] = '0' + (prevVel/10);
		speed[1] = '0' + (prevVel%10);

		//tank speed
		gfx_color(255, 10, 10); 

		gfx_display_ascii(660, 150, 5, speed[0]);
		gfx_display_ascii(705, 150, 5, speed[1]);

		gfx_flush();

	}
	return;
}

void TableroCliente::muestraDirTanque() {
	if(prevDirTanq != tanq.getDirTanque()) {

		gfx_color(192, 192, 192);
		gfx_fill_rectangle(600, 250, 200, 70);			

		prevDirTanq = tanq.getDirTanque();
		int auxDir = prevDirTanq * 10;

		char aux[20];
		strcpy(aux, "Direccion Tanque");
		
		gfx_color(0, 10, 20);
		gfx_text(650, 250, aux);

		//speed display
		gfx_color(0, 0, 0);
		gfx_fill_rectangle(625, 260, 150, 65);
		

		int pdec = auxDir%10;
		auxDir /= 10;
		int uni = auxDir % 10;
		auxDir /= 10;
		int dec = auxDir % 10;
		auxDir /= 10;
		int cen = auxDir;
		cout << cen << " " << dec << " " << uni << " " << pdec << "\0\0\n";
		
		auxDir%= 100;
		tanqDir[0] = '0' + cen;
		tanqDir[1] = '0' + dec;
		tanqDir[2] = '0' + uni;
		tanqDir[3] = '0' + pdec;

		//tank speed
		gfx_color(255, 10, 10); 

		gfx_display_ascii(635, 267, 4, tanqDir[0]);
		gfx_display_ascii(670, 267, 4, tanqDir[1]);
		gfx_display_ascii(705, 267, 4, tanqDir[2]);
		
		//punto decimal
		gfx_fill_rectangle(734, 315, 5, 5);

		gfx_display_ascii(740, 267, 4, tanqDir[3]);

		gfx_flush();

	}
	return;
}

void TableroCliente::muestraDirCanion() {
	if(prevDirCanion != tanq.getDirCanion()) {
		
		gfx_color(192, 192, 192);
		gfx_fill_rectangle(600, 335, 100, 90);	

		prevDirCanion = tanq.getDirCanion();

		char aux[20];
		strcpy(aux, "Direccion");
		
		gfx_color(0, 10, 20);
		gfx_text(620, 345, aux);

		//speed display
		gfx_color(0, 0, 0);
		gfx_fill_rectangle(610, 352, 80, 65);
		

		tanqDir[0] = '0' + abs(prevDirCanion)/10;
		tanqDir[1] = '0' + abs(prevDirCanion)%10;

		//tank speed
		gfx_color(255, 10, 10); 

		if(prevDirCanion < 0)
			gfx_fill_rectangle(610, 382, 6, 4);

		gfx_display_ascii(619, 359, 4, tanqDir[0]);
		gfx_display_ascii(654, 359, 4, tanqDir[1]);

		gfx_flush();

	}
	return;
}

void TableroCliente::muestraEleCanion() {
	if(prevEleCanion != tanq.getEleCanion()) {
		
		
		gfx_color(192, 192, 192);
		gfx_fill_rectangle(700, 335, 100, 90);	

		prevEleCanion = tanq.getEleCanion();

		char aux[20];
		strcpy(aux, "Elevacion");

		gfx_color(0, 10, 20);
		gfx_text(720, 345, aux);


		gfx_color(0, 0, 0);
		gfx_fill_rectangle(710, 352, 80, 65);
		

		tanqDir[0] = '0' + abs(prevEleCanion)/10;
		tanqDir[1] = '0' + abs(prevEleCanion)%10;

		//tank speed
		gfx_color(255, 10, 10);
		gfx_display_ascii(719, 359, 4, tanqDir[0]);
		gfx_display_ascii(754, 359, 4, tanqDir[1]);

		gfx_flush();

	}
	return;
}


void TableroCliente::muestraDispEstado() {

	return;
}

void TableroCliente::dibujaTanque(InfoTanque& tx, Coordenada origen) {

	vector<Coordenada> coordEx = tx.getCoordGUI(origen, mtrPx);
	vector<Coordenada> coordIn = tx.getCoordIntGUI(origen, mtrPx);	

	unsigned int len = coordEx.size();
	
	XPoint coordsEx[5];
	XPoint coordsIn[5];
	
	for(unsigned i = 0; i < len; i++) {
		coordsEx[i].x = static_cast<short>(coordEx[i].getX());
		coordsEx[i].y = static_cast<short>(coordEx[i].getY());
		coordsIn[i].x = static_cast<short>(coordIn[i].getX());
		coordsIn[i].y = static_cast<short>(coordIn[i].getY());
	}

	gfx_color(255, 255, 255);
	gfx_polygon(coordsEx, len);
	gfx_polygon(coordsIn, len);
	gfx_circle(origen.getX(), origen.getY(), tx.getRadio()/mtrPx);
	gfx_flush();
}

void TableroCliente::dibujaTanque(DibujoTanque& tx, Coordenada origen) {

	vector<Coordenada> coordEx = tx.getCoordGUI(origen, mtrPx);
	vector<Coordenada> coordIn = tx.getCoordIntGUI(origen, mtrPx);	

	unsigned int len = coordEx.size();
	
	XPoint coordsEx[5];
	XPoint coordsIn[5];
	
	for(unsigned i = 0; i < len; i++) {
		coordsEx[i].x = static_cast<short>(coordEx[i].getX());
		coordsEx[i].y = static_cast<short>(coordEx[i].getY());
		coordsIn[i].x = static_cast<short>(coordIn[i].getX());
		coordsIn[i].y = static_cast<short>(coordIn[i].getY());
	}

	gfx_color(255, 255, 255);
	gfx_polygon(coordsEx, len);
	gfx_polygon(coordsIn, len);
	gfx_circle(origen.getX(), origen.getY(), tx.getRadio()/mtrPx);
	gfx_flush();
}

void TableroCliente::muestraMiTanque() {

	bool flag = false;

	gfx_color(0, 0, 0);
	gfx_fill_rectangle(0, 0, 600, 600);
	dibujaTanque(tanq, Coordenada(300, 300));
	
	//mostrar coordenadas ubicacion
	xs = tanq.getPosicion().getX();
	ys = tanq.getPosicion().getY();

	if(xs < XMIN) {
		flag = true;
		xs = XMIN;
	} else if(XMAX < xs) {
		flag = true;
		xs = XMAX;
	}

	if(ys < YMIN) {
		flag = true;
		ys = YMIN;
	} else if(YMAX < ys) {
		flag = true;
		ys = YMAX;
	}

	if(flag) {
		tanq.setPosicion(Coordenada(xs, ys));
		tanq.resetVelocidad();
	}


	gfx_color(255, 255, 255);
	
	char aux[20];
	for(int i = 0, dx, dy; i < 4; i++) {
		
		dx = xs + (COORD_X[i]*mtrPx);
		dy = ys + (COORD_Y[i]*mtrPx);

		//dx/= mtrPx;
		//dy/= mtrPx;

		if(dx < 0 || dy < 0) 
			continue;
		else
			sprintf(aux, "(%d,%d)", dx, dy);

		gfx_text(SHOW_POS_X[i], SHOW_POS_Y[i], aux);

	}
	gfx_flush();
	return;
}

bool TableroCliente::checkTanques() {
	bool flag = false;
	//
	return flag;
}

void TableroCliente::dibujaTanques() {

	return;
}

bool TableroCliente::unirJuego() {
	bool flag;
	//tanq = *(Tanque*)doOperation();
	tanq.inicializaDT(Coordenada(500, 500));
	flag = true;
	return flag;
}

void TableroCliente::enviaDisparo(Disparo disparo) {
	//doOpertaion()
	return;
}


void TableroCliente::panelControl() {
	muestraSalud();
	muestraVelocidad();
	muestraDispEstado();
	muestraDirTanque();
	muestraDirCanion();
	muestraEleCanion();
}

bool TableroCliente::getStatus() {
	return status;
}

void TableroCliente::dibujaTablero() {

	panelControl();
	
	muestraMiTanque();
	
	if(checkTanques()) {
		dibujaTanques();
	}
	
	return;
}

void TableroCliente::event(long key) {
	switch(key) {
		//tanque
		case 97:  //A move left
			cout << "T M L\0\n";
			tanq.giraTanqueIzq();
			break;
		case 119: //W speed up
			cout << "T M Ac\0\n";
			tanq.acelerar();
			break;
		case 115: //S speed down
			cout << "T M De\0\n";
			tanq.desacelerar();
			break;
		case 100: //D move right
			cout << "T M R\0\n";
			tanq.giraTanqueDer();
			break;
		//canion
		case 106: //J move left
			cout << "C M L\0\n";
			tanq.giraCanionIzq();
			break;
		case 105: //I move up
			cout << "C M U\0\n";
			tanq.elevaCanion();
			break;
		case 107: //K move down
			cout << "C M D\0\n";
			tanq.deciendeCanion();
			break;
		case 108: //L move right
			cout << "C M R\0\n";
			tanq.giraCanionDer();
			break;
		//disparo
		case 32: //space shoot
			cout << "Disparo\0\n";
			enviaDisparo(tanq.dispara());
			break;
		//zoom	
		case 117: //u zoom +
			cout << "Zoom In\0\n";
			aumentaZoom();
			break;
		case 111: //o ¡zoom -
			cout << "Zoom Out\0\n";
			disminuyeZoom();
			break;
		default:
			break;
	}
}

TableroCliente::~TableroCliente() {
	delete[] speed;
	delete[] tanqDir;
	delete[] ip;
	delete[] text;
}
