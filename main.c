#include "BSP/bsp.h"

typedef union {
    uint32_t data;
    struct {
        uint8_t B;
        uint8_t G;
        uint8_t R;
    } pixel;
} pixel_t;

int notmain ( void ) {
    pixel_t p;
    bsp_init();

    p.pixel.R = 0;
    p.pixel.G = 0xFF;
    p.pixel.B = 0;

    while(1) {
        for (int y = 0 ; y < SCREEN_HEIGHT ; y++) {
            for( int x = 0 ; x < SCREEN_WIDTH ; x++ ) {
                set_pixel(x,y, p.data );
                p.pixel.R++;
            }
             p.pixel.G++;
        }
         p.pixel.B++;
    }
    return(0);
}
