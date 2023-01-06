#ifndef __MAIN_H
#define __MAIN_H

#include <pico/stdlib.h>
#include "hardware/spi.h"
#include "hardware/gpio.h"
#include "hardware/pio.h"
#include "stdio.h"
#include "ff.h"
#include "sdcard.h"
#include <string.h>

#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

#define SDCARD_SPI_BUS 		spi1
#define SDCARD_PIN_SPI0_CS     	22
#define SDCARD_PIN_SPI0_SCK    	5
#define SDCARD_PIN_SPI0_MOSI   	18
#define SDCARD_PIN_SPI0_MISO   	19

#define SDCARD_PIO		pio1
#define SDCARD_PIO_SM		0

void PrintDirFiles(void);
uint32_t Storage_DirFileList(const char* DirName);
uint8_t system_init(void);
int sdcard_test(void);

#endif
