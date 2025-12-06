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

// Giá tr? n?p ?? Timer1 tràn sau ?úng 1s (v?i th?ch anh 16MHz, Prescaler 1024)
// 65536 - (16000000/1024) = 49911
#define TCNT1_PRELOAD  49911 // xu?t phát t? 49911 ch?y ??n 65536 

ISR(TIMER1_OVF_vect) {
	// Quan tr?ng: Ph?i n?p l?i giá tr? ngay khi vào ng?t
	TCNT1 = TCNT1_PRELOAD;
	
	// ??o tr?ng thái LED
	PORTB ^= (1 << LED_PIN);
	// PORTB ^= 0b00010000;
}

int main(void) {
	// C?u hình GPIO 
	DDRB |= (1 << LED_PIN);
	// DDRB |= 0b00010000;
	
	// C?u hình Timer1 (Normal Mode, Prescaler 1024)
	TCCR1A = 0;
	
	// Set Prescaler 1024 (CS12=1, CS10=1)
	TCCR1B |= (1 << CS12) | (1 << CS10);
	// TCCR1B = 0b00000101;

	// N?p giá tr? ban ??u 
	// ?? l?n tràn ??u tiên c?ng ?úng là 1s
	TCNT1 = TCNT1_PRELOAD;

	// Cho phép ng?t tràn 
	TIMSK1 |= (1 << TOIE1);
	// TIMSK1 = 0b00000001;

	sei(); // B?t ng?t toàn c?c

	while (1) {
		// CPU không làm vi?c 
	}
}