#ifndef _SDCARD_H_
#define _SDCARD_H_

/* SPI pin assignment */

/* Pico Wireless */
#ifndef SDCARD_SPI_BUS
#define SDCARD_SPI_BUS spi1
#endif

#ifndef SDCARD_PIN_SPI0_CS
#define SDCARD_PIN_SPI0_CS     22
#endif

#ifndef SDCARD_PIN_SPI0_SCK
#define SDCARD_PIN_SPI0_SCK    5
#endif

#ifndef SDCARD_PIN_SPI0_MOSI
#define SDCARD_PIN_SPI0_MOSI   18
#endif

#ifndef SDCARD_PIN_SPI0_MISO 
#define SDCARD_PIN_SPI0_MISO   19
#endif

#endif // _SDCARD_H_
