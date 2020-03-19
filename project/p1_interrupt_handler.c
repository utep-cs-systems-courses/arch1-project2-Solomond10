#include <msp430.h>
#include "switches.h"

/* Switch on P2 (S2) */
void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IES & SWITCHES) {	      /* did a button cause this interrupt? */
    P2IES &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}

