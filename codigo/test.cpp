#include <vector>
#include <string>
#include <cstring>
#include <iostream>

#include <unistd.h>
#include <X11/Xlib.h>

#include "gfxModified.h"

#include "Coordenada.h"
#include "DibujoTanque.h"
#include "TableroCliente.h"

#define LARGO 800 
#define ALTO 600


using namespace std;

void testDibujoTanque() {
	DibujoTanque dTanque(Coordenada(0, 0), 0, 0);
	vector<Coordenada> coordenadas;
	Coordenada aux;

	for(double i = 0; i < 360; i+= 2.5) {
		dTanque.setDirTanque(i);
		coordenadas = dTanque.getCoordenadas();
		for(int j = 0; j < 4; j++) {
			aux = coordenadas[j];
			cout << "Coordenada " << j+1 << ": x=" <<  aux.getX() << ", y=" << aux.getY() << "\n"; 
		}
		cout << "\n";
	}
}

void testMovTanque() {
	DibujoTanque dTanque(Coordenada(0, 0), 0, 0);
	dTanque.acelerar();
	Coordenada aux;
	while(true) {
		aux = dTanque.getPosicion();
		cout << aux.getX() << " " << aux.getY() << '\n';
		usleep(500000);
	}
}

void dibujoTablero() {
	int vida = 100;
	gfx_open(LARGO, ALTO, "Dibujo Tanque");
	gfx_clear();

	//control panel
	gfx_color(192, 192, 192);
	gfx_fill_rectangle(600, 0, 200, 600);

	//healty bar perimeter
	gfx_color(0, 0, 0);
	gfx_fill_rectangle(649, 49, 102, 52);	

	//healty bar inside
	gfx_color(0, 102, 0);
	gfx_fill_rectangle(650, 50, 100, 50);

	//healty bar label
	char* text;
	string str = "Vida: " + to_string(vida) + "%";
	text = new char(str.size());
	memcpy(text, str.c_str(), str.size());
	gfx_color(0, 10, 20);
	gfx_text(655, 40, text);
	free(text);

	

	//speed inforamtion
	char *speed = new char(2);
	str = "Velocidad (km/hr)";
	text = new char(str.size());
	memcpy(text, str.c_str(), str.size());
	
	gfx_color(0, 10, 20);
	gfx_text(650, 180, text);
	
	free(text);

	for(int i= 0; i <= 20; i++) {

		//speed display
		gfx_color(0, 0, 0);
		gfx_fill_rectangle(650, 190, 100, 85);
		speed[0] = '0' + (i/10);
		speed[1] = '0' + (i%10);
		//tank speed
		cout << speed[0] << "\n";
		cout << speed[1] << "\n";
		gfx_color(255, 10, 10); 
		gfx_display_ascii(660, 200, 5, speed[0]);
		gfx_display_ascii(705, 200, 5, speed[1]);
		gfx_flush();
		sleep(2);
	}

	DibujoTanque dTanque(Coordenada(0, 0), 0, 0);
	dTanque.acelerar();
	Coordenada aux;
	while(true) {
		aux = dTanque.getPosicion();
		cout << aux.getX() << " " << aux.getY() << '\n';
		usleep(500000);
	}

	short p1 = 287;
	short p2 = 313;

	short pi1 = 292;
	short pi2 = 308;

	XPoint tanq[5];
	tanq[0].x = p1;
	tanq[0].y = p1;

	tanq[1].x = p2;
	tanq[1].y = p1;

	tanq[2].x = p2;
	tanq[2].y = p2;

	tanq[3].x = p1;
	tanq[3].y = p2;

	tanq[4].x = p1;
	tanq[4].y = p1;

	XPoint tanqInt[5];
	tanqInt[0].x = pi1;
	tanqInt[0].y = p1;

	tanqInt[1].x = pi2;
	tanqInt[1].y = p1;

	tanqInt[2].x = pi2;
	tanqInt[2].y = p2;

	tanqInt[3].x = pi1;
	tanqInt[3].y = p2;

	tanqInt[4].x = pi1;
	tanqInt[4].y = p1;



	short movesX[] = {1,0,-1,0};
	short movesy[] = {0,1,0,-1};

	gfx_polygon(tanq, 5);
	gfx_polygon(tanqInt, 5);
	gfx_flush();

	while(true) {
		continue;
	}
	return;
}

int main(int args, char* argv[]) {
	if(args < 4) {
		cout << "Error, favor de ingresar IP y puerto del servidor, y equipo para iniciar el programa\n";
		cout << "./tanque IP puerto equipo\n";
		return 0;

	}
	TableroCliente tablero(argv[1], atoi(argv[2]), atoi(argv[3]));
	cout << tablero.getStatus() << "\n";
	tablero.dibujaTablero();
	while(true) {
		tablero.checkAcciones();
		tablero.dibujaTablero();
		usleep(18000);
	}
	return 0;
}