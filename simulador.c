
#include <math.h>
#include "simulador.h"
#include <stdio.h>

void calcularFase1(EstadoCohete_t *cohete, Configuracion_t *config) {
 cohete->tiempo = TIEMPO_FASE1;
 cohete->aceleracion = config->aceleracionFase1;

 cohete->velocidad = VELOCIDAD_INICIAL + config->aceleracionFase1 * TIEMPO_FASE1;

 cohete->altura = ALTURA_INICIAL + VELOCIDAD_INICIAL * TIEMPO_FASE1 + 0.5 * config->aceleracionFase1 * TIEMPO_FASE1 * TIEMPO_FASE1;
}               

void calcularFase2(EstadoCohete_t *cohete, Configuracion_t *config) {
 double distancia;
 double velocidadFinal;
 double tiempoFase2;

 distancia = config->alturaApagado - cohete->altura;

 velocidadFinal = sqrt(cohete->velocidad * cohete->velocidad + 2 * config->aceleracionFase2 * distancia);

 tiempoFase2 = (velocidadFinal - cohete->velocidad) / config->aceleracionFase2;

 cohete->tiempo = cohete->tiempo + tiempoFase2;
 cohete->altura = config->alturaApagado;
 cohete->velocidad = velocidadFinal;
 cohete->aceleracion = config->aceleracionFase2;
}


double calcularAceleracionMaxima(Configuracion_t *config) {
 double aceleracionMaxima;

 if (config->aceleracionFase1 > config->aceleracionFase2) {
    aceleracionMaxima = config->aceleracionFase1;
 } else {
    aceleracionMaxima = config->aceleracionFase2;
 }
    return aceleracionMaxima / GRAVEDAD;
}

double calcularAlturaMaxima(EstadoCohete_t *cohete) {
 double alturaMaxima;
 alturaMaxima = cohete->altura + (cohete->velocidad * cohete->velocidad) /(2 * GRAVEDAD);
 return alturaMaxima;
}

void guardarEnHistorial(Simulacion_t historial[], int *cantidad, Configuracion_t *config,
                        EstadoCohete_t *cohete, double alturaMaxima, double aceleracionMaxima) {
 int i;
 Simulacion_t nueva;

 nueva.config = *config;
 nueva.tiempoTotal = cohete->tiempo;
 nueva.velocidadApagado = cohete->velocidad;
 nueva.alturaMaxima = alturaMaxima;
 nueva.aceleracionMaxima = aceleracionMaxima;

 if (*cantidad < MAX_HISTORIAL) {
    historial[*cantidad] = nueva;
    (*cantidad)++;
 } else {
    /* Historial lleno: se descarta la simulacion mas vieja */
    for (i = 0; i < MAX_HISTORIAL - 1; i++) {
       historial[i] = historial[i + 1];
    }
    historial[MAX_HISTORIAL - 1] = nueva;
 }
}

void mostrarHistorial(Simulacion_t historial[], int cantidad) {
 int i;
 int mejor = 0;

 printf("\n=== HISTORIAL DE SIMULACIONES ===\n");

 if (cantidad == 0) {
    printf("Todavia no se realizo ninguna simulacion.\n");
    return;
 }

 printf("%-4s %-10s %-10s %-14s %-10s %-12s %-14s %-6s\n",
        "N", "a1(m/s2)", "a2(m/s2)", "h apagado(m)", "t(s)", "v2(m/s)", "h max(m)", "g");

 for (i = 0; i < cantidad; i++) {
    printf("%-4d %-10.2f %-10.2f %-14.2f %-10.2f %-12.2f %-14.2f %-6.2f\n",
           i + 1,
           historial[i].config.aceleracionFase1,
           historial[i].config.aceleracionFase2,
           historial[i].config.alturaApagado,
           historial[i].tiempoTotal,
           historial[i].velocidadApagado,
           historial[i].alturaMaxima,
           historial[i].aceleracionMaxima);

    if (historial[i].alturaMaxima > historial[mejor].alturaMaxima) {
       mejor = i;
    }
 }

 printf("\nMejor desempeno: simulacion N %d (altura maxima %.2f m).\n",
        mejor + 1, historial[mejor].alturaMaxima);
}