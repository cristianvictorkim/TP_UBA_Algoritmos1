#include "osos_contra_reloj.h"
#include "test_de_personalidad.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char ARBOL = 'A';
const char PIEDRA = 'R';
const char KOALA = 'K';

const char LINTERNA = 'L';
const char VELA = 'V';
const char BENGALA = 'E';
const char PILA = 'B';

static const char POLAR = 'I';
static const char PANDA = 'P';
static const char PARDO = 'G';

const char CHLOE = 'C';

const char VACIO = 'O';

const int MAX_FILAS = 20;
const int MAX_COLUMNAS = 30;

const int MAX_ARBOLES = 350;
const int MAX_PIEDRAS = 80;

const int COLUMNA_NULA = 0;

const int MOVIMIENTOS_LINTERNA_PARDO = 15;
const int MOVIMIENTOS_LINTERNA_POLAR_PANDA = 10;
const int MOVIMIENTOS_VELA = 5;
const int MOVIMIENTOS_BENGALA = 3;
const int VELAS_POLAR = 6;
const int VELAS_PARDO_PANDA = 4;
const int BENGALAS_PANDA = 2;

const int MAX_PILAS = 30;
const int MAX_VELAS = 30;
const int MAX_BENGALAS = 10;

const char ARRIBA = 'W';
const char IZQUIERDA = 'A';
const char ABAJO = 'S';
const char DERECHA = 'D';
const char TIEMPO = 'T';

const int PRIMERA_FILA = 0;
const int PRIMERA_COLUMNA = 0;

const int ELEMENTO_SIN_USAR = -1;

bool es_personaje_pisado (juego_t juego, int fil, int col){

    return (fil == juego.personaje.posicion.fil && col == juego.personaje.posicion.col);
}

bool es_chloe_pisada (juego_t juego, int fil, int col){

    return (fil == juego.amiga_chloe.fil && col == juego.amiga_chloe.col);
}

bool es_obstaculo_pisado (juego_t juego, int fil, int col){

    bool superpuesta = false;
    int i;

    for (i=0; i<juego.cantidad_obstaculos; i++){
        if (fil == juego.obstaculos[i].posicion.fil && col == juego.obstaculos[i].posicion.col){
            superpuesta = true;
        }
    }
    return superpuesta;
}

bool es_herramienta_pisada (juego_t juego, int fil, int col){

    bool superpuesta = false;
    int i;

    for (i=0; i<juego.cantidad_herramientas; i++){
        if (fil == juego.herramientas[i].posicion.fil && col == juego.herramientas[i].posicion.col){
            superpuesta = true;
        }
    }
    return superpuesta;
}

bool es_jugada_valida(char jugada){

    return (jugada == ARRIBA || jugada == ABAJO || jugada == IZQUIERDA || jugada == DERECHA || 
            jugada == LINTERNA || jugada == VELA || jugada == TIEMPO);
}

void ubicar_personaje (juego_t* juego, char tipo_persoanje){

    juego->personaje.tipo = tipo_persoanje;
    //printf ("\nPersonaje: %c \n", juego->personaje.tipo);
    
    juego->personaje.posicion.fil = rand() % MAX_FILAS;
    juego->personaje.posicion.col = COLUMNA_NULA;
    printf ("\nPosicion inicial personaje: (%i %i) \n", juego->personaje.posicion.fil, juego->personaje.posicion.col);

    juego->personaje.elemento_en_uso = ELEMENTO_SIN_USAR;
    juego->personaje.ultimo_movimiento = DERECHA;
}

void ubicar_chloe (juego_t* juego){

    juego->amiga_chloe.fil = rand() % MAX_FILAS;
    juego->amiga_chloe.col = rand() % MAX_COLUMNAS;

    while (es_personaje_pisado (*juego, juego->amiga_chloe.fil, juego->amiga_chloe.col)){
        juego->amiga_chloe.fil = rand() % MAX_FILAS;
        juego->amiga_chloe.col = rand() % MAX_COLUMNAS;
    }  
    juego->chloe_visible = false;
    printf ("Posicion inicial Chloe: (%i %i) \n", juego->amiga_chloe.fil, juego->amiga_chloe.col);
}

void ubicar_arboles (juego_t* juego){

    int i;

    for (i=0; i<MAX_ARBOLES; i++){

        juego->obstaculos[i].tipo = ARBOL;
        juego->obstaculos[i].posicion.fil = rand() % MAX_FILAS;
        juego->obstaculos[i].posicion.col = rand() % MAX_COLUMNAS;
        //printf("for %i\n", i);

        while (es_personaje_pisado (*juego, juego->obstaculos[i].posicion.fil, juego->obstaculos[i].posicion.col) || 
               es_chloe_pisada (*juego, juego->obstaculos[i].posicion.fil, juego->obstaculos[i].posicion.col) ||
               es_obstaculo_pisado (*juego, juego->obstaculos[i].posicion.fil, juego->obstaculos[i].posicion.col)){
            juego->obstaculos[i].posicion.fil = rand() % MAX_FILAS;
            juego->obstaculos[i].posicion.col = rand() % MAX_COLUMNAS;
        }
        juego->obstaculos[i].visible = false;

        juego->cantidad_obstaculos++;  
    }
    //printf("sale del for");
    //printf("Cantidad de obstaculos con arboles: %i\n", juego->cantidad_obstaculos); 
    //printf("Obstaculo posicion %i: %c\n", 0, juego->obstaculos[0].tipo);
}

void ubicar_piedras (juego_t* juego){

    int i;
    //printf("%i\n", juego->cantidad_obstaculos);
    for (i=MAX_ARBOLES; i<MAX_ARBOLES+MAX_PIEDRAS; i++){

        juego->obstaculos[i].tipo = PIEDRA;
        juego->obstaculos[i].posicion.fil = rand() % MAX_FILAS;
        juego->obstaculos[i].posicion.col = rand() % MAX_COLUMNAS;

        while (es_personaje_pisado (*juego, juego->obstaculos[i].posicion.fil, juego->obstaculos[i].posicion.col) || 
               es_chloe_pisada (*juego, juego->obstaculos[i].posicion.fil, juego->obstaculos[i].posicion.col) ||
               es_obstaculo_pisado (*juego, juego->obstaculos[i].posicion.fil, juego->obstaculos[i].posicion.col)){
            juego->obstaculos[i].posicion.fil = rand() % MAX_FILAS;
            juego->obstaculos[i].posicion.col = rand() % MAX_COLUMNAS;
        }
        juego->obstaculos[i].visible = false;
        //printf("Obstaculo posicion %i: %c\n", juego->cantidad_obstaculos, juego->obstaculos[juego->cantidad_obstaculos].tipo);
        juego->cantidad_obstaculos++;
    }
    //printf("Cantidad de obstaculos con piedras: %i\n", juego->cantidad_obstaculos); 
}

void ubicar_koala (juego_t* juego){

    int tope = juego->cantidad_obstaculos;

    juego->obstaculos[tope].tipo = KOALA;
    juego->obstaculos[tope].posicion.fil = rand() % MAX_FILAS;
    juego->obstaculos[tope].posicion.col = rand() % MAX_COLUMNAS;

    while (es_personaje_pisado (*juego, juego->obstaculos[tope].posicion.fil, juego->obstaculos[tope].posicion.col) || 
           es_chloe_pisada (*juego, juego->obstaculos[tope].posicion.fil, juego->obstaculos[tope].posicion.col) ||
           es_obstaculo_pisado (*juego, juego->obstaculos[tope].posicion.fil, juego->obstaculos[tope].posicion.col)){
        juego->obstaculos[tope].posicion.fil = rand() % MAX_FILAS;
        juego->obstaculos[tope].posicion.col = rand() % MAX_COLUMNAS;    
    }
    printf("Posicion de koala: (%i %i)\n", juego->obstaculos[tope].posicion.fil, juego->obstaculos[tope].posicion.col);
    //printf("Salgo de koala");
    juego->obstaculos[tope].visible = false;
    juego->cantidad_obstaculos++;
    //printf("Salgo de koala");
}

void cargar_linterna (juego_t* juego){
   
    int tope = juego->personaje.cantidad_elementos;
    
    juego->personaje.mochila[tope].tipo = LINTERNA;

    if (juego->personaje.tipo == PARDO){
        juego->personaje.mochila[tope].movimientos_restantes = MOVIMIENTOS_LINTERNA_PARDO;
    }
    else{
        juego->personaje.mochila[tope].movimientos_restantes = MOVIMIENTOS_LINTERNA_POLAR_PANDA;
    }
    juego->personaje.cantidad_elementos ++;
    //printf("Movimientos restantes: %i\n", juego->personaje.mochila[tope].movimientos_restantes);
}

void cargar_velas (juego_t* juego){

    int i;
    int tope = juego->personaje.cantidad_elementos;

    if (juego->personaje.tipo == POLAR){
        for (i=tope; i<tope+VELAS_POLAR; i++){
            juego->personaje.mochila[i].tipo = VELA;
            juego->personaje.mochila[i].movimientos_restantes = MOVIMIENTOS_VELA;
            juego->personaje.cantidad_elementos ++;
        }
    }
    else{
        for (i=tope; i<VELAS_PARDO_PANDA; i++){
            juego->personaje.mochila[i].tipo = VELA;
            juego->personaje.mochila[i].movimientos_restantes = MOVIMIENTOS_VELA;
            juego->personaje.cantidad_elementos ++;
        }
    }
}

void cargar_bengalas (juego_t* juego){

    int i;
    int tope = juego->personaje.cantidad_elementos;

    if (juego->personaje.tipo == PANDA){
        for (i=tope; i<tope+BENGALAS_PANDA; i++){
            juego->personaje.mochila[i].movimientos_restantes = MOVIMIENTOS_BENGALA;
            juego->personaje.cantidad_elementos ++;
        }
    }
}

void ubicar_pilas (juego_t* juego){

    int i;

    for (i=0; i<MAX_PILAS; i++){
        juego->herramientas[i].tipo = PILA;
        juego->herramientas[i].posicion.fil = rand() % MAX_FILAS;
        juego->herramientas[i].posicion.col = rand() % MAX_COLUMNAS;

        while(es_personaje_pisado(*juego, juego->herramientas[i].posicion.fil, juego->herramientas[i].posicion.col) ||
        es_chloe_pisada(*juego, juego->herramientas[i].posicion.fil, juego->herramientas[i].posicion.col)||
        es_obstaculo_pisado(*juego, juego->herramientas[i].posicion.fil, juego->herramientas[i].posicion.col)||
        es_herramienta_pisada(*juego, juego->herramientas[i].posicion.fil, juego->herramientas[i].posicion.col)){

            juego->herramientas[i].posicion.fil = rand() % MAX_FILAS;
            juego->herramientas[i].posicion.col = rand() % MAX_COLUMNAS;
        }
        juego->herramientas[i].visible = false;
        juego->cantidad_herramientas++;
    }
}

void ubicar_velas (juego_t* juego){

    int i;

    for (i=MAX_PILAS; i<MAX_PILAS+MAX_VELAS; i++){
        juego->herramientas[i].tipo = VELA;
        juego->herramientas[i].posicion.fil = rand() % MAX_FILAS;
        juego->herramientas[i].posicion.col = rand() % MAX_COLUMNAS;

        while(es_personaje_pisado(*juego, juego->herramientas[i].posicion.fil, juego->herramientas[i].posicion.col) ||
              es_chloe_pisada(*juego, juego->herramientas[i].posicion.fil, juego->herramientas[i].posicion.col)||
              es_obstaculo_pisado(*juego, juego->herramientas[i].posicion.fil, juego->herramientas[i].posicion.col)||
              es_herramienta_pisada(*juego, juego->herramientas[i].posicion.fil, juego->herramientas[i].posicion.col)){

            juego->herramientas[i].posicion.fil = rand() % MAX_FILAS;
            juego->herramientas[i].posicion.col = rand() % MAX_COLUMNAS;
        }
        juego->herramientas[i].visible = false;
        juego->cantidad_herramientas++;
    }
}

void ubicar_bengalas (juego_t* juego){

    int i;

    for (i=MAX_PILAS + MAX_VELAS; i<MAX_PILAS + MAX_VELAS + MAX_BENGALAS; i++){
        juego->herramientas[i].tipo = BENGALA;
        juego->herramientas[i].posicion.fil = rand() % MAX_FILAS;
        juego->herramientas[i].posicion.col = rand() % MAX_COLUMNAS;

        while(es_personaje_pisado(*juego, juego->herramientas[i].posicion.fil, juego->herramientas[i].posicion.col) ||
              es_chloe_pisada(*juego, juego->herramientas[i].posicion.fil, juego->herramientas[i].posicion.col)||
              es_obstaculo_pisado(*juego, juego->herramientas[i].posicion.fil, juego->herramientas[i].posicion.col)||
              es_herramienta_pisada(*juego, juego->herramientas[i].posicion.fil, juego->herramientas[i].posicion.col)){

            juego->herramientas[i].posicion.fil = rand() % MAX_FILAS;
            juego->herramientas[i].posicion.col = rand() % MAX_COLUMNAS;
        }
        juego->herramientas[i].visible = false;
        juego->cantidad_herramientas++;
    }
}

void inicializar_juego(juego_t* juego, char tipo_personaje){

    juego->cantidad_obstaculos = 0;
    juego->personaje.cantidad_elementos = 0;
    juego->cantidad_herramientas = 0;

    ubicar_personaje (juego, tipo_personaje);

    ubicar_chloe (juego);

    ubicar_arboles (juego);
    ubicar_piedras (juego);
    ubicar_koala (juego);
    //printf("ubique los obstaculos");

    cargar_linterna (juego);
    cargar_velas (juego);
    cargar_bengalas (juego);
    //printf("Solo falta ubicar herramientas");
    
    ubicar_pilas (juego);
    ubicar_velas (juego);
    ubicar_bengalas (juego);
}

int estado_juego(juego_t juego){

    int estado = 0;

    if (juego.personaje.posicion.fil == juego.amiga_chloe.fil && juego.personaje.posicion.col == juego.amiga_chloe.col){
        estado = -1;
    }
    return estado;
}

void iluminar_linterna (juego_t* juego){
    
    int col = juego->personaje.posicion.col;
    int fil = juego->personaje.posicion.fil;

    if(juego->personaje.ultimo_movimiento == ARRIBA){

        if(juego->amiga_chloe.fil < fil && juego->amiga_chloe.col == col){
            juego->chloe_visible = true;
        }
        for(int i=0; i<MAX_OBSTACULOS; i++){
            if(juego->obstaculos[i].posicion.fil < fil && juego->obstaculos[i].posicion.col == col){
                juego->obstaculos[i].visible = true;       
            }
        }
        for(int i=0; i<MAX_HERRAMIENTAS; i++){
            if(juego->herramientas[i].posicion.fil < fil && juego->herramientas[i].posicion.col == col){
                juego->herramientas[i].visible = true;       
            }
        }
    }
    if(juego->personaje.ultimo_movimiento == ABAJO){

        if(juego->amiga_chloe.fil > fil && juego->amiga_chloe.col == col){
            juego->chloe_visible = true;
        }
        for(int i=0; i<MAX_OBSTACULOS; i++){
            if(juego->obstaculos[i].posicion.fil > fil && juego->obstaculos[i].posicion.col == col){
                juego->obstaculos[i].visible = true;       
            }
        }
        for(int i=0; i<MAX_HERRAMIENTAS; i++){
            if(juego->herramientas[i].posicion.fil > fil && juego->herramientas[i].posicion.col == col){
                juego->herramientas[i].visible = true;       
            }
        }
    }
    if(juego->personaje.ultimo_movimiento == DERECHA){

        if(juego->amiga_chloe.fil == fil && juego->amiga_chloe.col > col){
            juego->chloe_visible = true;
        }
        for(int i=0; i<MAX_OBSTACULOS; i++){
            if(juego->obstaculos[i].posicion.fil == fil && juego->obstaculos[i].posicion.col > col){
                juego->obstaculos[i].visible = true;       
            }
        }
        for(int i=0; i<MAX_HERRAMIENTAS; i++){
            if(juego->herramientas[i].posicion.fil == fil && juego->herramientas[i].posicion.col > col){
                juego->herramientas[i].visible = true;       
            }
        }
    }
    if(juego->personaje.ultimo_movimiento == IZQUIERDA){

        if(juego->amiga_chloe.fil == fil && juego->amiga_chloe.col < col){
            juego->chloe_visible = true;
        }
        for(int i=0; i<MAX_OBSTACULOS; i++){
            if(juego->obstaculos[i].posicion.fil == fil && juego->obstaculos[i].posicion.col < col){
                juego->obstaculos[i].visible = true;       
            }
        }
        for(int i=0; i<MAX_HERRAMIENTAS; i++){
            if(juego->herramientas[i].posicion.fil == fil && juego->herramientas[i].posicion.col < col){
                juego->herramientas[i].visible = true;       
            }
        }
    }
    
}

void encender_linterna (juego_t* juego){

    int i;

    for(i=0; i<MAX_HERRAMIENTAS; i++){

        if(juego->personaje.mochila[i].tipo == LINTERNA && juego->personaje.mochila[i].movimientos_restantes > 0){

            juego->personaje.elemento_en_uso = i;
            juego->personaje.mochila[i].movimientos_restantes --;
            
            iluminar_linterna(juego);       
        }
    }
}

void apagar_linterna (juego_t* juego){
    juego->personaje.elemento_en_uso = ELEMENTO_SIN_USAR;
}

void iluminar_vela (juego_t* juego){

    int col = juego->personaje.posicion.col;
    int fil = juego->personaje.posicion.fil;

    if((juego->amiga_chloe.fil <= fil+1 && juego->amiga_chloe.fil >= fil-1) || 
       (juego->amiga_chloe.col <= col+1 && juego->amiga_chloe.col >= col-1)){

        juego->chloe_visible = true;
    }

}

void encender_vela (juego_t* juego){

    int i;

    for(i=0; i<MAX_HERRAMIENTAS; i++){

        if(juego->personaje.mochila[i].tipo == VELA && juego->personaje.mochila[i].movimientos_restantes > 0){

            juego->personaje.elemento_en_uso = i;
            juego->personaje.mochila[i].movimientos_restantes --;
            
            iluminar_vela(juego);       
        }
    }
}


void realizar_jugada(juego_t* juego, char jugada){
    
    if (jugada == ARRIBA && juego->personaje.posicion.fil != PRIMERA_FILA){
        juego->personaje.posicion.fil--;
    }
    else if (jugada == IZQUIERDA && juego->personaje.posicion.col != PRIMERA_COLUMNA){
        juego->personaje.posicion.col--;
    }
    else if (jugada == ABAJO && juego->personaje.posicion.fil != MAX_FILAS){
        juego->personaje.posicion.fil++;
    }
    else if (jugada == DERECHA && juego->personaje.posicion.col != MAX_COLUMNAS){
        juego->personaje.posicion.col++;
    }
    else if (jugada == LINTERNA && juego->personaje.elemento_en_uso == ELEMENTO_SIN_USAR){
        encender_linterna(juego);
    }
    else if (jugada == LINTERNA && juego->personaje.elemento_en_uso != ELEMENTO_SIN_USAR){
        apagar_linterna(juego);
    }
    else if (jugada == VELA && juego->personaje.elemento_en_uso == ELEMENTO_SIN_USAR){
        encender_vela(juego);
    }
}

void vaciar_mapa (juego_t juego, char mapa[MAX_FILAS][MAX_COLUMNAS]){

    int i;
    int j;

    for(i=0; i<MAX_FILAS; i++){
        for(j=0; j<MAX_COLUMNAS; j++){
            mapa[i][j]= ' ';
        }
    }
}

void cargar_mapa (juego_t juego, char mapa[MAX_FILAS][MAX_COLUMNAS]){

    int i;
    
    for (i=0; i<juego.cantidad_obstaculos; i++){

        int fil = juego.obstaculos[i].posicion.fil;
        int col = juego.obstaculos[i].posicion.col;

        if (juego.obstaculos[i].visible == true){
            mapa[fil][col] = juego.obstaculos[i].tipo;
        }
    }
    
    for (i=0; i<juego.cantidad_herramientas; i++){

        int fil = juego.herramientas[i].posicion.fil;
        int col = juego.herramientas[i].posicion.col;

        if ((juego.herramientas[i].tipo == PILA && juego.herramientas[i].visible == true)){
            mapa[fil][col] = juego.herramientas[i].tipo;
        }
    }

    mapa[juego.personaje.posicion.fil][juego.personaje.posicion.col] = juego.personaje.tipo;

    mapa[juego.amiga_chloe.fil][juego.amiga_chloe.col] = CHLOE;
}

void imprimir_mapa (juego_t juego, char mapa[MAX_FILAS][MAX_COLUMNAS]){

    int i;
    int j;

    printf ("\n");
    printf ("      ");
    for (i=0; i<MAX_COLUMNAS; i++){
        if (i<10){
        printf ("%i   ", i);
        }
        else{
            printf("%i  ", i);
        }
    }
    
    /*
    printf ("\n");
    printf ("     ");
    for (i=0; i<MAX_COLUMNAS; i++){
        printf ("___ ");
    }
    */

    printf ("\n");
    for (i=0; i<MAX_FILAS; i++){
        if (i<10){
            printf("  %i ", i);
        }
        else{
            printf(" %i ", i);
        } 

        for (j=0; j<MAX_COLUMNAS; j++){
            
            if (mapa[i][j] == CHLOE && juego.chloe_visible == true){
                printf ("| %c ", CHLOE);
            }
            else if (mapa[i][j] == ARBOL){
                printf ("| %c ", ARBOL);
            }
            else if (mapa[i][j] == PIEDRA){
                printf ("| %c ", PIEDRA);
            }
            else if (mapa[i][j] == KOALA){
                printf ("| %c ", KOALA);
            }
            else if (mapa[i][j] == PILA){
                printf ("| %c ", PILA);
            }
            else if (mapa[i][j] == VELA){
                printf ("| %c ", VELA);
            }
            else if (mapa[i][j] == BENGALA){
                printf ("| %c ", BENGALA);
            }
            else if (mapa[i][j] == juego.personaje.tipo){
                printf ("| %c ", juego.personaje.tipo);
            }
            else{
                printf ("|   ");
            }
        }
        printf ("|   ");
        printf ("\n");
    }
    /*
        printf ("     ");
        for (i=0; i<MAX_COLUMNAS; i++){
            printf ("─── ");
        }
    printf ("\n");
    */
    
}

void mostrar_juego(juego_t juego){

    char mapa[MAX_FILAS][MAX_COLUMNAS];
    vaciar_mapa (juego, mapa);
    cargar_mapa (juego, mapa);
    imprimir_mapa (juego, mapa);
}