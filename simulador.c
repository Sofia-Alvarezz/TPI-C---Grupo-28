
#include <math.h>
#include "simulador.h"


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

 velocidadFinal = sqrt(
    cohete->velocidad * cohete->velocidad +
    2 * config->aceleracionFase2 * distancia
 );

 tiempoFase2 = (velocidadFinal - cohete->velocidad) / config->aceleracionFase2;

 cohete->tiempo = cohete->tiempo + tiempoFase2;
 cohete->altura = config->alturaApagado;
 cohete->velocidad = velocidadFinal;
 cohete->aceleracion = config->aceleracionFase2;
 tiempoFase2 = (velocidadFinal - cohete->velocidad) / ACELERACION_FASE2;

 cohete->tiempo = cohete->tiempo + tiempoFase2;
 cohete->altura = ALTURA_APAGADO;
 cohete->velocidad = velocidadFinal;
 cohete->aceleracion = ACELERACION_FASE2;
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

