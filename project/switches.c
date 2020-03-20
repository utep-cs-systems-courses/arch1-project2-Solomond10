#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "buzzer.h"

char button1_down, button2_down, button3_down, button4_down, switch_state_changed;
/* effectively boolean */
short cycles = 1000;

static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE = SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
  led_update();
  
}

void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  button1_down = (p2val & SW1) ? 0 : 1; /* Assigns button1_down to switch 1  */
  button2_down = (p2val & SW2) ? 0 : 1; /* Assigns button2_down to switch 2  */
  button3_down = (p2val & SW3) ? 0 : 1; /* Assigns button3_down to switch 3  */
  button4_down = (p2val & SW4) ? 0:  1; /* Assigns button4_down to switch 4  */
  switch_state_changed = 1;
  led_update();
  
}
