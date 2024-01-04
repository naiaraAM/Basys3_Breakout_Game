#ifndef __LEDS_H__
#define __LEDS_H__


#define NUM_LEDS        16
#define MAX_LED         0x8000
#define MASK_BUTTONS    0xF

/**
 * @brief Initializes the LEDs.
 */
void init_leds();

/**
 * @brief Blinks the LEDs a specified number of times.
 *
 * @param times The number of times to blink the LEDs.
 */
void led_loop(int times);

#endif
