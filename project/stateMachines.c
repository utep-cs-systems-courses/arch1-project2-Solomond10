#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

static enum {turn_off=0} offState;

/* Turns off buzzers and leds  */
void sm_off(){
  
  switch(offState){
    case turn_off:
      red_on &= 0;
      green_on &= 0;
      buzzer_set_period(0);
      offState = 0;
      break;
  }
}

void change_states()		/* Blink both red and green leds at the same time, then red only, 
				   then green only, then off */
{
  char changed = 0;  

  static enum {O=0, R=1, G=2, G_R=3} color = G_R;

  switch (color) {

  case O: //Turns off both red and green led
    red_on &= 0;
    green_on &= 0;
    color = G_R;
    break;
    
  case R: //Turns on red led and turns off green led
    red_on = 1;
    green_on &= 0;
    color = G;
    break;
    
  case G: //Turns on green led and turns off red led
    green_on = 1;
    red_on &= 0;
    color = O;
    break;
    
  case G_R: //Blinks both lights at the same time
    green_on = 1;
    red_on = 1;
    color = R;
    
  }

  led_changed = changed;
  led_update();
}





