#include <stdint.h>
#define SCREEN_WIDTH    1024
#define SCREEN_HEIGHT   768
#define SCREEN_BPP      32

typedef enum {
	sw_a,
	sw_b
} sw_t;

void bsp_init();
uint32_t sw_read(sw_t pin);
uint32_t strafing(sw_t sw[2]);
void delay_us(uint32_t us);
void set_pixel(uint32_t x, uint32_t y, uint32_t color);
