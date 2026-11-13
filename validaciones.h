#ifndef VALIDACIONES_H
#define VALIDACIONES_H

void limpiarBuffer(void);
int leerEntero(const char *mensaje, int minimo, int maximo);
double leerDouble(const char *mensaje, double minimo, double maximo);
char leerSiNo(const char *mensaje);

#endif