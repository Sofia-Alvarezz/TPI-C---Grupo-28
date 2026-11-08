#include <stdio.h>

int main() {
    int opcion;

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
                printf("Iniciar simulacion\n");
                break;

            case 3:
                printf("Consultar resultados\n");
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