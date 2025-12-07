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

  #include "gpio_write.h" // Header c?a file này
 
  void gpio_write(uint8_t port_id, uint8_t pin, uint8_t level) {
	  // Khai báo con tr? ?? l?u ??a ch? thanh ghi PORT
	  volatile uint8_t *port_reg = 0;

	  // Ánh x? t? Tên Port (ID) sang ??a ch? thanh ghi PORT 
	  switch (port_id) {
		  case PORT_B:
		  port_reg = &PORTB;
		  break;
		  case PORT_C:
		  port_reg = &PORTC;
		  break;
		  case PORT_D:
		  port_reg = &PORTD;
		  break;
		  default:
		  return;
	  }

	  // Th?c hi?n ghi m?c logic
	  if (level == HIGH) {
		  // Xu?t m?c cao (5V): Set bit lên 1
		  *port_reg |= (1 << pin);
		  } else {
		  // Xu?t m?c th?p (0V): Clear bit v? 0
		  *port_reg &= ~(1 << pin);
	  }
  }