#ifndef GRABADORA_H
#define GRABADORA_H

#include <stdint.h>
#include <stdbool.h>

// Configuracion bajo consumo
#define SAMPLE_RATE 22050
#define CANALES 1
#define BITS 16
#define BUFFER_SIZE 4096
#define MAX_GRABACION_MIN 120

typedef struct {
    bool grabando;
    bool pausado;
    uint32_t segundos;
    uint32_t bytes_grabados;
    char archivo_actual[256];
} EstadoGrabadora;

void grabadora_init(void);
bool grabadora_iniciar(const char *nombre);
void grabadora_pausar(void);
void grabadora_reanudar(void);
void grabadora_detener(void);
void grabadora_procesar_audio(int16_t *buffer, int muestras);
uint32_t grabadora_get_segundos(void);
bool grabadora_esta_grabando(void);

#endif
