test: test.o TableroCliente.o DibujoTanque.o InfoTanque.o Disparo.o Coordenada.o gfxModified.o
	g++ test.o TableroCliente.o DibujoTanque.o InfoTanque.o Disparo.o Coordenada.o gfxModified.o -o testDibujo.o -std=c++11 -lX11 -lpthread
test.o: test.cpp
	g++ test.cpp -Wall -c
TableroCliente.o: TableroCliente.cpp
	g++ TableroCliente.cpp -Wall -c
DibujoTanque.o: DibujoTanque.cpp Coordenada.o
	g++ DibujoTanque.cpp -Wall -c
InfoTanque.o: InfoTanque.cpp
	g++ InfoTanque.cpp -Wall -c
Disparo.o:	Disparo.cpp
	g++ Disparo.cpp -Wall -c
Coordenada.o: Coordenada.cpp
	g++ Coordenada.cpp -Wall -c
gfxModified.o:
	gcc gfxModified.c -Wall -c
clean:
	rm *.o ./testDibujo