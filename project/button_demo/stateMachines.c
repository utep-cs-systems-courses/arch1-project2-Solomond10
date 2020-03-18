#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

static enum {off=0, dim=1, bright=2} ledMode;
static char pwmCount = 0;

static enum {low=0, moderate=1, high=2, very_high=3} soundState;
static enum {turn_off=0} offState;



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

void sm_sound(){
  static char soundState = 0;
  
  switch(soundState){
    
  case low:
    buzzer_set_period(200);
    soundState = 1;
    break;

  case moderate:
    buzzer_set_period(500);
    soundState = 2;
    break;

  case high:
    buzzer_set_period(700);
    soundState = 3;
    break;

  case very_high:
    buzzer_set_period(1000);
    soundState = 0;
    break;

  }

}

void sound_speed(){
  
  soundState = (soundState + 1) % 3;

}



void sm_slow_clock(){

  ledMode = (ledMode + 1) % 3;

}

void sm_fast_clock(){

  pwmCount = (pwmCount + 1) & 3;

}



void sm_update_led()

{

  char new_green_on;

  switch (ledMode) {

  case off:
    new_green_on = 0;
    break;

  case bright:
    new_green_on = 1;
    break;

  case dim:
    new_green_on = (pwmCount < 1);
    break;

  }

  if (green_on != new_green_on){

    green_on = new_green_on;
    led_changed = 1;

  }

}



char toggle_red()/* always toggle! */

{

  static char state = 0;

  switch (state) {

  case 0:

    red_on = 0;
    state = 1;
    break;

  case 1:

    red_on = 1;
    state = 0;
    break;

  }

  return 1;/* always changes an led */

}



char toggle_green()/* only toggle green if red is on!  */

{

  char changed = 0;

  if (red_on) {
    green_on ^= 1;
    changed = 1;

  }

  return changed;

}





void state_advance()/* alternate between toggling red & green */

{

  char changed = 0;



  static enum {R=0, G=1} color = G;

  switch (color) {

  case R: changed = toggle_red(); color = G;
  break;
  
  case G: changed = toggle_green(); color = R;
  break;

  }
  
  led_changed = changed;
  led_update();

}



