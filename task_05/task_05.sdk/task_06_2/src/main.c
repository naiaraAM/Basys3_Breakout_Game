/*
 * main.c
 *
 *  Created on: 30 nov. 2023
 *      Author: Pablo Goitia Gonzalez	<pgg566@alumnos.unican.es>
 *      		Naiara Alonso Montes 	<nam312@alumnos.unican.es>
 */

#include <stdio.h>
#include <sleep.h>
#include "mb_interface.h"

// Timer control constants
#define TIMER_INT	1
#define INTC_IPR	(*((volatile unsigned long *) (XPAR_INTC_0_BASEADDR + 0x04)))
#define INTC_IER	(*((volatile unsigned long *) (XPAR_INTC_0_BASEADDR + 0x08)))
#define INTC_IAR	(*((volatile unsigned long *) (XPAR_INTC_0_BASEADDR + 0x0C)))
#define INTC_MER	(*((volatile unsigned long *) (XPAR_INTC_0_BASEADDR + 0x1C)))
#define TCSR0		(*((volatile unsigned long *) (XPAR_AXI_TIMER_0_BASEADDR + 0x00)))
#define TLR0		(*((volatile unsigned long *) (XPAR_AXI_TIMER_0_BASEADDR + 0x04)))
#define RST_VALUE	10000	// Equals to 1 ms

// LED's and Buttons control constants
#define MAX_LED 		0x8000
#define BASE_GPIO0 		0x40000000
#define BASE_GPIO1 		0x40010000
#define MASK_BUTTONS	0xF
#define BASE_MDM 		0x41400000
#define OFF_TX_FIFO		0x04
#define OFF_STATUS 		0x08

// Global variables
int tiempo = 0;

// Function definition
void print_button(char button);
void init_timer(void);
void myISR(void) __attribute__ ((interrupt_handler));
void timer_ISR(void);
void msleep(int milisegundos);

int main() {
	init_timer();
	INTC_MER = 0x03; 							// Int Controller Master Enable
	microblaze_enable_interrupts();

	int data;
	int led = MAX_LED;							// Posicion del LED en binario
	volatile int *gpio0 = (int*)BASE_GPIO0;
	volatile int *gpio1 = (int*)BASE_GPIO1;

	gpio1[1] = 0;								// Configurarlo como salida
	gpio0[1] = MASK_BUTTONS; 					// Configurar 4 bits como entrada

	while(1) {
		gpio1[0] = led;

		while((data = gpio0[0] & MASK_BUTTONS) == 0); 				// Espera a que se pulse un boton.
																	// &0xf para quedarnos solo con 4 bits (4 botones)

		if ((data & 0x2) != 0) {									// Botón de mover a la izquierda
			if (led < MAX_LED)
				led <<= 1;
			print_button('i');
		}
		else if ((data & 0x4) != 0) {								// Botón de mover a la derecha
			if (led > 1)
				led >>= 1;
			print_button('d');
		}
		else if ((data & 0x1) != 0) {								// Botón de ir al principio (izquierda)
			led = MAX_LED;
			print_button('p');
		}
		else if ((data & 0x8) != 0) {								// Botón de ir al final (derecha)
			led = 0x1;
			print_button('f');
		}
		while((gpio0[0] & MASK_BUTTONS) != 0) msleep(5000);			// Espera a que se levante un botón, usleep sustituido por msleep
	}
}

/**
 * @brief Sleep miliseconds.
 * @param milisegundos time in ms to sleep
 */
void msleep(int milisegundos) {
	int temp = tiempo;
	while (tiempo != milisegundos + temp);
}

/**
 * @brief Prints a string indicating which buttons has been pressed.
 * @param button char indicating the button
 */
void print_button(char button) {
	volatile int* mdm_status = (int*)(BASE_MDM + OFF_STATUS);
	volatile int* tx_fifo = (int*)(BASE_MDM + OFF_TX_FIFO);
	char str[16] = "Pressed button: ";
	int counter = 0;

	while (1) {								// esto se puede optimizar
		if ((*mdm_status & 0x8) == 0) {		// is not full
			if (counter < 16)
				*tx_fifo = str[counter];
			else if (counter < 17)
				*tx_fifo = button;
			else if (counter < 18)
				*tx_fifo = '\r';
			else
				break;

			counter++;
		}
		else								// is full
			usleep(10000);	// wait for 10 ms
	}
}

/**
 * @brief Timer initialization.
 */
void init_timer() {
	TLR0 = RST_VALUE;
	TCSR0 = 0x20; // Timer Load and Clear any Pending Ints
	TCSR0 = 0xD2; // Timer Clear Load Bit

	// Enable Timer Interrupt in IntC
	INTC_IER = TIMER_INT;
}

/**
 * @brief Interrupt Service Routine.
 */
void myISR()
{
	if (INTC_IPR & TIMER_INT)
		timer_ISR();
}

/**
 * @brief Interrupt Service Routine for the timer.
 */
void timer_ISR()
{
	tiempo++;
	// Acknowledge Interrupt In Timer (Clear pending bit)
	TCSR0 = TCSR0 | 0x100;
}
