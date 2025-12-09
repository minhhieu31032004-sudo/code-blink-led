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
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define NUM_LEDS     5
#define CLUSTER_SIZE 3

/* * Thêm t? khóa 'static' ?? báo cho trình biên d?ch bi?t 
 * hàm này ch? dùng n?i b? trong file main.c -> H?t l?i "no previous prototype"
 *
 * Thêm '(void)' vào tham s? -> H?t l?i "declaration isn't a prototype"
 */

static void Clear_All_Leds(void) {
    PORTB &= ~0x1F; 
}

static void Effect_1_SingleChase(void) {
    for (int i = 0; i < NUM_LEDS; i++) {
        PORTB = (1 << i);   
        _delay_ms(1000);     
    }
    Clear_All_Leds();
}

static void Effect_2_ClusterChase(void) {
	
	// ?i?u ki?n d?ng: i <= (5 - 3) t?c là i <= 2
	
    for (int i = 0; i <= (NUM_LEDS - CLUSTER_SIZE); i++) {
		
		// T?o m?t n? bit cho 3 ?èn
		
        uint8_t cluster_mask = (1 << i) | (1 << (i+1)) | (1 << (i+2));
		
        PORTB = cluster_mask;
		
        _delay_ms(1000);
    }
    Clear_All_Leds();
}

int main(void) {
    DDRB |= 0x1F; 
// C?u hình chi?u d? li?u
    while (1) {
        Effect_1_SingleChase();
        _delay_ms(1000);
        Effect_2_ClusterChase();
        _delay_ms(1000);
    }
}