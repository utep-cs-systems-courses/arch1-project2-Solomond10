## Description

This program uses interrupts on to detect whether one of the 4 switches from
the extension board was pressed or not. When one of the switches on the
extension board is pressed a specific task is carried out depending on which
was pressed. Switch 1 alternates between red and green leds being lit. Switch
2 changes the birghtness of the red led. Switch 3 makes a range of different
sounds using the buzzer. Switch 4 combines all the actions of from swtitch 1
to switch 3 into one by having a the tone of the buzzer alternate when the
leds alternate.  

## How to Use 

The Makefile in this directory is used to build program on the msp430 in order
to be able to run the program on the msp430.
