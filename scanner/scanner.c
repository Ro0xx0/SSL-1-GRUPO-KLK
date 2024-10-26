#include <stdio.h>
#include <ctype.h>
#include "scanner.h"

#define TAMANIO_BUFFER 20

typedef int ESTADO;

char _buffer[TAMANIO_BUFFER+1];
int  _pos = 0;

void LimpiarBuffer(void) {
}

void AgregarCaracter(int caracter) {
    _buffer[_pos++] = caracter;
}

const char *Buffer(void) {
    _buffer[_pos] = '\0';
    return _buffer;
}

TOKEN EsReservada(void) {
    return 4;
}

int ObtenerColumna(int simbolo) {
    if (isalpha(simbolo)) {
        return 0;
    } else if (isdigit(simbolo)) {
        return 1;
    } else if (simbolo == '+') {
        return 2;
    } else if (simbolo == '-') {
        return 3;
    } else if (simbolo == '(') {
        return 4;
    } else if (simbolo == ')') {
        return 5;
    } else if (simbolo == ',') {
        return 6;
    } else if (simbolo == ';') {
        return 7;
    } else if (simbolo == ':') {
        return 8;
    } else if (simbolo == '=') {
        return 9;
    } else if (simbolo == -1) {
        return 10;
    } else if (isspace(simbolo)) {
        return 11;
    }    
    return 12;
}


ESTADO Transicion(ESTADO estado, int simbolo) {
    static ESTADO TT[12][13] = {
        /*L   D   +   -   (   )   ,   ;   :   =  fdt  sp otro */
        /* ¿y la tabla? ¿dónde está la tabla? */
    };
    int columna = ObtenerColumna(simbolo);
    return TT[estado][columna];
}

TOKEN Scanner(void) {
    TOKEN token = 0;
    int c, pos = 0;
    ESTADO estado = 0;
    LimpiarBuffer();
    while (c=getchar()) {
        estado = Transicion(estado, c);
        switch (estado) {
            case 1:
            case 3:
                AgregarCaracter(c);
                break;
            case 2:
                ungetc(c, stdin);
                return 4; /* ID */
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
                /* situacion rara. ¿cómo la podemos resolver? */
            case 13:
                return 13; /* FDT */
        }
    }
}
