#include <stdio.h>
#include "simulador.h"
#include "validaciones.h"

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

        /* leerEntero repite la pregunta hasta que se ingrese un numero entre 0 y 4 */
        opcion = leerEntero("\nIngrese una opcion: ", 0, 4);

        switch (opcion) {

            case 1: {
             Configuracion_t nuevaConfig;
             double alturaFase1;

             printf("\n=== CONFIGURAR LANZAMIENTO ===\n");

             /* Las aceleraciones deben ser positivas: entre 0.1 y 100 m/s2 */
             nuevaConfig.aceleracionFase1 = leerDouble("Aceleracion primera fase (m/s2): ", 0.1, 100.0);
             nuevaConfig.aceleracionFase2 = leerDouble("Aceleracion segunda fase (m/s2): ", 0.1, 100.0);

             alturaFase1 = ALTURA_INICIAL + VELOCIDAD_INICIAL * TIEMPO_FASE1 + 0.5 * nuevaConfig.aceleracionFase1 * TIEMPO_FASE1 * TIEMPO_FASE1;

             printf("Al desacople de los SRB la nave estara a %.2f m.\n", alturaFase1);
             printf("La altura de apagado debe ser mayor a ese valor.\n");

             /* La altura de apagado debe superar la altura de la primera fase */
             nuevaConfig.alturaApagado = leerDouble("Altura de apagado (m): ", alturaFase1 + 1.0, 10000000.0);

             config = nuevaConfig;
             simulacionRealizada = 0;
             printf("\nConfiguracion guardada correctamente.\n");
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
             if (leerSiNo("Seguro que desea salir? (s/n): ") == 's') {
              printf("Saliendo del programa...\n");
             } else {
              opcion = -1; /* para que el menu siga */
             }
             break;
        }

    } while (opcion != 0);

    return 0;
}