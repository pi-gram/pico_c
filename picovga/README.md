# pico_vga

This was an experiment to access the SD-Card on the pico demo VGA board.

The key is to use the correct GPIO setting values AND to use the PIO code that overrides the SPI access layer.

The following is a DEBUG output of accessing a FAT formatted SD-Card:

SDCARD_TEST.C: system init response=0
SDCARD_TEST.C: SDCARD_SPI_BUS=1074003968
SDCARD_TEST.C: SDCARD_PIN_SPI0_CS=22
SDCARD_TEST.C: SDCARD_PIN_SPI0_SCK=5
SDCARD_TEST.C: SDCARD_PIN_SPI0_MOSI=18
SDCARD_TEST.C: SDCARD_PIN_SPI0_MISO=19
SDCARD_TEST.C: SDCARD_PIO=1345323008
SDCARD_TEST.C: SDCARD_PIO_SM=0
SDCARD_TEST.C: Let's try to mount the SDcard
FF.C: inside f_mount about to call mount_volume
FF.C: about to call disk_initialize from within mount_volume
SDCARD.C: about to call init_spi() here, I think I was called by FF.C: mount_volume
SDCARD.C: we should be executing the PIO code here
SDCARD.C: pio_spi_init executed
SDCARD_TEST.C: Mounted OKAY!
SDCARD_TEST.C: sdcard_success=1
SDCARD_TEST.C: Woo!hoo! party time
The DirName to look through is: /
flower.bmp
test.txt
cal.cfg
successfully listed files in the root folder:3
The DirName to look through is: /800
3-D Tic-Tac-Toe.rom
Abracadabra.rom
Alf in the Color Caves.rom
Alien Ambush.rom
Alien Garden.rom
ataribas.rom
atariosb.rom
atarixl.rom
successfully listed files in the /800 folder:8


As pre-built .uf2 file is included using the settings as defined in the DEBUG output above.

To use, open a Terminator window and split horizontally
[1]
mkdir build
cd build
cmake -D"PICO_BOARD=vgaboard" ..
make
[2]
tio -m ODELBS /dev/ttyACM0

Turn on PICO and hold BOOTSEL, listen for the be-boop noise
Drag the pciovga.uf2 file onto the newly attached device
It will auto disconnect and then reconnect and you will see the DEBUG output in the tio window.

