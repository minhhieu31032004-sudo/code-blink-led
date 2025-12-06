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

// ??nh ngh?a chân LED 
#define LED1_PIN PB0 // 100ms
#define LED2_PIN PB1 // 500ms
#define LED3_PIN PB2 // 1000ms
#define LED4_PIN PB3 // 5000ms

// Bi?n ??m th?i gian (dùng uint16_t vì c?n ??m ??n 500 cho 5s)
volatile uint16_t cnt_100ms = 0;
volatile uint16_t cnt_500ms = 0;
volatile uint16_t cnt_1000ms = 0;
volatile uint16_t cnt_5000ms = 0;

// ISR ch?y m?i 10ms
ISR(TIMER1_COMPA_vect) {
	cnt_100ms++;
	cnt_500ms++;
	cnt_1000ms++;
	cnt_5000ms++;

	// X? lý LED 1 (100ms) - C?n 10 nh?p 10ms
	if (cnt_100ms >= 10) {
		PORTB ^= (1 << LED1_PIN);
		cnt_100ms = 0;
	}

	// X? lý LED 2 (500ms) - C?n 50 nh?p
	if (cnt_500ms >= 50) {
		PORTB ^= (1 << LED2_PIN);
		cnt_500ms = 0;
	}

	// X? lý LED 3 (1000ms) - C?n 100 nh?p
	if (cnt_1000ms >= 100) {
		PORTB ^= (1 << LED3_PIN);
		cnt_1000ms = 0;
	}

	// X? lý LED 4 (5000ms) - C?n 500 nh?p
	if (cnt_5000ms >= 500) {
		PORTB ^= (1 << LED4_PIN);
		cnt_5000ms = 0;
	}
}

int main(void) {
	// C?u hình Output cho 4 LED
	DDRB |= (1<<LED1_PIN)|(1<<LED2_PIN)|(1<<LED3_PIN)|(1<<LED4_PIN);

	// C?u hình Timer1 CTC Mode, chu k? 10ms
	// WGM12 = 1 (Mode 4: CTC)
	TCCR1B |= (1 << WGM12);

	// Prescaler = 64 (CS11 = 1, CS10 = 1)
	TCCR1B |= (1 << CS11) | (1 << CS10);

	// OCR1A = 2499={(TxF)/prescaler}-1,Ch?n prescaler=64 -> T=10ms=0,01s 
	OCR1A = 2499;

	// Cho phép ng?t so sánh kênh A (OCIE1A)
	TIMSK1 |= (1 << OCIE1A);

	sei(); // B?t ng?t toàn c?c

	while (1) {
		// CPU không làm vi?c
	}
}