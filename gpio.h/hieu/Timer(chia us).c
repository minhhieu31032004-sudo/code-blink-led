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

#define LED_PIN PB0 

// Bi?n ??m trong ng?t (volatile ?? tránh l?i t?i ?u hóa)
volatile uint16_t timer_count = 0;

/**
 * Hàm c?u hình Timer1 ch?y CTC Mode theo ??n v? us
 * Th?i gian ng?t mong mu?n (Max ~32000us)
 * Công th?c: Prescaler 8 (0.5us/tick) -> OCR = us * 2 - 1
 */
void Timer1_Config_CTC_us(uint16_t us) {
    // Reset thanh ghi ?i?u khi?n
    TCCR1A = 0;
    TCCR1B = 0;

    // C?u hình CTC Mode (Mode 4: WGM12=1)
    TCCR1B |= (1 << WGM12);
    // TCCR1B |= 0b00001000;

    // C?u hình Prescaler = 8 (CS11=1)
    // T?i 16MHz, Prescaler 8 giúp timer ??m m?i 0.5us
    TCCR1B |= (1 << CS11);
    // TCCR1B |= 0b00000010;

    // Tính toán giá tr? so sánh
    // us = 1000 (1ms) -> OCR = 1000 * 2 - 1 = 1999
    OCR1A = (us * 2) - 1;

    // Cho phép ng?t so sánh kênh A
    TIMSK1 |= (1 << OCIE1A);
    // TIMSK1 |= 0b00000010;
}

ISR(TIMER1_COMPA_vect) {
    timer_count++; // T?ng bi?n count sau m?i chu k? (ví d? 1ms)
    
    //  Mu?n nháy LED m?i 1 giây (1000ms)
    // N?u ta c?u hình Timer ch?y 1000us (1ms), thì c?n ??m 1000 l?n
    if (timer_count >= 1000) {
        PORTB ^= (1 << LED_PIN); // ??o LED
        timer_count = 0;         // Reset bi?n ??m
    }
}

int main(void) {
    // C?u hình chân LED Output
    DDRB |= (1 << LED_PIN);
    
    // C?u hình Timer ng?t m?i 1000us (= 1ms)
    // ?ây là "Base Time" (Th?i gian c? s?)
    Timer1_Config_CTC_us(1000); 

    sei(); // B?t ng?t toàn c?c

    while (1) {
        // CPU k làm vi?c , vi?c ??m n?m hoàn toàn trong ISR
    }
}