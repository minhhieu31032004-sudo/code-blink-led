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

#define LED1_PIN PB0
#define LED2_PIN PB1
#define LED3_PIN PB2
#define LED4_PIN PB3

// Bi?n ??m
volatile uint16_t count_led1 = 0;
volatile uint16_t count_led2 = 0;
volatile uint16_t count_led3 = 0;
volatile uint16_t count_led4 = 0;

// ISR ch?y m?i 10ms
ISR(TIMER0_COMPA_vect) {
	count_led1++;
	count_led2++;
	count_led3++;
	count_led4++;

	// LED 1: 100ms (10 l?n 10ms)
	if (count_led1 >= 10) {
		PORTB ^= (1 << LED1_PIN);
		count_led1 = 0;
	}
	// LED 2: 500ms (50 l?n)
	if (count_led2 >= 50) {
		PORTB ^= (1 << LED2_PIN);
		count_led2 = 0;
	}
	// LED 3: 1000ms (100 l?n)
	if (count_led3 >= 100) {
		PORTB ^= (1 << LED3_PIN);
		count_led3 = 0;
	}
	// LED 4: 5000ms (500 l?n)
	if (count_led4 >= 500) {
		PORTB ^= (1 << LED4_PIN);
		count_led4 = 0;
	}
}

int main(void) {
	DDRB |= 0b00001111; //Set 4 chân PB0-PB3 là Output

	//  C?u hình Timer0 CTC 10ms 
	
	// Ch? ?? CTC (WGM01 = 1)
	TCCR0A |= (1 << WGM01);
	
	// Prescaler 1024 (CS02=1, CS00=1)
	TCCR0B |= (1 << CS02) | (1 << CS00);
	
	// Giá tr? so sánh cho 10ms(Prescaler 1024 m?i t?o ???c nh?p 10ms)
	OCR0A = 155;

	// Cho phép ng?t so sánh kênh A (OCIE0A)
	TIMSK0 |= (1 << OCIE0A);

	sei();

	while (1) { }
}