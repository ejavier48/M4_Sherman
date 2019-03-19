animacionv1: animacion.o gfx.o
	g++ -lX11 gfx.o animacion.o -o animacionv1
animacion.o: animacion.cpp
	g++ animacion.cpp -c
gfx.o: gfx.c gfx.h
	gcc gfx.c -c

