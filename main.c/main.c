#include "include/grabadora.h"
#include <stdio.h>

int main(void) {
    printf("Grabadora PS3 - Iniciando...\n");
    grabadora_init();

    printf("Grabando... Presiona X para detener\n");
    if (!grabadora_iniciar("grabacion_01")) {
        printf("Error al iniciar grabacion\n");
        return 1;
    }

    int16_t buffer[BUFFER_SIZE];
    for (int i = 0; i < 5 * (SAMPLE_RATE / BUFFER_SIZE); i++) {
        for (int j = 0; j < BUFFER_SIZE; j++) buffer[j] = 0;
        grabadora_procesar_audio(buffer, BUFFER_SIZE);
        printf("Grabando: %u seg\r", grabadora_get_segundos());
    }

    grabadora_detener();
    printf("\nGrabacion guardada!\n");
    return 0;
}
