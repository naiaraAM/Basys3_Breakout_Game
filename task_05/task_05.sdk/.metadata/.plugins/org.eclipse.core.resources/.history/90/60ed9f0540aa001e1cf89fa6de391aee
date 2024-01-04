#include <stdio.h>
#include "mb_interface.h"
#include "timer.h"

int cycles = 0; // global variable to count the number of cycles

void msleep(int miliseconds)
{
	int temp = cycles;
	while (cycles != miliseconds + temp);
}

void init_timer()
{
	TLR0 = RST_VALUE;
	TCSR0 = 0x20; // Timer Load and Clear any Pending Ints
	TCSR0 = 0xD2; // Timer Clear Load Bit

	// Enable Timer Interrupt in IntC
	INTC_IER = TIMER_INT;

	// Int Controller Master Enable
	INTC_MER = 0x03;
	microblaze_enable_interrupts();
}

void myISR()
{
	if (INTC_IPR & TIMER_INT)
		timer_ISR();
}

void timer_ISR()
{
	cycles++;
	// Acknowledge Interrupt In Timer (Clear pending bit)
	TCSR0 = TCSR0 | 0x100;
	INTC_IAR = TIMER_INT;
}

int get_cycles()
{
	return cycles;
}
