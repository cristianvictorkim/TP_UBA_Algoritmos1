#include <stdio.h>
#include <stdlib.h>

const char DULCE = 'D';
const char SALADO = 'S';
const char AMARGO = 'A';

const char AZUL = 'A';
const char AMARILLO = 'Y';
const char VERDE = 'V';
const char NEGRO = 'N';
const char BLANCO = 'B';
const char ROSA = 'R';

const char VERDADERO = 'V';
const char FALSO = 'F';

const int FECHA_MINIMA = 1988;
const int FECHA_MAXIMA = 2008;

const int TALLE_MINIMA = 33;
const int TALLE_MAXIMA = 47;

const int ALTURA_MINIMA = 10;
const int ALTURA_MAXIMA = 250;

const int ALTURA_JOHNNYBRAVO = 180;
const int ALTURA_BELLOTA = 120;
const int ALTURA_POLLITO = 50;
const int ALTURA_BLUE = 140;
const int ALTURA_PUROHUESO = 200;
const int ALTURA_CORAJE = 30;

const int DIVISOR = 20;
const int SUMAR = 1;

const int SIN_ZAPATOS = 0;
const int MINIMO_TALLA1 = 33;
const int MAXIMO_TALLA1 = 37;
const int MINIMO_TALLA2 = 38;
const int MAXIMO_TALLA2 = 42;
const int MINIMO_TALLA3 = 43;
const int MAXIMO_TALLA3 = 47;

const int MINIMO_DUPLA_JHONNY_CORAJE = 1;
const int MAXIMO_DUPLA_JHONNY_CORAJE = 80;
const int MINIMO_DUPLA_HUESO_POLLITO = 81;
const int MAXIMO_DUPLA_HUESO_POLLITO = 160;
const int MINIMO_DUPLA_BLUE_BELLOTA = 161;
const int MAXIMO_DUPLA_BLUE_BELLOTA = 240;

/*
 * Pre: -
 * Post: Devolverá 'V' si la fecha esta entre los validos o 'F' si no.
 */
char es_fecha_valida (int fecha){

    char retorno = VERDADERO;

    if (fecha < FECHA_MINIMA || fecha > FECHA_MAXIMA){
        retorno = FALSO;
    }
    return retorno;
}

/*
 * Pre: -
 * Post: Devolverá 'V' si el sabor esta entre los validos o 'F' si no.
 */
char es_sabor_valido (char sabor){

    char retorno = VERDADERO;

    if (sabor != DULCE && sabor != SALADO && sabor != AMARGO){  
        retorno = FALSO;
    }
    return retorno;
} 

/*
 * Pre: -
 * Post: Devolverá 'V' si la talla esta entre los validos o 'F' si no.
 */
char es_talla_valida (int talla){

    char retorno = VERDADERO;

    if ((talla < TALLE_MINIMA || talla > TALLE_MAXIMA) && talla != SIN_ZAPATOS){
        retorno = FALSO;
    }
    return retorno;
}

/*
 * Pre: -
 * Post: Devolverá 'V' si el color esta entre los validos o 'F' si no.
 */
char es_color_valido (char color){

    char retorno = VERDADERO;

    if (color != AZUL && color != AMARILLO && color != ROSA && color != NEGRO && color != BLANCO && color != VERDE){  
        retorno = FALSO;
    }
    return retorno;
} 

/*
 * Pre: -
 * Post: devolverá 'V' si la altura esta entre los validos o 'F' si no.
 */
char es_altura_valida (int altura){

    char retorno = VERDADERO;

    if (altura < ALTURA_MINIMA || altura > ALTURA_MAXIMA){
        retorno = FALSO;
    }
    return retorno;
}

void mostrar_convencion_sabores(){
	printf("(D: dulce - S: salado - A: amargo): ");
}

void mostrar_convencion_colores(){
	printf("(A: azul - Y: amarillo - V: verde - N: negro - B: blanco - R: rosa): ");
}

/*
 * Pre: que los colores ingresados sean válidos
 * Post: devolverá un puntaje dependiendo del color preferido.
 */
int dar_puntos_colores (char color){

    int puntaje_color;
    
    if ((color == 'R') || (color == 'Y'))
        puntaje_color = 5;
    if ((color == 'N') || (color == 'B'))
        puntaje_color = 15;
    if ((color == 'A') || (color == 'V'))
        puntaje_color = 20;  

    //seguimiento
    printf ("\nPuntaje color: %d", puntaje_color);

    return puntaje_color; 
}

/*
 * Pre: que los sabores ingresados sean válidos
 * Post: devolverá un puntaje dependiendo del sabor preferido.
 */
int dar_puntos_sabores (char sabor){

    int puntaje_sabor;
    
    if (sabor == 'D')
        puntaje_sabor = 15;
    if (sabor == 'S')
        puntaje_sabor = 5;
    if (sabor == 'A')
        puntaje_sabor = 20;  

    //seguimiento
    printf ("\nPuntaje sabor: %d", puntaje_sabor);

    return puntaje_sabor;
}

/*
 * Pre: que las fechas ingresadas sean válidas
 * Post: devolverá un puntaje dependiendo del año.
 */
int dar_puntos_ano (int fecha){

    int puntaje_ano;

    puntaje_ano = (fecha % DIVISOR) + SUMAR;

    //seguimiento
    printf ("\nPuntaje ano: %d", puntaje_ano);

    return puntaje_ano;
}

/*
 * Pre: que las tallas ingresadas sean válidas
 * Post: devolverá un número multiplicador dependiendo de la talla.
 */
int dar_multiplicador_talla (int talle){

    int multip_talla;

    if (talle == 0)
        multip_talla = 1;
    if ((talle >= MINIMO_TALLA1) && (talle <= MAXIMO_TALLA1))
        multip_talla = 2;
    if ((talle >= MINIMO_TALLA2) && (talle <= MAXIMO_TALLA2))
        multip_talla = 3;
    if ((talle >= MINIMO_TALLA3) && (talle <= MAXIMO_TALLA3))
        multip_talla = 4;

    //seguimiento
    printf ("\nMultiplicador talla: %d", multip_talla);
    return multip_talla;
}

/*
 * Pre: -
 * Post: -
 */
void determinar_personaje (int puntos, int altura){

    int diferencia_JhonnyBravo = abs (ALTURA_JOHNNYBRAVO - altura);
    int diferencia_Coraje = abs (ALTURA_CORAJE - altura);
    int diferencia_PuroHueso = abs (ALTURA_PUROHUESO - altura);
    int diferencia_Pollito = abs (ALTURA_POLLITO - altura);
    int diferencia_Blue = abs (ALTURA_BLUE - altura);
    int diferencia_Bellota = abs (ALTURA_BELLOTA - altura);

    if ((puntos >= MINIMO_DUPLA_JHONNY_CORAJE) && (puntos <= MAXIMO_DUPLA_JHONNY_CORAJE)){ //Jhonny o Coraje
        if (diferencia_JhonnyBravo > diferencia_Coraje)
            printf ("\n\nEl personaje detectado es - Coraje -. \n");
        else
            printf ("\n\nEl personaje detectado es - Jhonny Bravo -. \n");
    }    
    if ((puntos >= MINIMO_DUPLA_HUESO_POLLITO) && (puntos <= MAXIMO_DUPLA_HUESO_POLLITO)){ //Puro Hueso o Pollito
        if (diferencia_PuroHueso > diferencia_Pollito)
            printf ("\n\nEl personaje detectado es - Pollito -. \n");
        else
            printf ("\n\nEl personaje detectado es - Puro Hueso -. \n");
    }
    if ((puntos >= MINIMO_DUPLA_BLUE_BELLOTA) && (puntos <= MAXIMO_DUPLA_BLUE_BELLOTA)){ //Blue o Bellota
        if (diferencia_Blue > diferencia_Bellota)
            printf ("\n\nEl personaje detectado es - Bellota -. \n");
        else
            printf ("\n\nEl personaje detectado es - Blue -. \n");
    }
}

int main(){

    int fecha_nacimiento;
    char preferencia_sabor;
    int talla_zapatos;
    char preferencia_color;
    int altura_personaje;
    int puntaje_total;

    printf ("\n¿Cuál es su fecha de nacimiento? (indicar un número entre 1988 y 2008): ");
    scanf ("%d", &fecha_nacimiento);
    while (es_fecha_valida (fecha_nacimiento) == FALSO){
        printf ("Indique una fecha válida (número entre 1988 y 2008): ");
        scanf ("%d", &fecha_nacimiento);
    }

    printf ("\n¿Cuál es su sabor preferido? ");
    mostrar_convencion_sabores();
    scanf (" %c", &preferencia_sabor);
    while (es_sabor_valido (preferencia_sabor) == FALSO){
        printf ("Indique un sabor válido ");
        mostrar_convencion_sabores();
        scanf (" %c", &preferencia_sabor);
    }

    printf ("\n¿Cuál es su talla de zapatos? (indicar un número entre 33 y 47): ");
    scanf ("%d", &talla_zapatos);
    while (es_talla_valida (talla_zapatos) == FALSO){
        printf ("Indique una talla válida (número entre 33 y 47): ");
        scanf ("%d", &talla_zapatos);
    }

    printf ("\n¿Cuál es su color preferido? ");
    mostrar_convencion_colores();
    scanf (" %c", &preferencia_color);
    while (es_color_valido (preferencia_color) == FALSO){
        printf ("Indique un color válido ");
        mostrar_convencion_colores();
        scanf (" %c", &preferencia_color);
    }

    printf ("\n¿Cuál es su altura? (indicar un número entre 10 y 250): ");
    scanf ("%d", &altura_personaje);
    while (es_altura_valida (altura_personaje) == FALSO){
        printf ("Indique una altura válida (número entre 10 y 250): ");
        scanf ("%d", &altura_personaje);
    }

    puntaje_total = (dar_puntos_sabores (preferencia_sabor) + dar_puntos_colores (preferencia_color) + 
                     dar_puntos_ano (fecha_nacimiento)) * (dar_multiplicador_talla (talla_zapatos));
    
    //seguimiento 
    printf ("\nEl puntaje total es de: %d", puntaje_total);

    determinar_personaje (puntaje_total, altura_personaje);
    
    return 0;
}