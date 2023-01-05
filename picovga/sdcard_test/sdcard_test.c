#include "main.h"

uint8_t counter = 0;
bool sdcard_success = false;
const uint LED_PIN = PICO_DEFAULT_LED_PIN;
static FATFS fs;

bool initSDCard()
{
    FRESULT fr;
    TCHAR str[40];
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
    
    fr = f_chdir("/");
    if (fr != FR_OK)
    {
        printf("SDCARD_TEST.C: Cannot change dir to / : %d\n", fr);
        return false;
    }
    // for f_getcwd to work, set
    //   #define FF_FS_RPATH		2
    // in drivers/fatfs/ffconf.h
    fr = f_getcwd(str, sizeof(str));
    if (fr != FR_OK)
    {
        printf("SDCARD_TEST.C: Cannot get current dir: %d\n", fr);
        return false;
    }
    printf("SDCARD_TEST.C: Current directory is: %s\n", str);

    return true;
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
SDCARD_TEST.C: SDCARD_SPI_BUS=1073987584
SDCARD_TEST.C: SDCARD_PIN_SPI0_CS=22
SDCARD_TEST.C: SDCARD_PIN_SPI0_SCK=18
SDCARD_TEST.C: SDCARD_PIN_SPI0_MOSI=19
SDCARD_TEST.C: SDCARD_PIN_SPI0_MISO=20
SDCARD_TEST.C: SDCARD_PIO=1344274432
SDCARD_TEST.C: SDCARD_PIO_SM=0
SDCARD_TEST.C: Let's try to mount the SDcard
FF.C: inside f_mount about to call mount_volume
FF.C: about to call disk_initialize from within mount_volume
SDCARD.C: about to call init_spi() here, I think I was called by FF.C: mount_volume
SDCARD.C: we should be executing the PIO code here
SDCARD_TEST.C: SD card mount error: 3
SDCARD_TEST.C: sdcard_success=0
SDCARD_TEST.C: Bugger an error happened...again..
*/

}

