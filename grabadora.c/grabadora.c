#include "include/grabadora.h"
#include <stdio.h>
#include <string.h>

static EstadoGrabadora estado;
static FILE *fp = NULL;

void grabadora_init(void) {
    memset(&estado, 0, sizeof(estado));
    estado.grabando = false;
    estado.pausado = false;
}

bool grabadora_iniciar(const char *nombre) {
    if (estado.grabando) return false;
    char path[300];
    snprintf(path, sizeof(path), "/dev_hdd0/music/%s.wav", nombre);
    fp = fopen(path, "wb");
    if (!fp) return false;
    // Header WAV basico 22050Hz mono 16-bit
    // Se completa al cerrar, por ahora escribimos header vacio
    uint8_t header[44] = {0};
    memcpy(header, "RIFF", 4);
    memcpy(header+8, "WAVEfmt ", 8);
    header[16] = 16; header[20] = 1; header[22] = 1;
    header[24] = (SAMPLE_RATE & 0xFF);
    header[25] = (SAMPLE_RATE >> 8) & 0xFF;
    header[32] = (SAMPLE_RATE * 2) & 0xFF;
    header[33] = ((SAMPLE_RATE * 2) >> 8) & 0xFF;
    header[34] = 2; header[36] = 16;
    memcpy(header+36, "data", 4);
    fwrite(header, 1, 44, fp);
    strncpy(estado.archivo_actual, path, sizeof(estado.archivo_actual)-1);
    estado.grabando = true;
    estado.pausado = false;
    estado.segundos = 0;
    estado.bytes_grabados = 0;
    return true;
}

void grabadora_pausar(void) {
    if (estado.grabando) estado.pausado = true;
}

void grabadora_reanudar(void) {
    if (estado.grabando) estado.pausado = false;
}

void grabadora_detener(void) {
    if (!estado.grabando) return;
    if (fp) fclose(fp);
    fp = NULL;
    estado.grabando = false;
}

void grabadora_procesar_audio(int16_t *buffer, int muestras) {
    if (!estado.grabando || estado.pausado || !fp) return;
    fwrite(buffer, sizeof(int16_t), muestras, fp);
    estado.bytes_grabados += muestras * sizeof(int16_t);
    estado.segundos = estado.bytes_grabados / (SAMPLE_RATE * 2);
}

uint32_t grabadora_get_segundos(void) {
    return estado.segundos;
}

bool grabadora_esta_grabando(void) {
    return estado.grabando && !estado.pausado;
}
