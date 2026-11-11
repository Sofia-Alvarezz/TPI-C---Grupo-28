
#ifndef SIMULADOR_H
#define SIMULADOR_H

#define VELOCIDAD_INICIAL 0.0
#define ALTURA_INICIAL 0.0
#define ACELERACION_FASE1 20.0
#define TIEMPO_FASE1 120.0
#define ACELERACION_FASE2 12.5
#define ALTURA_APAGADO 160000.0
#define GRAVEDAD 9.8

typedef struct {
    double tiempo;
    double altura;
    double velocidad;
    double aceleracion;
} EstadoCohete_t;

typedef struct {
    double aceleracionFase1;
    double aceleracionFase2;
    double alturaApagado;
} Configuracion_t;

void calcularFase1(EstadoCohete_t *cohete, Configuracion_t *config);

void calcularFase2(EstadoCohete_t *cohete, Configuracion_t *config);

double calcularAlturaMaxima(EstadoCohete_t *cohete);

double calcularAceleracionMaxima(Configuracion_t *config);

#endif



