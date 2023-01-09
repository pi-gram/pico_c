cmake_minimum_required(VERSION 3.12)

# Pull in PICO SDK (must be before project)
include(pico_sdk_import.cmake)


project(mcume C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the Pico SDK
pico_sdk_init()

add_subdirectory(lib/FatFs_SPI)
add_subdirectory(lib/sdcard)

include_directories(./lib/FatFs_SPI)
include_directories(./lib/sdcard)

include_directories(config)
include_directories(vga_t4)
#include_directories(picovga_t4)
include_directories(tft_t)
include_directories(psram)


set(PICO800_SOURCES 
		pico800/antic.c 
		pico800/atari800.c
		pico800/cpu.c
		pico800/crc32.c
		pico800/gtia.c
		pico800/pia.c
		pico800/pokey.c
		pico800/pokeysnd.c
		pico800/sio.c
		pico800/emuapi.cpp
		pico800/AudioPlaySystem.cpp
		pico800/pico800.cpp
	)


set(PICOSND_SOURCES 
		picosnd/sndplay.cpp
		picosnd/sid.cpp
		picosnd/reSID.cpp
		picosnd/emuapi.cpp
		picosnd/AudioPlaySystem.cpp
		picosnd/picosnd.cpp
	)

set(VGA_T4_SOURCES 
		vga_t4/VGA_t4.cpp
		vga_t4/scanvideo.c
	)

set(PICOVGA_T4_SOURCES 
		picovga_t4/VGA_t4.cpp
		picovga_t4/vga.cpp
		picovga_t4/vga_vmode.cpp
	)

set(PSRAM_SOURCES 
		psram/psram_t.cpp
	)

set(TFT_T_SOURCES 
		tft_t/tft_t_dma.cpp
	)


set(TESTIO_SOURCES 
		testio/testio.cpp
		testio/emuapi.cpp
	)

set(TESTVGA_SOURCES 
		testvga/testvga.cpp
	)

set(TESTKEYMAX_SOURCES 
		testkeymax/testkeymax.cpp
		testkeymax/emuapi.cpp
	)

set(TESTPSRAM_SOURCES 
		testpsram/testpsram.cpp
		testpsram/emuapi.cpp
	)

# Vic20,ZX81,ZX Spectrum,Colem
#add_compile_definitions(OVERRULE_WIDTH=320 OVERRULE_HEIGHT=192)

add_executable(mcume
		${PICO800_SOURCES}
#		${PICOSND_SOURCES}
#		${TESTIO_SOURCES}
#		${TESTVGA_SOURCES}
#		${TESTKEYMAX_SOURCES}
#		${TESTPSRAM_SOURCES}
#		${PSRAM_SOURCES}
		${VGA_T4_SOURCES}
#		${PICOVGA_T4_SOURCES}
#		${TFT_T_SOURCES}
	)

pico_enable_stdio_uart(mcume 1)
pico_enable_stdio_usb(mcume 1)

#uncomment following two and comment one after
pico_generate_pio_header(mcume ${CMAKE_CURRENT_LIST_DIR}/vga_t4/timing.pio)
pico_generate_pio_header(mcume ${CMAKE_CURRENT_LIST_DIR}/vga_t4/scanvideo.pio)
pico_generate_pio_header(mcume ${CMAKE_CURRENT_LIST_DIR}/picovga_t4/picovga.pio)

set(SD_CS "22" CACHE STRING "Specify the Chip Select GPIO pin for the SD card")
set(SD_SCK "5" CACHE STRING "Specify the Clock GPIO pin for the SD card")
set(SD_MOSI "18" CACHE STRING "Select the Master Out Slave In GPIO pin for the SD card")
set(SD_MISO "19" CACHE STRING "Select the Master In Slave Out GPIO pin for the SD card")

target_compile_definitions(mcume PRIVATE
	SDCARD_PIN_SPI0_CS=${SD_CS}
	SDCARD_PIN_SPI0_SCK=${SD_SCK}
	SDCARD_PIN_SPI0_MOSI=${SD_MOSI}
	SDCARD_PIN_SPI0_MISO=${SD_MISO}
	SDCARD_PIO=pio1
	SDCARD_PIO_SM=0
)

add_compile_definitions(mcume PRIVATE
  PICO_SCANVIDEO_PLANE_COUNT=3
  PICO_SCANVIDEO_MAX_SCANLINE_BUFFER2_WORDS=10
  PICO_SCANVIDEO_MAX_SCANLINE_BUFFER3_WORDS=10
)
  
target_link_libraries(mcume PRIVATE
        pico_multicore
	pico_stdlib
	sdcard 
	FatFs_SPI
#        pico_scanvideo_dpi
	hardware_spi
	hardware_gpio
	hardware_pio
        hardware_adc
        hardware_pwm
)


#target_compile_options(mcume PUBLIC -O3)
#target_compile_options(mcume PUBLIC -Wall -Wextra -Wno-unused-function -Wno-unused-parameter)
IF (NOT DEFINED N_SD_CARDS)
    SET(N_SD_CARDS 1)
ENDIF()
target_compile_definitions(mcume PUBLIC N_SD_CARDS=${N_SD_CARDS})

pico_add_extra_outputs(mcume)

