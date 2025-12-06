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
#include <avr/interrupt.h>

#define LED_PIN    PB4


ISR(TIMER1_OVF_vect) {
	// Không c?n bi?n ??m if/else gì c? vì b?n thân Timer1 tràn ?ã m?t ~4s r?i
	
	// ??o tr?ng thái LED
	PORTB ^= (1 << LED_PIN);
	// PORTB ^= 0b00010000;
}

int main(void) {
	//  C?u hình GPIO 
	DDRB |= (1 << LED_PIN);
	// DDRB |= 0b00010000;
	
	// C?u hình Timer1 (Normal Mode, Prescaler 1024)
	
	// TCCR1A: Normal Mode (WGM11=0, WGM10=0)
	TCCR1A = 0;
	// TCCR1A = 0b00000000;

	// TCCR1B: Prescaler = 1024
	// V?i Timer1: Bit CS12=1, CS11=0, CS10=1 (Gi?ng Timer0 nh?ng tên bit là CS1x)
	TCCR1B |= (1 << CS12) | (1 << CS10);
	// TCCR1B = 0b00000101;

	// TIMSK1: Cho phép ng?t tràn Timer1 (TOIE1)
	TIMSK1 |= (1 << TOIE1);
	// TIMSK1 = 0b00000001;

	// B?t ng?t toàn c?c 
	sei();

	while (1) {
		// Vòng l?p chính không làm vi?c
	}
}