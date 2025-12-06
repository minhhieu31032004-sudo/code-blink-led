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


#define LED_PIN    PB4  // LED PB4 (chân s? 12 trên m?ch )

// Bi?n ??m s? l?n tràn
volatile uint8_t timer0_overflow_count = 0;

// ISR cho Timer0 Overflow (x?y ra m?i ~16.384ms)
ISR(TIMER0_OVF_vect) {
	timer0_overflow_count++;
	
	// 61 l?n tràn * 16.384ms ~= 1000ms (1s)
	if (timer0_overflow_count >= 61) {
		
		// ??o tr?ng thái LED t?i chân PB4
		PORTB ^= (1 << LED_PIN);
		// PORTB ^= 0b00010000; // bit th? 4 ???c b?t lên (tính t? 0)
		
		timer0_overflow_count = 0; // Reset bi?n ??m
	}
}

int main(void) {
	
	// Set PB4 là Output
	DDRB |= (1 << LED_PIN);
	// DDRB |= 0b00010000 Bit 4 lên 1
	
	// C?u hình Timer0 (Normal Mode, Prescaler 1024) 
	// TCCR0A: Normal Mode
	TCCR0A = 0;
	// TCCR0A = 0b00000000;

	// TCCR0B Prescaler = 1024 (CS02=1, CS00=1)
	TCCR0B |= (1 << CS02) | (1 << CS00);
	// TCCR0B = 0b00000101;

	// TIMSK0 Cho phép ng?t tràn
	TIMSK0 |= (1 << TOIE0);
	// TIMSK0 = 0b00000001;

	// B?t ng?t toàn c?c 
	sei();

	while (1) {
		// CPU không làm vi?c ch? ng?t
	}
}