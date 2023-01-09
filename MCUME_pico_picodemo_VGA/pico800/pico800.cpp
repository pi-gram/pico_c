#include "pico.h"
#include "pico/stdlib.h"
#include <string.h>

extern "C" {
  #include "iopins.h"  
  #include "emuapi.h"  
}
#include "keyboard_osd.h"

extern "C" {
#include "atari800.h"
}
#include <stdio.h>

#include "hardware/clocks.h"
#include "hardware/vreg.h"

//FORCE the situation to use this library
#include "vga_t_dma.h"
//#ifdef USE_VGA
//#include "vga_t_dma.h"
//#else
//#include "tft_t_dma.h"
//#endif
volatile bool vbl=true;
const uint LED_PIN = PICO_DEFAULT_LED_PIN;

bool repeating_timer_callback(struct repeating_timer *t) {
    if (vbl) {
        vbl = false;
    } else {
        vbl = true;
    }   
    return true;
}
TFT_T_DMA tft;

static int skip=0;


int main(void) {
    emu_printf("pico800 init");

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
    emu_printf("just done stdio_init_all");
    
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
    
    
//#ifdef USE_VGA    
////    tft.begin(VGA_MODE_400x240);
    emu_printf("about to invoke TFT 320x240 mode");
    tft.begin(VGA_MODE_320x240);
//#else
//    tft.begin();
//#endif    
    emu_printf("about to call emu_init");
    emu_init();
    
    emu_printf("about to enter loop-i-de-loop");
    //0x0020 = MASK_KEY_USER1
    int action = handleMenu(0x0020);
    emu_printf("returned from handleMenu");
    emu_printi(action); //125
    
    //how does the VGA user actually select a filename? or we can even hardcode this
    //
    //how does this actutally then invoke the emulator?
    //where is that code?
    //
    //let's wait for a little bit - 5scs sounds long enough
    sleep_ms(5000);
	emu_printf("about to call emu_start");
	emu_start();        
	emu_printf("about to init filename");
	//emu_Init("/800/Abracadabra.rom");      
	//emu_Init("/800/Alf in the Color Caves.rom");
	emu_Init("/800/Alien Ambush.rom");
	//emu_Init("/800/Alien Garden.rom");
	//emu_Init("/800/3-D Tic-Tac-Toe.rom");
	tft.fillScreenNoDma( RGBVAL16(0x00,0x00,0x00) );
	tft.startDMA();
	struct repeating_timer timer;
	add_repeating_timer_ms(5, repeating_timer_callback, NULL, &timer);
    tft.waitSync();
    emu_printf("okay - we are here: about to loop emu_Step()");
    //now keep looping
    while (true) {
        emu_Step();
    }
/*    
    while (true) {
        if (menuActive()) {
            uint16_t bClick = emu_DebounceLocalKeys();
            int action = handleMenu(bClick);
            char * filename = menuSelection();   
            emu_printf("menu is active");
            if (action == ACTION_RUNTFT) {           //126
              toggleMenu(false);
              emu_printf("about to call emu_start");
              emu_start();        
              emu_printf("about to init filename");
              emu_Init(filename);      
              tft.fillScreenNoDma( RGBVAL16(0x00,0x00,0x00) );
              tft.startDMA();
              struct repeating_timer timer;
              add_repeating_timer_ms(5, repeating_timer_callback, NULL, &timer);
            }  
            tft.waitSync();
        }
        else {  
            emu_printf("menu is not active therefore loop for debouncing keys");
            emu_Step(); 
            uint16_t bClick = emu_DebounceLocalKeys();
            emu_Input(bClick);      
        }
        //int c = getchar_timeout_us(0);
        //switch (c) {
        //    case ' ':
        //        printf("test: %d\n", 1);
        //        break;
        //}
    }
*/    
}

static unsigned char  palette8[PALETTE_SIZE];
static unsigned short palette16[PALETTE_SIZE];

void emu_SetPaletteEntry(unsigned char r, unsigned char g, unsigned char b, int index)
{
    if (index<PALETTE_SIZE) {
        palette8[index]  = RGBVAL8(r,g,b);
        palette16[index]  = RGBVAL16(r,g,b);        
    }
}

void emu_DrawVsync(void)
{
    skip += 1;
    skip &= VID_FRAME_SKIP;
    volatile bool vb=vbl; 
    while (vbl==vb) {};
#ifdef USE_VGA   
//    tft.waitSync();                   
#else                      
//    volatile bool vb=vbl; 
//    while (vbl==vb) {};
#endif
}

void emu_DrawLine(unsigned char * VBuf, int width, int height, int line) 
{
    if (skip == 0) {
#ifdef USE_VGA                        
         tft.writeLine(width,height,line, VBuf, palette8);
#else
         tft.writeLine(width,height,line, VBuf, palette16);
#endif      
    }  
}  

void emu_DrawLine8(unsigned char * VBuf, int width, int height, int line) 
{
    if (skip == 0) {
#ifdef USE_VGA                        
      tft.writeLine(width,height,line, VBuf);
#endif      
    }
} 

void emu_DrawLine16(unsigned short * VBuf, int width, int height, int line) 
{
    if (skip == 0) {
#ifdef USE_VGA        
        tft.writeLine16(width,height,line, VBuf);
#endif        
    }
}  

void emu_DrawScreen(unsigned char * VBuf, int width, int height, int stride) 
{
    if (skip == 0) {
#ifdef USE_VGA                
        tft.writeScreen(width,height-TFT_VBUFFER_YCROP,stride, VBuf+(TFT_VBUFFER_YCROP/2)*stride, palette8);
#endif
    }
}

int emu_FrameSkip(void)
{
    return skip;
}

void * emu_LineBuffer(int line)
{
    return (void*)tft.getLineBuffer(line);    
}


#ifdef HAS_SND
#include "AudioPlaySystem.h"
AudioPlaySystem mymixer;

void emu_sndInit() {
  tft.begin_audio(256, mymixer.snd_Mixer);
  mymixer.start();    
}

void emu_sndPlaySound(int chan, int volume, int freq)
{
  if (chan < 6) {
    mymixer.sound(chan, freq, volume); 
  }
}

void emu_sndPlayBuzz(int size, int val) {
  mymixer.buzz(size,val); 
}

#endif


