#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "validaciones.h"

/* Descarta todo lo que quedo en el buffer hasta el fin de linea */
void limpiarBuffer(void) {
    int caracter;
    while ((caracter = getchar()) != '\n' && caracter != EOF) {
    }
}

/* Si se cerro la entrada (Ctrl+Z / Ctrl+D) se termina el programa
   para evitar un bucle infinito */
static void verificarFinEntrada(void) {
    if (feof(stdin)) {
        printf("\nSe cerro la entrada. Finalizando el programa...\n");
        exit(1);
    }
}

int leerEntero(const char *mensaje, int minimo, int maximo) {
    int valor;
    char siguiente;
    int valido = 0;

    do {
        printf("%s", mensaje);

        /* Se lee el numero y el caracter siguiente: tiene que ser '\n',
           asi se rechazan entradas como "3abc" o "2.5" */
        if (scanf("%d%c", &valor, &siguiente) == 2 && siguiente == '\n') {
            if (valor >= minimo && valor <= maximo) {
                valido = 1;
            } else {
                printf("Error: ingrese un valor entre %d y %d.\n", minimo, maximo);
            }
        } else {
            verificarFinEntrada();
            printf("Error: debe ingresar un numero entero.\n");
            limpiarBuffer();
        }
    } while (!valido);

    return valor;
}

double leerDouble(const char *mensaje, double minimo, double maximo) {
    double valor;
    char siguiente;
    int valido = 0;

    do {
        printf("%s", mensaje);

        if (scanf("%lf%c", &valor, &siguiente) == 2 && siguiente == '\n') {
            if (valor >= minimo && valor <= maximo) {
                valido = 1;
            } else {
                printf("Error: ingrese un valor entre %.2f y %.2f.\n", minimo, maximo);
            }
        } else {
            verificarFinEntrada();
            printf("Error: debe ingresar un valor numerico.\n");
            limpiarBuffer();
        }
    } while (!valido);

    return valor;
}

char leerSiNo(const char *mensaje) {
    char respuesta;
    char siguiente;
    int valido = 0;

    do {
        printf("%s", mensaje);

        if (scanf(" %c%c", &respuesta, &siguiente) == 2 && siguiente == '\n') {
            respuesta = (char) tolower(respuesta);
            if (respuesta == 's' || respuesta == 'n') {
                valido = 1;
            } else {
                printf("Error: responda 's' o 'n'.\n");
            }
        } else {
            verificarFinEntrada();
            printf("Error: responda 's' o 'n'.\n");
            limpiarBuffer();
        }
    } while (!valido);

    return respuesta;
}





