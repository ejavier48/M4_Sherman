/* Para compilar use:
gcc gfxModified.c -c
gcc final_ukranio1.c -c
gcc final_ukranio1.o gfxModified.o -o final_ukranio1 -lX11 -lm

libreria original gfx:
https://www3.nd.edu/~dthain/courses/cse20211/fall2013/gfx/
Tomado de: https://github.com/PatMyron/slime-volleyball
Originally created by Patrick Myron and Anna McMahon
Further Modified by Ukranio Coronilla
*/

#include <stdio.h>
#include <math.h>
#include "gfxModified.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



//Resolución de la pantalla
#define ANCHURA 800
#define ALTURA 600

typedef struct {
    float x;
    float y; //posicion

    float vx; //velocidad
    float vy;    

    int r;  //radio
    int color[3]; //Color de la pelota
}Pelota;

typedef struct {
    float x;
    float y; //posicion
    
    float vx; //velocidad
    float vy;
    
    int r;  //radio
    int color[3]; //Color del agente
}Agente;

void muevePelota(Pelota *pPelota, Agente* pJugador);
void checaColisiones(Pelota *pPelota, Agente* pAgente);
void mueveAgente(Agente *pJugador, bool tecla[6]);
void validaMovimientoAgente(Agente *pAgente);
void calculaDireccionPelota(Pelota *Ball, Agente *Player);

bool tecla[6];  //Arreglo para saber si una tecla de dirección se ha presionado

int main()
{
	Pelota pelota={ANCHURA/2, 10,0,0,10, {255,255,255}}, *pPelota;
    Agente jugador={ANCHURA/4,ALTURA,0,0,25, {87,1,2}}, *pJugador;
    int i;

    pPelota=&pelota;
    pJugador=&jugador;

    for(i=0;i<6;i++){
        tecla[i]=false;   //Inicializa arreglo
    }
    gfx_open(ANCHURA, ALTURA, "Ejemplo Micro Juego GFX");
    while(1) {
        if(gfx_event_waiting2()) {

            gfx_keyPress(tecla); //Obtiene la tecla que se ha presionado como siguiente evento
            
            mueveAgente(pJugador,tecla);
            validaMovimientoAgente(pJugador);            
        }
        
        muevePelota(pPelota, pJugador);
        //Dibuja la pelota
        gfx_color(pelota.color[0],pelota.color[1],pelota.color[2]);
        gfx_fill_arc(pelota.x - pelota.r, pelota.y - pelota.r, 2*pelota.r, 2*pelota.r, 0, 360*64);

        //Dibuja al jugador 
        gfx_color(jugador.color[0],jugador.color[1],jugador.color[2]);
        gfx_fill_arc(jugador.x - jugador.r, jugador.y - jugador.r, 2*jugador.r, 2*jugador.r, 0, 180*64);
       
		gfx_flush();
        usleep(18000);
    }

}

// Actualiza la velocidad y la posición de la pelota
void muevePelota(Pelota *pPelota, Agente* pAgente){
    //Checa para ver si la pelota colisiona con algo para cambiar su velocidad    
    checaColisiones(pPelota, pAgente);
    (pPelota->vy)+=.08; //Para simular la aceleración de la gravedad
    (pPelota->x) = (pPelota->x) + (pPelota->vx); //Cambios para x recordando v=d/t 
    (pPelota->y) = (pPelota->y) + (pPelota->vy);
    gfx_clear();
}

//checa los bordes de la pelota y actualiza su localización, el vector velocidad   cambia si la pelota choca con algo.
void checaColisiones(Pelota *pPelota, Agente* pAgente){
    float distContacto, agenteBolaDist;
    
    if((pPelota->x < pPelota->r) || (pPelota->x > (ANCHURA - pPelota->r)))  // colision lateral cambia al vector velocidad en x
        pPelota->vx = -pPelota->vx;
    if(pPelota->y < pPelota->r)   //colision en techo cambia el vector velocidad en y
        pPelota->vy = -pPelota->vy;
    if(pPelota->y >= (ALTURA - pPelota->r))   //colision en piso
        pPelota->vy = -pPelota->vy;
    
    //distancia entre el centro del agente y la pelota
    agenteBolaDist=sqrtf(powf(pAgente->y - pPelota->y,2)+powf(pAgente->x - pPelota->x,2));
    //distancia minima permisible entre los centros del agente y la pelota
    distContacto = pAgente->r + pPelota->r;
    //checa para ver si existe colision entre la pelota y el agente
    if(agenteBolaDist < distContacto)
        calculaDireccionPelota(pPelota,pAgente);
}


//Lee el arreglo tecla para realizar un movimiento a la izquierda o a la derecha dependiendo de la tecla que se presionó.
void mueveAgente(Agente *pJugador, bool tecla[6]){

    if ( tecla[3] == 1 ){  // Si se presionó la tecla de mover a la izquierda
        pJugador->x-=10;
    }
    if ( tecla[5] == 1 ){  // Si se presionó la tecla de mover a la derecha
        pJugador->x+=10;
    }
    gfx_flush();
}

//Después de que se ha presionado una tecla, la función se asegura que el agente no se ha salido de la pantalla
void validaMovimientoAgente(Agente *pAgente){
    
    //Limita al agente por la orilla derecha
    if((pAgente->x)>(ANCHURA-pAgente->r)){
        pAgente->x=(ANCHURA-pAgente->r);
    }
    //Limita al agente por la orilla izquierda
    if((pAgente->x)<(pAgente->r)){
        pAgente->x=(pAgente->r);
    }
    
}//end func


//Cambia la dirección de la pelota de acuerdo a las leyes de la física
void calculaDireccionPelota(Pelota *Bola, Agente *Jugador){ 
    //la velocidad absoluta de la pelota se inicializa a 10 después de que choca con la raqueta debido
    //a que de no hacerlo se movería mas lento cada vez
    float velocidadAbsoluta = 10;
    float pendienteEntreCentros;
    float difCentrosX,difCentrosY;
    float anguloEntreCentros;
    float velx, vely;

    difCentrosX = Bola->x - Jugador->x;
    difCentrosY = Bola->y - Jugador->y;
    //Aunque puede existir un denominador igual a cero, y pendiente infinita la función arco tangente si resuelve con argumento infinito
    pendienteEntreCentros = difCentrosY / difCentrosX ;
    anguloEntreCentros = atanf(pendienteEntreCentros);

    printf("difCentrosY =  %f, difCentrosX = %f, pendienteEntreCentros = %f, anguloEntreCentros = %f\n", difCentrosY, difCentrosX, pendienteEntreCentros, anguloEntreCentros );


    if(difCentrosX < 0 && difCentrosY < 0)
        anguloEntreCentros += acosf(-1.0); // Ajusta la restricción del angulo sumandole PI = 3.14159...
    
    velx =  velocidadAbsoluta * cosf(anguloEntreCentros);
    vely = velocidadAbsoluta * sinf(anguloEntreCentros);
    printf("Velocidad_X = %f, Velocidad_Y = %f\n\n", velx, vely);
    Bola->vx = velx;
    Bola->vy = vely;
    
}
