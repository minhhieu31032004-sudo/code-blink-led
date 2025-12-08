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
/*
 * timer.c
 */ 
#include "timer.h"

// Bi?n toàn c?c module (static ?? che gi?u kh?i các file khác)
static volatile uint32_t _timer1_overflow_count = 0; // ??m s? l?n ng?t
static uint16_t _timer1_top_value = 0;              // L?u giá tr? OCR1A ?? tính toán
static uint32_t _last_total_ticks = 0;              // L?u m?c th?i gian l?n ?o tr??c

/*
  Vi?t l?i hàm c?u hình t? bài c?
 */
void Timer1_Config_CTC_us(uint16_t us) {
    // T?t ng?t toàn c?c ?? c?u hình an toàn
    cli();

    TCCR1A = 0;
    TCCR1B = 0;
    
    // Mode 4: CTC (WGM12 = 1)
    TCCR1B |= (1 << WGM12);
    
    // Prescaler = 8 (CS11 = 1) -> 0.5us per tick (v?i th?ch anh 16MHz)
    TCCR1B |= (1 << CS11);
    
    // Tính toán OCR1A: us * 2 - 1
    _timer1_top_value = (us * 2) - 1;
    OCR1A = _timer1_top_value;
    
    // Reset b? ??m
    TCNT1 = 0;
    _timer1_overflow_count = 0;
    _last_total_ticks = 0;

    // Cho phép ng?t so sánh kênh A
    TIMSK1 |= (1 << OCIE1A);

    sei(); // B?t l?i ng?t toàn c?c
}

/*
  ISR: X? lý ng?t khi Timer ??m ?? s? us cài ??t
 */
ISR(TIMER1_COMPA_vect) {
    _timer1_overflow_count++;
}

/*
   Tr? v? s? l?n Timer1 ?ã overflow (s? l?n ng?t)
 */
uint32_t Timer1_Get_Overflow_Count(void) {
    uint32_t count;
    
    // ATOMIC ACCESS: T?t ng?t khi ??c bi?n volatile nhi?u byte
    // ?? tránh ng?t x?y ra gi?a ch?ng làm sai l?ch d? li?u
    uint8_t sreg = SREG; // L?u tr?ng thái ng?t hi?n t?i
    cli();               // T?t ng?t
    
    count = _timer1_overflow_count;
    
    SREG = sreg;         // Khôi ph?c tr?ng thái ng?t
    return count;
}

/*
  Tính s? xung trôi qua k? t? l?n ?o tr??c
  Logic: T?ng xung = (S? l?n tràn * Giá tr? Max 1 chu k?) + Giá tr? hi?n t?i TCNT1
 */
uint32_t Timer1_Get_Delta_Ticks(void) {
    uint32_t current_total_ticks;
    uint32_t delta;
    
    uint8_t sreg = SREG;
    cli(); // B?t ??u ?o?n Atomic
    
    // Tính t?ng s? xung tính t? lúc kh?i ??ng
    // M?i l?n tràn là (_timer1_top_value + 1) xung
    current_total_ticks = (_timer1_overflow_count * (_timer1_top_value + 1)) + TCNT1;
    
    SREG = sreg; // K?t thúc ?o?n Atomic

    // Tính kho?ng chênh l?ch so v?i l?n ?o tr??c
    if (current_total_ticks >= _last_total_ticks) {
        delta = current_total_ticks - _last_total_ticks;
    } else {
        // Tr??ng h?p bi?n 32bit b? tràn 
        delta = (UINT32_MAX - _last_total_ticks) + current_total_ticks + 1;
    }

    // C?p nh?t m?c th?i gian m?i
    _last_total_ticks = current_total_ticks;

    return delta;
}