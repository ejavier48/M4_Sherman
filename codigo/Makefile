test: test.o DibujoTanque.o Coordenada.o
	g++ test.o DibujoTanque.o Coordenada.o -o testDibujo
test.o: test.cpp
	g++ test.cpp -Wall -c
DibujoTanque.o: DibujoTanque.cpp Coordenada.o
	g++ DibujoTanque.cpp -Wall -c
Coordenada.o: Coordenada.cpp
	g++ Coordenada.cpp -Wall -c
clean:
	rm *.o ./testDibujo