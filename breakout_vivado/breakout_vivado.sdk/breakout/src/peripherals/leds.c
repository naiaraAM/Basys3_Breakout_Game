#include <stdio.h>
#include "xparameters.h"
#include "leds.h"
#include "timer.h"

volatile int *gpio1 = (int *)XPAR_AXI_GPIO_1_BASEADDR;

void init_leds()
{
	gpio1[1] = 0; // Configurarlo como salida
}

void led_loop(int times)
{
	int led = 0b1; // Posicion del LED en binario

	for (int t = 0; t < times; t++)
	{
		for (int l = 0; l < NUM_LEDS; l++)
		{
			gpio1[0] = led;
			led <<= 1;
			msleep(10);
		}
		for (int l = 0; l < NUM_LEDS; l++)
		{
			led >>= 1;
			gpio1[0] = led;
			msleep(10);
		}
		gpio1[0] = 0;
	}
}
