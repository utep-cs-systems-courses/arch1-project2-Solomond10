#include <msp430.h>
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "stateMachines.h"
#include "libTimer.h"

short var = 1000;
unsigned char red_on = 0, green_on = 0, led_changed = 0, state_status = 0;
/* state_status is the status of state's 1,2,3 and 4. So if state_status is equal to 1 state we go to state 1.*/

static char redVal[] = {0,LED_RED}, greenVal[] = {0,LED_GREEN};

void led_init()
{
  P1DIR |= LEDS;	      // bits attached to leds are output
  switch_state_changed = 1;
  led_changed = 1;
  led_update();
  
}

void led_update(){
  char ledFlags = redVal[red_on] | greenVal[green_on];
  if (switch_state_changed) {
    
    if (button1_down){
      state_status = 1;

      red_on &= 0;
      green_on &= 0;
      buzzer_set_period(0);

      
      if(led_changed){
       
	P1OUT &= (0xff^LEDS) | ledFlags;
	P1OUT |= ledFlags;
	led_changed = 0;
      }
     
    }
    else if(button2_down){
      state_status = 2;
      
      red_on &= 0;
      green_on &= 0;
      buzzer_set_period(0);
      
      if(led_changed){
       
 	P1OUT &= (0xff^LEDS) | ledFlags;
	P1OUT |= ledFlags;
	led_changed = 0;
      }
    }
    else if(button3_down){
      state_status = 3;

      red_on &= 0;
      green_on &= 0;
      buzzer_set_period(0);
    }
    else if(button4_down){
       state_status = 4;

      red_on &= 0;
      green_on &= 0;
      buzzer_set_period(0);
      
    }
    else if(button4_down & button1_down){
      state_status = 5;

      /* Shuts leds and buzzer off */
      
    }

    P1OUT &= (0xff - LEDS) | ledFlags; // clear bits for off leds
    P1OUT |= ledFlags;         // set bits for on leds
  }
  
  switch_state_changed = 0;
}

