#ifndef __MAIN_H
#define __MAIN_H

#include <pico/stdlib.h>
#include "hardware/spi.h"
#include "hardware/gpio.h"
#include "hardware/pio.h"
#include "stdio.h"
#include "ff.h"
#include "sdcard.h"

#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

#define SDCARD_SPI_BUS 		spi1
#define SDCARD_PIN_SPI0_CS     	22
#define SDCARD_PIN_SPI0_SCK    	18
#define SDCARD_PIN_SPI0_MOSI   	19
#define SDCARD_PIN_SPI0_MISO   	20

#define SDCARD_PIO		pio1
#define SDCARD_PIO_SM		0

//I thought it could be as simple as:
//spi1 should be spi0
//pio1 should be pio0
//not so :-(

uint8_t system_init(void);
int sdcard_test(void);

#endif
