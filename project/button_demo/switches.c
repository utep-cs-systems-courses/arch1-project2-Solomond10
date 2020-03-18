#include <msp430.h>
#include "switches.h"
#include "led.h"


char button1_down, button2_down, button3_down, button4_down, switch_state_changed;

/* effectively boolean */
//char switch_state_down, switch_state_changed; /* effectively boolean */

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
  button1_down = (p2val & SW1) ? 0 : 1; /* 0 When switch 1 is up  */
  button2_down = (p2val & SW2) ? 0 : 1; /* 0 When switch 2 is up  */
  button3_down = (p2val & SW3) ? 0 : 1; /* 0 When switch 3 is up  */
  button4_down = (p2val & SW4) ? 0:  1; /* 0 When switch 4 is up  */

  switch_state_changed = 1;
  led_update();
}
