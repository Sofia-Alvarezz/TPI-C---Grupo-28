#include <stdio.h>
#include "simulador.h"

int main() {
    int opcion;
    EstadoCohete_t cohete;
    double alturaMaxima;
    double aceleracionMaxima;
    int simulacionRealizada = 0;

    do {
        printf("\n=== SIMULADOR ARTEMIS SLS ===\n");
        printf("1. Configurar lanzamiento\n");
        printf("2. Iniciar simulacion\n");
        printf("3. Consultar resultados\n");
        printf("4. Ver historial\n");
        printf("0. Salir\n");

        printf("\nIngrese una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
             printf("Configurar lanzamiento\n");
             break;

            
            case 2:
             calcularFase1(&cohete);
             calcularFase2(&cohete);

             alturaMaxima = calcularAlturaMaxima(&cohete);
             aceleracionMaxima = calcularAceleracionMaxima();

             simulacionRealizada = 1;

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
                printf("Ver historial\n");
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