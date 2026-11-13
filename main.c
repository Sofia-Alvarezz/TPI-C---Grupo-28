#include <stdio.h>
#include "simulador.h"
#include <math.h>

int main() {
    int opcion;
    EstadoCohete_t cohete;

    Configuracion_t config = {
    ACELERACION_FASE1,
    ACELERACION_FASE2,
    ALTURA_APAGADO
    };

    double alturaMaxima;
    double aceleracionMaxima;
    int simulacionRealizada = 0;
    Simulacion_t historial[MAX_HISTORIAL];
    int cantidadHistorial = 0;
    do {
        printf("\n=== SIMULADOR ARTEMIS SLS ===\n");
        printf("1. Configurar lanzamiento\n");
        printf("2. Iniciar simulacion\n");
        printf("3. Consultar resultados\n");
        printf("4. Ver historial\n");
        printf("0. Salir\n");

        printf("\nIngrese una opcion: ");
        if (scanf("%d", &opcion) != 1) {
         printf("\nError: debe ingresar un numero.\n");
         int caracter;
         while ((caracter = getchar()) != '\n' && caracter != EOF) {
         }
         continue;
        }

        switch (opcion) {
            
            case 1: {
             Configuracion_t nuevaConfig;
             int datosValidos = 1;
             double alturaFase1;

            printf("\n=== CONFIGURAR LANZAMIENTO ===\n");

            printf("Aceleracion primera fase (m/s2): ");
            if (scanf("%lf", &nuevaConfig.aceleracionFase1) != 1) {
             datosValidos = 0;
            }

            if (datosValidos) {
             printf("Aceleracion segunda fase (m/s2): ");
             if (scanf("%lf", &nuevaConfig.aceleracionFase2) != 1) {
              datosValidos = 0;
             }
            }

            if (datosValidos) {
             printf("Altura de apagado (m): ");
             if (scanf("%lf", &nuevaConfig.alturaApagado) != 1) {
              datosValidos = 0;
             }
            }

            if (datosValidos) {
             alturaFase1 = ALTURA_INICIAL + VELOCIDAD_INICIAL * TIEMPO_FASE1 + 0.5 * nuevaConfig.aceleracionFase1 * TIEMPO_FASE1 * TIEMPO_FASE1;
             if (nuevaConfig.aceleracionFase1 > 0 &&
             nuevaConfig.aceleracionFase2 > 0 &&
             nuevaConfig.alturaApagado > alturaFase1 &&
             isfinite(nuevaConfig.aceleracionFase1) &&
             isfinite(nuevaConfig.aceleracionFase2) &&
             isfinite(nuevaConfig.alturaApagado) &&
             isfinite(alturaFase1)) {
             config = nuevaConfig;
             simulacionRealizada = 0;
             printf("\nConfiguracion guardada correctamente.\n");
             } else {
             printf("\nError: los valores no son validos.\n");
             printf("Las aceleraciones deben ser positivas y la altura\n");
             printf("de apagado debe superar la altura de la primera fase.\n");
             }
            } else {
             printf("\nError: debe ingresar valores numericos.\n");
             int caracter;
             while ((caracter = getchar()) != '\n' && caracter != EOF) {
             }
            }
            break;
            }
            
            case 2:
             calcularFase1(&cohete, &config);
             calcularFase2(&cohete, &config);

             alturaMaxima = calcularAlturaMaxima(&cohete);
             aceleracionMaxima = calcularAceleracionMaxima(&config);

             simulacionRealizada = 1;
             guardarEnHistorial(historial, &cantidadHistorial, &config, &cohete,
                                alturaMaxima, aceleracionMaxima);
             printf("\nSimulacion finalizada correctamente.\n");
            break;



            
            case 3:
             if (simulacionRealizada == 1) {
              printf("\n=== RESULTADOS DE LA SIMULACION ===\n");
              printf("Tiempo total de propulsion: %.2f s\n", cohete.tiempo);
              printf("Altura al apagado: %.2f m\n", cohete.altura);
              printf("Velocidad al apagado: %.2f m/s\n", cohete.velocidad);
              printf("Altura maxima: %.2f m\n", alturaMaxima);
              printf("Aceleracion maxima: %.2f g\n", aceleracionMaxima);
              } else {
                 printf("\nPrimero debe realizar una simulacion.\n");
              }
              break;


            case 4:
                mostrarHistorial(historial, cantidadHistorial);
                break;

            case 0:
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opcion incorrecta\n");
        }

    } while (opcion != 0);

    return 0;
}