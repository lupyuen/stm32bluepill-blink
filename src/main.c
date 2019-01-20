/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2009 Uwe Hermann <uwe@hermann-uwe.de>
 * Copyright (C) 2011 Stephen Caudle <scaudle@doceme.com>
 * Copyright (C) 2012 Karl Palsson <karlp@tweak.net.au>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#define RCCLEDPORT (RCC_GPIOC)
#define LEDPORT (GPIOC)
#define LEDPIN (GPIO13)

int bss_var;

int data_var = 123;

static void gpio_setup(void)
{
	/* Enable GPIO clock. */
	/* Using API functions: */
	rcc_periph_clock_enable(RCCLEDPORT);
	/* Set pin to 'output push-pull'. */
	/* Using API functions: */
	gpio_set_mode(LEDPORT, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, LEDPIN);
}

int main(void)
{
	int stack_var = 0;
	int i;
	gpio_setup();
	/* Blink the LED on the board. */
	while (1) {
		/* Using API function gpio_toggle(): */
		gpio_toggle(LEDPORT, LEDPIN);	/* LED on/off */
		for (i = 0; i < 1000000 + bss_var + data_var + stack_var; i++) {	/* Wait a bit. Reference ss_var + data_var + stack_var here so the compiler won't optimised them out */
			__asm__("nop");
		}
	}

	return 0;
}
