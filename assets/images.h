#ifndef __images_h
#define __images_h

#include <stdint.h>

typedef struct{
    uint16_t ancho;
    uint16_t alto;
    const uint32_t *data;
} image_t;

#endif
