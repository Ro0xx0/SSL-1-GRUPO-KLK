#include <stdio.h>
#include <ctype.h>
#include "scanner.h"

#define TAMANIO_BUFFER 20

typedef int ESTADO;

char _buffer[TAMANIO_BUFFER+1];
int  _pos = 0;

void LimpiarBuffer(void) {
    int c;
    while ((c= getchar()) != '\n' && c != EOF) { 
        _buffer[_pos] = '\0';
        _pos++;
    }
}

void AgregarCaracter(int caracter) {
    _buffer[_pos++] = caracter;
}

const char *Buffer(void) {
    _buffer[_pos] = '\0';
    return _buffer;
}

TOKEN EsReservada(void) {
    if(!strcmp(_buffer, "inicio") == 0) return INICIO;
    if (strcmp(_buffer, "fin") == 0) return FIN;
    if (strcmp(_buffer, "leer") == 0) return LEER;
    if (strcmp(_buffer, "escribir") == 0) return ESCRIBIR;
    return ID;
}

int ObtenerColumna(int simbolo) {
    if (isalpha(simbolo)) {  
        return 0; //Letra (L)
    } else if (isdigit(simbolo)) {
        return 1;
    } else if (isspace(simbolo)) {
        return 11;
    }

    switch (simbolo) {
        case '+': return 2;
        case '-': return 3;
        case '(': return 4;
        case ')': return 5;
        case ',': return 6;
        case ';': return 7;
        case ':': return 8;
        case '=': return 9;
        case -1: return 10;
        default: return 12;
    }
}

ESTADO Transicion(ESTADO estado, int simbolo) {
    static ESTADO TT[12][13] = {
    // 0   1   2   3   4   5   6   7   8   9  10   11  12 //
    // L   D   +   -   (   )   ,   ;   :   =  fdt  sp otro
    {  1,  3,  5,  6,  7,  8,  9, 10, 11, 14, 13,  0,  _ }, // Estado 0
    {  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  _,  2 }, // Estado 1
    { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,  _, 99 }, // Estado 2
    {  3,  4,  3,  4,  4,  4,  4,  4,  4,  4,  4,  _,  4 }, // Estado 3

    };
    
    int columna = ObtenerColumna(simbolo);
    return TT[estado][columna];
}

TOKEN Scanner(void) {
    TOKEN token = 0;
    int c, pos = 0;
    ESTADO estado = 0;
    LimpiarBuffer();
    while ((c = getchar()) != EOF) {
        estado = Transicion(estado, c);
        switch(estado)
        {
            case 1:
            case 3:
                AgregarCaracter(c);
                break;
            case 2:
                Buffer();
                ungetc(c, stdin);
                token = EsReservada();
                return token; /* ID */ //antes habia 4
            case 4:
                ungetc(c, stdin);
                return 5; /* CONSTANTE */
            case 5:
                AgregarCaracter(c);
                return 11; /* SUMA */
            case 6:
                AgregarCaracter(c);
                return 12; /* RESTA */
            case 7:
                AgregarCaracter(c);
                return 6;  /* PARENIZQUIERDO */
            case 8:
                AgregarCaracter(c);
                return 7;  /* PARENDERECHO */
            case 9:
                AgregarCaracter(c);
                return 9;  /* COMA */
            case 10:
                AgregarCaracter(c);
                return 8;  /* PUNTOYCOMA */
            case 11:
                AgregarCaracter(c);
                break;
            case 12:
                AgregarCaracter(c);
                return 10; /* ASIGNACION */
            case 99:
                return 13; // FDT
            case 13:
                return 13; /* FDT */
        }
    }
}
