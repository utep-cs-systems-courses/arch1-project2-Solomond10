## Description

This program uses interrupts on to detect whether one of the 4 switches from
the extension board was pressed or not. When one of the switches on the
extension board is pressed a specific task is carried out depending on which
was pressed. Switch 1 acts as an off button for both the buzzers and leds. Switch
2 when press turn on both green and red leds, then blinks red only, then green
only, then both leds shut off. Switch 3 has a similar sequence to switch 2 but
nows implements noise that from the buzzer. Switch 4 combines all the actions of from swtitch 2
and switch 3 into one by having a the tone of the buzzer alternate when the
leds alternate but implements the dimming of leds.  

## How to Use 

The Makefile in this directory is used to build program on the msp430 in order
to be able to run the program on the msp430. To implement program onto msp430
simply type make load while in the project folder. To get rid of unwanted executable
files simply type make clean while in the project folder.
