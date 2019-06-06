ARMGNU ?= arm-none-eabi

AOPS = --warn --fatal-warnings
CFLAGS = -Wall -Werror -O3  -nostartfiles -ffreestanding

# Habría que inicializar la FPU en vectors.s
#CFLAGS += -march=armv8-a+crc -mtune=cortex-a53 -mfpu=neon-fp-armv8 -mfloat-abi=hard

LDFLAGS =  -lgcc


all : kernel7.img

grabar:
	sudo mount /dev/mmcblk0p1 /mnt/tarjeta
	sudo cp boot/kernel7.img /mnt/tarjeta/kernel7.img
	sync
	sudo umount /dev/mmcblk0p1

clean :
	find . -iname "*.o" -exec rm -f {} \;
	rm -f *.bin
	rm -f *.hex
	rm -f *.elf
	rm -f *.list
	rm -f *.img
	rm -f *.bc

OBJS=main.o BSP/bsp.o BSP/HAL/rpi-gpio.o BSP/HAL/rpi-interrupts.o BSP/HAL/rpi-armtimer.o  BSP/HAL/gpu.o BSP/HAL/mailbox.o

vectors.o : vectors.s
	$(ARMGNU)-as vectors.s -o vectors.o


%.o: %.c
	$(ARMGNU)-gcc $(CFLAGS) -c $< -o $@

hal/%.o: hal/%.c
	$(ARMGNU)-gcc $(CFLAGS) -c $< -o $@

main.elf : memmap vectors.o  $(OBJS)
	$(ARMGNU)-gcc vectors.o $(OBJS) -T memmap -o main.elf $(LDFLAGS) $(CFLAGS)
	$(ARMGNU)-objdump -S -D main.elf > main.list

kernel7.img : main.elf
	$(ARMGNU)-objcopy main.elf -O binary boot/kernel7.img

main.hex : main.elf
	$(ARMGNU)-objcopy main.elf -O ihex main.hex
