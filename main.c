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


typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t ancho;
    uint16_t alto;
    pixel_t color;
} rectangulo_t;

void dibujar_rect(rectangulo_t c);
void borrar_rect(rectangulo_t c);
void dibujar_img(image_t i, uint32_t mascara, uint16_t x, uint16_t y);
int notmain ( void ) {
    rectangulo_t pantalla;

    bsp_init();

    pantalla.x = 0;
    pantalla.y = 0;
    pantalla.ancho = 1024;
    pantalla.alto = 768;


    borrar_rect(pantalla);

    int x=(1024-480)/2;
    int y=(768-480)/2;

    int vel_x=3;
    int vel_y=3;


    pantalla.ancho = smile_img.alto;
    pantalla.alto = smile_img.ancho;
    while(1) {
        pantalla.x = x;
        pantalla.y = y;
        borrar_rect(pantalla);

        if(sw_read(sw_a) != 0)
            x+=vel_x;
        else
            x-=vel_x;

        if(sw_read(sw_b) != 0)
            y+=vel_y;
        else
            y-=vel_y;

        if(x < -1*smile_img.ancho)
            x = 1024;
        else if (x> 1024) {
            x =-1*smile_img.ancho;
        }

        if(y < -1*smile_img.alto)
            y= 768;
        else if (x> 768) {
            y =-1*smile_img.alto;
        }




        dibujar_img(smile_img, 0x00000000, x, y);
        delay_us(20000);
    }
    return(0);
}


void dibujar_rect(rectangulo_t c) {
    for (int y = c.y ; y < c.y + c.alto  ; y++) {
        for( int x = c.x ; x < c.x + c.ancho  ; x++ ) {
            set_pixel(x,y, c.color.data );
        }
    }
}

void borrar_rect(rectangulo_t c) {
    for (int y = c.y ; y < c.y + c.alto  ; y++) {
        for( int x = c.x ; x < c.x + c.ancho  ; x++ ) {
            set_pixel(x,y, 0xffffff );
        }
    }
}


void dibujar_img(image_t i, uint32_t mascara, uint16_t pos_x, uint16_t pos_y) {
    for (int y = 0 ; y < i.alto  ; y++) {
        for( int x = 0 ; x < i.ancho  ; x++ ) {
            if(mascara != i.data[y*i.ancho + x])
                set_pixel( x + pos_x, y + pos_y, i.data[y*i.ancho + x]);
        }
    }
}
