#ifndef __TIMER_H__
#define __TIMER_H__

#include "xparameters.h"

// Timer control constants
#define TIMER_INT	1
#define INTC_IPR	(*((volatile unsigned long *) (XPAR_INTC_0_BASEADDR + 0x04)))
#define INTC_IER	(*((volatile unsigned long *) (XPAR_INTC_0_BASEADDR + 0x08)))
#define INTC_IAR	(*((volatile unsigned long *) (XPAR_INTC_0_BASEADDR + 0x0C)))
#define INTC_MER	(*((volatile unsigned long *) (XPAR_INTC_0_BASEADDR + 0x1C)))
#define TCSR0		(*((volatile unsigned long *) (XPAR_AXI_TIMER_0_BASEADDR + 0x00)))
#define TLR0		(*((volatile unsigned long *) (XPAR_AXI_TIMER_0_BASEADDR + 0x04)))
#define RST_VALUE	100000	// Equals to 1 ms

/**
 * @brief Initializes the timer.
 * 
 * It enables timer interrupts and microblaze interrupt controller (IC).
 */
void init_timer(void);

/**
 * @brief Interrupt Service Routine.
 */
void myISR(void) __attribute__((interrupt_handler));

/**
 * @brief Timer interrupt service routine.
 * 
 * This function is called every time the timer interrupt is triggered. It increments the number 
 * of cycles each time.
 */
void timer_ISR(void);

/**
 * @brief Sleeps for a specified number of milliseconds.
 *
 * Just a spin loop. It uses the global variable to count the number of cycles to wait.
 *
 * @param miliseconds The number of ms to sleep.
 */
void msleep(int miliseconds);

/**
 * @brief Gets the number of cycles.
 *
 * @return The number of cycles.
 */
int get_cycles();

#endif
