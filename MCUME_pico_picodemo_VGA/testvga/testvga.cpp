#include "pico.h"
#include "pico/stdlib.h"

#include "vga_t_dma.h"

#include <stdio.h>
#include <stdio.h>

TFT_T_DMA vga;

#define BLUE       VGA_RGB(0, 0, 170)
#define LIGHT_BLUE VGA_RGB(0, 136, 255)
#define RED        VGA_RGB(255, 0, 0)
#define GREEN      VGA_RGB(0, 255, 0)

static int fb_width, fb_height;

static char * digits = "0123456789";
const uint LED_PIN = PICO_DEFAULT_LED_PIN;

#include "hardware/clocks.h"
#include "hardware/vreg.h"

static uint8_t pix = 0;
int main(void) {
//    vreg_set_voltage(VREG_VOLTAGE_1_05);
//    set_sys_clock_khz(125000, true);    
//    set_sys_clock_khz(150000, true);    
//    set_sys_clock_khz(133000, true);    
//    set_sys_clock_khz(200000, true);    
//    set_sys_clock_khz(210000, true);    
    set_sys_clock_khz(230000, true);    
//    set_sys_clock_khz(225000, true);    
//    set_sys_clock_khz(250000, true);  
    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    //flash 2 times 5 seconds gap
    gpio_put(LED_PIN, 1);
    sleep_ms(1000);
    gpio_put(LED_PIN, 0);
    sleep_ms(5000);
    gpio_put(LED_PIN, 1);
    sleep_ms(1000);
    gpio_put(LED_PIN, 0);
    
    printf("TESTVGA.CPP: start\n");   

//    vga.begin(VGA_MODE_400x240);
    vga.begin(VGA_MODE_320x240);
    //tft.fillScreenNoDma( RGBVAL16(0xff,0x00,0x00) );
//	vga.clear(LIGHT_BLUE); //background colour
//	vga.clear(GREEN); //background colour
	vga.clear(RED); //background colour

	vga.get_frame_buffer_size(&fb_width, &fb_height);
//	vga.drawRect((fb_width-320)/2,(fb_height-200)/2, 320,200, BLUE);
//	vga.drawRect((fb_width-320)/2,(fb_height-200)/2, 320,200, GREEN);
	vga.drawRect((fb_width-320)/2,(fb_height-200)/2, 320,200, RED);
//	vga.drawText((fb_width-320)/2,(fb_height-200)/2+1*8,"    ***** PI-GRAM 64 BASIC V2 *****    ",LIGHT_BLUE, BLUE,false);
//	vga.drawText((fb_width-320)/2,(fb_height-200)/2+1*8,"    ***** PI-GRAM 64 BASIC V2 *****    ",LIGHT_BLUE, GREEN,false);
	vga.drawText((fb_width-320)/2,(fb_height-200)/2+1*8,"    ***** PI-GRAM 64 BASIC V2 *****    ",LIGHT_BLUE, RED,false);
//	vga.drawText((fb_width-320)/2,(fb_height-200)/2+3*8," 64K RAM SYSTEM  38911 BASIC BYTES FREE",LIGHT_BLUE, BLUE,false);
//	vga.drawText((fb_width-320)/2,(fb_height-200)/2+3*8," 64K RAM SYSTEM  38911 BASIC BYTES FREE",LIGHT_BLUE, GREEN,false);
	vga.drawText((fb_width-320)/2,(fb_height-200)/2+3*8," 64K RAM SYSTEM  38911 BASIC BYTES FREE",LIGHT_BLUE, RED,false);
//	vga.drawText((fb_width-320)/2,(fb_height-200)/2+5*8,"READY.",LIGHT_BLUE,BLUE,false);
//	vga.drawText((fb_width-320)/2,(fb_height-200)/2+5*8,"READY.",LIGHT_BLUE,GREEN,false);
	vga.drawText((fb_width-320)/2,(fb_height-200)/2+5*8,"READY.",LIGHT_BLUE,RED,false);

	uint newclock = clock_get_hz(clk_sys)/1000000;
	
    char buf[4] = {32,32,32,0};
	uint r1 = newclock/100;
	uint r = newclock - r1*100;
	uint r2 = r/10;
	r = newclock - r1*100 - r2*10;
	uint r3 = r;
	buf[0] = digits[r1]; //2    2
	buf[1] = digits[r2]; //4    3
	buf[2] = digits[r3]; //0    0
    printf("TESTVGA.CPP: buf: %s\n", buf);
//    vga.drawText(4*8,8,buf,BLUE,LIGHT_BLUE,false);
//    vga.drawText(4*8,8,buf,GREEN,LIGHT_BLUE,false);
    vga.drawText(4*8,8,buf,RED,LIGHT_BLUE,false);

    while (true) {
        //tft.fillScreenNoDma( pix++ );
        vga.waitSync();
	vga.drawText((fb_width-320)/2,(fb_height-200)/2+6*8," ",BLUE,LIGHT_BLUE,false);
	sleep_ms(500);
	//vga.waitSync();
	vga.drawText((fb_width-320)/2,(fb_height-200)/2+6*8," ",BLUE,BLUE,false);
	sleep_ms(500);
	//vga.waitSync();

//	printf("TESTVGA.CPP: x\n");  
    }
}

/*
USING picovga_t4 lib:
[tio 21:58:28] Disconnected
[tio 22:23:07] Connected
TESTVGA.CPP: start
VGA_t4.cpp: executing begin
VGA_t4.cpp: about to init the vmode
VGA_t4.cpp: vmode = 536876372
VGA_t4.cpp: now we call VgaInitReql() inside vga.cpp
VGA.CPP: about to VgaInit
VGA.CPP: about to VgaTerm
VGA.CPP: about to VgaPioInit
VGA.CPP: about to init GPIO pins
VGA.CPP: initialised GPIO: 0
VGA.CPP: initialised GPIO: 1
VGA.CPP: initialised GPIO: 2
VGA.CPP: initialised GPIO: 3
VGA.CPP: initialised GPIO: 4
VGA.CPP: initialised GPIO: 5
VGA.CPP: initialised GPIO: 6
VGA.CPP: initialised GPIO: 7
VGA.CPP: initialised GPIO: 8
VGA.CPP: initialised GPIO: 9
VGA.CPP: initialised GPIO: 10
VGA.CPP: initialised GPIO: 11
VGA.CPP: initialised GPIO: 12
VGA.CPP: initialised GPIO: 13
VGA.CPP: initialised GPIO: 14
VGA.CPP: initialised GPIO: 15
VGA.CPP: about to init VGA_GPIO_SYNC 16
VGA.CPP: about to sm_config_set_out_pins: 0 15
VGA.CPP: should have finished the VGAPioInit
VGA.CPP: about to VgaBufInit
VGA.CPP: about to VgaDmaInit
width=320 height=240 wfull=339 wmax=339
freq=240000 vco=1440000 fbdiv=120 pd1=6 pd2=1
htot=3813 hfront=161 hsync=458 hback=314
vtot=525 vmax=480
TESTVGA.CPP: x

*/
/*
USING vga_t4 lib:
[tio 09:49:57] Connected
TESTVGA.CPP: start
VGA_t4.cpp: about to execute begin
VGA_t4.cpp: mode = 0:VGA_t4.cpp: we should be inside VGA_MODE_320x240
VGA_t4.cpp: about to execute init_pio_framebuffer
VGA_t4.cpp: about to execute multicore_launch_core1
VGA_t4.cpp: about to execute clear
VGA_t4.cpp: about to execute drawRect
TESTVGA.CPP: buf: 230
*/




