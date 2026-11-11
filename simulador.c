
#include <math.h>
#include "simulador.h"

void calcularFase1(EstadoCohete_t *cohete) {
    cohete->tiempo = TIEMPO_FASE1;
    cohete->aceleracion = ACELERACION_FASE1;

    cohete->velocidad = VELOCIDAD_INICIAL +
                        ACELERACION_FASE1 * TIEMPO_FASE1;

    cohete->altura = ALTURA_INICIAL +
                     VELOCIDAD_INICIAL * TIEMPO_FASE1 +
                     0.5 * ACELERACION_FASE1 * TIEMPO_FASE1 * TIEMPO_FASE1;                     
}

void calcularFase2(EstadoCohete_t *cohete) {
    double distancia;
    double velocidadFinal;
    double tiempoFase2;

    distancia = ALTURA_APAGADO - cohete->altura;

    velocidadFinal = sqrt(
        cohete->velocidad * cohete->velocidad +
        2 * ACELERACION_FASE2 * distancia
    );

    tiempoFase2 = (velocidadFinal - cohete->velocidad) /
                  ACELERACION_FASE2;

    cohete->tiempo = cohete->tiempo + tiempoFase2;
    cohete->altura = ALTURA_APAGADO;
    cohete->velocidad = velocidadFinal;
    cohete->aceleracion = ACELERACION_FASE2;
}

double calcularAlturaMaxima(EstadoCohete_t *cohete) {
    double alturaMaxima;

    alturaMaxima = cohete->altura +
                   (cohete->velocidad * cohete->velocidad) /
                   (2 * GRAVEDAD);

    return alturaMaxima;
}

double calcularAceleracionMaxima(void) {
    double aceleracionMaxima;

    if (ACELERACION_FASE1 > ACELERACION_FASE2) {
        aceleracionMaxima = ACELERACION_FASE1;
    } else {
        aceleracionMaxima = ACELERACION_FASE2;
    }

    return aceleracionMaxima / GRAVEDAD;
}

