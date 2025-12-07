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

  #include "gpio_init.h" // B?t bu?c ph?i include header c?a chính nó

  void gpio_init(uint8_t port_id, uint8_t pin, uint8_t mode) {
	  // Khai báo con tr? ?? l?u ??a ch? thanh ghi DDR
	  volatile uint8_t *ddr_reg = 0;

	  // Ánh x? t? Tên Port (ID) sang ??a ch? thanh ghi DDR 
	  switch (port_id) {
		  case PORT_B:
		  ddr_reg = &DDRB;
		  break;
		  case PORT_C:
		  ddr_reg = &DDRC;
		  break;
		  case PORT_D:
		  ddr_reg = &DDRD;
		  break;
		  default:
		  return; // N?u tên Port sai thì không làm gì c?
	  }

	  // Th?c hi?n c?u hình bit
	  if (mode == OUTPUT) {
		  // Mu?n là Output: Set bit lên 1
		  *ddr_reg |= (1 << pin);
		  } else {
		  // Mu?n là Input: Clear bit v? 0
		  *ddr_reg &= ~(1 << pin);
	  }
  }