#include "main.h"

uint8_t counter = 0;
bool sdcard_success = false;
const uint LED_PIN = PICO_DEFAULT_LED_PIN;
static FATFS fs;
FILINFO MyFileInfo;
DIR MyDirectory;
FIL MyFile;

static TCHAR str[40];

bool initSDCard()
{

    FRESULT fr;
    sleep_ms(1000);

    printf("SDCARD_TEST.C: Let's try to mount the SDcard\n");
    //I believe this next command calls FF.c: f_mount()
    //and internally that calls FF.c: mount_volume
    //and internally that calls SDCARD.C: disk_initialize
    //and internally that does the PIO calls to init the SDCard
    //
    fr = f_mount(&fs, "", 1);
    if (fr != FR_OK)
    {
        printf("SDCARD_TEST.C: SD card mount error: %d\n", fr);
        return false;
    }
    printf("SDCARD_TEST.C: Mounted OKAY!\n");
    
    return true;
}

void PrintDirFiles(void)
{
    uint32_t numFiles = 0x00;
    numFiles = Storage_DirFileList("/");
    printf("successfully listed files in the root folder:%d\n",numFiles);
    if(numFiles>1) {
        numFiles = Storage_DirFileList("/800");
        printf("successfully listed files in the /800 folder:%d\n",numFiles);    
    }
    fflush(stdout);
}

uint32_t Storage_DirFileList(const char* DirName)
{
    uint32_t i = 0, j = 0;
    FRESULT res;
    sleep_ms(1000);
    
    printf("The DirName to look through is: %s\n", DirName);

    res = f_opendir(&MyDirectory, DirName);
    if(res == FR_OK){
        i = strlen(DirName);
	for (;;){
	    res = f_readdir(&MyDirectory, &MyFileInfo);
	    if(res != FR_OK || MyFileInfo.fname[0] == 0) break;
            if(MyFileInfo.fname[0] == '.') continue;
	    if(!(MyFileInfo.fattrib & AM_DIR)){
	        do{
		    i++;
		}while (MyFileInfo.fname[i] != 0x2E);
		if(j < 255){ //just limit it to 255
		     printf("%s\n",MyFileInfo.fname);
		     j++;
		}
	    }
	    i = 0;
        }
    }
    return j;
}


uint8_t system_init(void)
{    
    stdio_init_all();
    
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    return 0;
}


int sdcard_test(void)
{
    counter = system_init();

    //flash 2 times 5 seconds gap
    gpio_put(LED_PIN, 1);
    sleep_ms(1000);
    gpio_put(LED_PIN, 0);
    sleep_ms(5000);
    gpio_put(LED_PIN, 1);
    sleep_ms(1000);
    gpio_put(LED_PIN, 0);

    printf("SDCARD_TEST.C: system init response=%d\n",counter);
    printf("SDCARD_TEST.C: SDCARD_SPI_BUS=%d\n",SDCARD_SPI_BUS);
    printf("SDCARD_TEST.C: SDCARD_PIN_SPI0_CS=%d\n",SDCARD_PIN_SPI0_CS);
    printf("SDCARD_TEST.C: SDCARD_PIN_SPI0_SCK=%d\n",SDCARD_PIN_SPI0_SCK);
    printf("SDCARD_TEST.C: SDCARD_PIN_SPI0_MOSI=%d\n",SDCARD_PIN_SPI0_MOSI);
    printf("SDCARD_TEST.C: SDCARD_PIN_SPI0_MISO=%d\n",SDCARD_PIN_SPI0_MISO);
    printf("SDCARD_TEST.C: SDCARD_PIO=%d\n",SDCARD_PIO);
    printf("SDCARD_TEST.C: SDCARD_PIO_SM=%d\n",SDCARD_PIO_SM);
  
    sdcard_success = initSDCard();  
    printf("SDCARD_TEST.C: sdcard_success=%d\n",sdcard_success);
    if(!sdcard_success) {
        printf("SDCARD_TEST.C: Bugger an error happened...again..\n");
    } else {
        printf("SDCARD_TEST.C: Woo!hoo! party time\n");
    }

    if(sdcard_success) {
        PrintDirFiles();
    }
    
    //flash 3 times 3 seconds gap
    gpio_put(LED_PIN, 1);
    sleep_ms(1000);
    gpio_put(LED_PIN, 0);
    sleep_ms(3000);
    gpio_put(LED_PIN, 1);
    sleep_ms(1000);
    gpio_put(LED_PIN, 0);
    sleep_ms(3000);
    gpio_put(LED_PIN, 1);
    sleep_ms(1000);
    gpio_put(LED_PIN, 0);


    return 0;

/*
DEBUG OUTPUT:

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

*/

}

