# MCUME PICO usage on a PICO DEMO VGA Board

This is the first experiment taking the MCUME code base from the wonderful website: [MCUME](https://github.com/Jean-MarcHarvengt/MCUME/)

I extracted out the core of what I was looking for in an attempt to understand the code flow as well as how to modify it to make it work with the PICO DEMO VGA board.

Whilst I do have the VGA output working...ish... the colours are all out of whack! It's a bit like watching Stranger Things... basically there is a LOT of RED.  I'm pretty sure that it is because I am using the PICO DEMO VGA Board that uses 5 pins for RED, then 5 for GREEN and then 5 for BLUE - whereas the original setup for MCUME was just 2 for BLUE, 3 for GREEN and 3 for RED - I've left the schematic in a folder.  I'll examine the codebase next to see how this was setup

The DEBUG output (before the _Step() looping) outputs a nice flow of how the code is executing, so you can follow through and trace what is being called and where.

Apart from the screen being mostly in RED.  The only other drawback in this version is the lack of BUTTONS.  I need to add in the usage of Button A, B and C.  But as usual (like the SDCard), it's not straight forward so will take me a bit of time to add them in and even when I do, it'll be limited to LEFT, RIGHT and FIRE... so maybe not all that useful?  Well, it will be for the likes of 'Alien Ambush', so I will be looking at somehow getting the UART from GPIO 20/21 to be used and add a keyboard matrix board (that I just happen to have) or a 5 button analog LEFT, RIGHT, UP, DOWN and FIRE external board that I've got.  We'll see.


A pre-built .uf2 file is included currently within the build folder.  It does require an /800/Alien Ambush.rom file to be on the sdcard.  I'm obviously not distributing any .rom files (for obvious reasons) but you can obtain them easily enough online.


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
It will auto disconnect and then reconnect and you will see the DEBUG output in the tio window, then on the VGA screen you will see a list of the files on the SDCard and then 5 seconds later it will auto-load 'Alien Ambush' and you can watch the intro screen moving about.


I'll add an image or even a video to show it in the current working state shortly and include it below:

