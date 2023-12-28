#include <stdio.h>
#include "mb_interface.h"
#include "timer.h"

// Global variables
int tiempo = 0;

/**
 * @brief Sleep miliseconds.
 * @param milisegundos time in ms to sleep
 */
void msleep(int milisegundos) {
	int temp = tiempo;
	while (tiempo <= milisegundos + temp);
	tiempo = 0;
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

	// Int Controller Master Enable
	INTC_MER = 0x03;
	microblaze_enable_interrupts();
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
	INTC_IAR = TIMER_INT;
}
