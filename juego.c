#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "osos_contra_reloj.h"
#include "utiles.h"

static const char ARRIBA = 'W';
static const char IZQUIERDA = 'A';
static const char ABAJO = 'S';
static const char DERECHA = 'D';

void pedir_jugada (juego_t* juego, char* jugada){
    
    printf("\nW: arriba     ");
    printf("A: izquierda  ");
    printf("S: abajo      ");
    printf("D: derecha  \n");
    printf("L: linterna   ");
    printf("V: vela       ");
    printf("E: bengala    ");
    printf("T: ver tiempo restante \n");
    printf("\nRealice la jugada: ");
    scanf(" %c", jugada);

    if (*jugada == ARRIBA || *jugada == ABAJO || *jugada == DERECHA || *jugada == IZQUIERDA){
        juego->personaje.ultimo_movimiento = *jugada;
    }
}

int main(){

    juego_t juego;
    char personaje = 'O';
    /*
    char personaje;
    test_de_personalidad (&personaje);
    */
    char jugada;

    srand ((unsigned)time(NULL));

    inicializar_juego (&juego, personaje);


    while(estado_juego(juego) == 0){
        system("clear");
        mostrar_juego (juego);
        pedir_jugada(&juego, &jugada);
        realizar_jugada(&juego, jugada);

        while (!es_jugada_valida(jugada)){
            system("clear");
            mostrar_juego (juego);
            printf ("\nJugada invalida!\n");
            pedir_jugada(&juego, &jugada);
            realizar_jugada(&juego, jugada);
        }
    }
    return 0;
}