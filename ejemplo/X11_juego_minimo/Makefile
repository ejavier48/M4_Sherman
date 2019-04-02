
uvideojuego:  uvideojuego.o gfxModified.o
	gcc uvideojuego.o gfxModified.o -o uvideojuego -lX11 -lm
uvideojuego.o: uvideojuego.c gfxModified.o
	gcc uvideojuego.c -c
gfxModified.o: gfxModified.c gfxModified.h
	gcc gfxModified.c -c