#include <iostream>
#include <vector>
#include "Coordenada.h"
#include "DibujoTanque.h"

using namespace std;

int main() {
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
	return 0;
}