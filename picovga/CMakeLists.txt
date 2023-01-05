cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)
project(picovga)
pico_sdk_init()

add_subdirectory(sdcard_test)
add_subdirectory(lib/fatfs)
add_subdirectory(lib/sdcard)

include_directories(sdcard_test)
include_directories(./lib/fatfs)
include_directories(./lib/sdcard)

add_executable(picovga 
main.c
)

# enable usb output, disable uart output
pico_enable_stdio_usb(picovga 1)
pico_enable_stdio_uart(picovga 1)

set(SD_CS "22" CACHE STRING "Specify the Chip Select GPIO pin for the SD card")
set(SD_SCK "18" CACHE STRING "Specify the Clock GPIO pin for the SD card")
set(SD_MOSI "19" CACHE STRING "Select the Master Out Slave In GPIO pin for the SD card")
set(SD_MISO "20" CACHE STRING "Select the Master In Slave Out GPIO pin for the SD card")

target_compile_definitions(picovga PRIVATE
	SDCARD_PIN_SPI0_CS=${SD_CS}
	SDCARD_PIN_SPI0_SCK=${SD_SCK}
	SDCARD_PIN_SPI0_MOSI=${SD_MOSI}
	SDCARD_PIN_SPI0_MISO=${SD_MISO}
#be aware we also set these within main.h
#curious what overrides what
	SDCARD_PIO=pio1
	SDCARD_PIO_SM=0
)

target_link_libraries(picovga PRIVATE
	sdcard_test
	pico_stdlib
	hardware_spi
	hardware_gpio
	hardware_pio
	sdcard 
	fatfs
)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(picovga)


