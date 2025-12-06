/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

//Ng?t INT0 (PD2) x?y ra ? ??o LED PD4
ISR(INT0_vect)
{
	PORTD ^= (1 << PORTD4);
}

int main(void)
{
	// PD2 (INT0) là input + b?t pull-up
	DDRD &= ~(1 << DDD2);

	PORTD |= (1 << PORTD2);

	// PD4 là output ?i?u khi?n LED
	DDRD |= (1 << DDD4);

	// Cau hinh ngat ngoai INT0 canh xuong
	EICRA |= (1 << ISC01);   // ISC01=1, ISC00=0 ? Kích ho?t xung c?nh xu?ng
	EIMSK |= (1 << INT0);    // Cho phép INT0,INT1 gi?ng nh? m?t công t?c b?t ng?t
	sei();                   // Hàm interrupt cho phép ng?t toàn c?c

	while(1)
	{
		// Không c?n code trong while, LED s? nh?p khi b?m nút
	}
}