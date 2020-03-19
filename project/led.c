#include <msp430.h>
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "stateMachines.h"
#include "libTimer.h"

short var = 1000;
unsigned char red_on = 0, green_on = 0, led_changed = 0, current_state = 0;
/* current_state is the status of state's 1,2,3 and 4. So if current_state is equal to 1 state we go to state 1.*/

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
      current_state = 1;

      /* Turns off lights and buzzer before the new pattern starts  */
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
      current_state = 2;

      /* Turns off lights and buzzer before the new pattern starts  */
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
      current_state = 3;

      /* Turns off lights and buzzer before the new pattern starts  */
      red_on &= 0;
      green_on &= 0;
      buzzer_set_period(0);
    }
    else if(button4_down){
       current_state = 4;

       /* Turns off lights and buzzer before the new pattern starts  */
      red_on &= 0;
      green_on &= 0;
      buzzer_set_period(0);
      
    }
    
    P1OUT &= (0xff - LEDS) | ledFlags; // clear bits for off leds
    P1OUT |= ledFlags;         // set bits for on leds
  }
  
  switch_state_changed = 0;
}

