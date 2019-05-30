#include  "bsp.h"
#include  "HAL/rpi-gpio.h"
#include  "HAL/rpi-interrupts.h"
#include  "HAL/rpi-armtimer.h"
#include  "HAL/gpu.h"

gpio_t pines_sw[2];
volatile uint8_t runTime;
uint16_t* screen;

void bsp_init(){
	/*sw*/
	pines_sw[0].func = 0;
	pines_sw[1].func = 0;

	pines_sw[0].num = 26;
	pines_sw[1].num = 20;

	gpio_init(pines_sw[0]);
	gpio_init(pines_sw[1]);

	RPI_ArmTimerInit();
	RPI_Irq_Init();
	screen = gpu_init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP);
}

uint32_t sw_read(sw_t pin){
	return gpio_read(pines_sw[pin]);
}

void delay_us(uint32_t us){
	if (us == 0)
		return;
	runTime = 1;
	RPI_GetArmTimer()->Load = us;
	while(runTime){
	}
}

void set_pixel(uint32_t x, uint32_t y, uint32_t color){
	screen[y*SCREEN_WIDTH+x] = color;
}
