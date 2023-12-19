/*
 * main.c
 *
 *  Created on: 22 nov. 2023
 *      Author: Naiara Alonso Montes
 */

#include <stdio.h>
#include <sleep.h>

#define BASE_MDM					0x41400000
#define UART_TX_FIFO				0x04
#define UART_STATUS					0x08
#define STATUS_FULL_FIFO_MASK 		0x08

int main (void)
{


	char text[] = "Hola\n";
	int counter = 0;
	volatile int *mdm_tx_fifo = (int*)(BASE_MDM + UART_TX_FIFO); // dir tx
	volatile int *mdm_status = (int*)(BASE_MDM + UART_STATUS); // dir status

	while(1)
	{
		if ((*mdm_status & STATUS_FULL_FIFO_MASK) != 0) // data on the buffer
		{
			usleep(10000); // wait
		} else // data on buffer
		{
			if (counter < 5)
			{
				*mdm_tx_fifo = text[counter];
				counter++;
			}
		}
	}
}


