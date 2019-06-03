#include "BSP/bsp.h"
#include "assets/img.h"

typedef union {
    uint32_t data;
    struct {
        uint8_t B;
        uint8_t G;
        uint8_t R;
        uint8_t dummy;
    } pixel;
} pixel_t;


typedef struct{
    uint16_t x;
    uint16_t y;
    uint16_t ancho;
    uint16_t alto;
    pixel_t color;
} rectangulo_t;

void dibujar_rect(rectangulo_t c);

int notmain ( void ) {
    rectangulo_t c;
    
    bsp_init();


    c.x = 100;
    c.y = 76;
    c.ancho = 300;
    c.alto = 100;
    c.color.pixel.R = 0;
    c.color.pixel.G = 0xff;
    c.color.pixel.B = 0;
    
    while(1) {
        //delay_us(20000);
        dibujar_rect(c);
        c.x++;
        if(c.x > 1024)
            c.x=0;
    }
    return(0);
}


void dibujar_rect(rectangulo_t c){    
        for (int y = c.y ; y < c.y + c.ancho  ; y++) {
            for( int x = c.x ; x < c.x + c.alto  ; x++ ) {
                set_pixel(x,y, c.color.data );
            }
        }
}
