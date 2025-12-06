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
// [Ph?n này b? khu?t trong ?nh, c?n thêm vào ?? ch?y ???c]
// #include <avr/io.h>
// #include <avr/interrupt.h>
// volatile uint16_t cnt = 0;

ISR(TIMER0_COMPA_vect)
{
	cnt++;

	// MU?N CHU KÌ 1s -> ??O TR?NG THÁI M?I 0,5s
	// T?N S? NG?T 2000Hz (0.5ms M?T L?N )
	// C?N ??M 1000 L?N ?? ???C 0.5s (1000 * 0.5ms = 500ms = 0.5s)
	if(cnt >= 1000)
	{
		PORTD ^= (1 << PORTD4); // ??O TR?NG THÁI ? PD4
		cnt = 0;                // Reset BI?N ??M
	}
}

void start_up()
{
	// Set Timer0 ch? ?? CTC (WGM01 = 1)
	// Set OC0A (PD6) ??o tr?ng thái khi so sánh  (COM0A0 = 1)
	// Set OC0B (PD5) ??o tr?ng thái khi so sánh  (COM0B0 = 1)
	TCCR0A = (1 << WGM01) | (1 << COM0A0) | (1 << COM0B0);

	// Set Prescaler = 64
	TCCR0B = (1 << CS01) | (1 << CS00);

	// Set giá tr? so sánh
	OCR0A = 124; // T?o ra t?n s? ng?t 2kHz

	OCR0B = 0;

	// Cho phép ng?t Timer0 Compare Match A
	TIMSK0 |= (1 << OCIE0A);

	// C?u hình Output
	DDRD |= (1 << DDD6); // Output cho OC0A
	DDRD |= (1 << DDD5); // Output cho OC0B

	// Set PD4 la Output LED Blink
	DDRD |= (1 << DDD4);

	// B?t ng?t toàn c?c
	sei();
}

int main(void)
{
	start_up();

	while(1)
	{
		// Blink LED X? LÍ TRONG TIMER NG?T
		// SÓNG 1KHZ ???C X? LÍ B?I PH?N C?NG (Timer Hardware)
	}
}
