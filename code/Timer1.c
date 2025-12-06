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

#define LED_PIN PB4 // Giả sử LED gắn ở chân PB4

// Biến đếm số lần tràn (khai báo volatile vì dùng trong ISR)
volatile uint8_t overflow_count = 0;


ISR(TIMER0_OVF_vect) {
	overflow_count++; // Tăng biến đếm mỗi khi timer tràn 
	
	// Kiểm tra đã đủ 244 lần tràn (tương đương ~4s) chưa
	if (overflow_count >= 244) {
		// Đảo trạng thái LED
		PORTB ^= (1 << LED_PIN);
		// PORTB ^= 0b00000001; // Dạng nhị phân tương đương

		// Reset biến đếm để bắt đầu chu kỳ 1s mới
		overflow_count = 0;
	}
}

int main(void) {
	// Cấu hình chân LED là Output
	DDRB |= (1 << LED_PIN);
	// DDRB |= 0b00000001;

	// Cấu hình Timer0 hoạt động ở Normal Mode
	// TCCR0A = 0 (Normal port operation, WGM01=0, WGM00=0)
	TCCR0A = 0x00;
	// TCCR0A = 0b00000000;

	// Cấu hình Prescaler = 1024
	// Set bit CS02=1 và CS00=1 trong thanh ghi TCCR0B
	TCCR0B |= (1 << CS02) | (1 << CS00);
	// TCCR0B = 0b00000101;

	// Cho phép ngắt tràn Timer0
	// Set bit TOIE0 trong thanh ghi TIMSK0
	TIMSK0 |= (1 << TOIE0);
	// TIMSK0 = 0b00000001;

	// Bật ngắt toàn cục (Global Interrupt)
	sei();

	while (1) {
		// Vòng lặp chính để trống, việc đếm thời gian do ISR đảm nhiệm
	}
}