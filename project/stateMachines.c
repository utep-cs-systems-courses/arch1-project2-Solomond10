#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

static enum {off=0, dim=1, bright=2} ledMode;
static char pwmCount = 0;
static enum {low=0, low_moderate=1, moderate=2, low_high=3, moderate_high=4, very_high=5} soundState;
static enum {turn_off=0} offState;
//extern sound_speed();

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

/* Changes the buzzer's frequency to get different sounds */
void sm_sound(){
  
  static char soundState = 0;
  switch(soundState){

  case low:
    buzzer_set_period(200);
    soundState = 5;
    break;
  case low_moderate:
    buzzer_set_period(400);
    soundState = 1;
  case moderate:
    buzzer_set_period(575);
    soundState = 4;
    break;
  case low_high:
    buzzer_set_period(750);
    soundState = 2;
    break;  
  case moderate_high:
    buzzer_set_period(900);
    soundState = 0;
    break;
  case very_high:
    buzzer_set_period(1500);
    soundState = 3;
    break;
    }
}

void sm_slow_clock()
{
  ledMode = (ledMode + 1) % 3;
}

void sm_fast_clock()
{
  pwmCount = (pwmCount + 1) & 3;
}

void sm_update_led()
{
  char new_green_on;
  
  switch (ledMode) {
  case off:
    new_green_on = 0; break;
  case bright:
    new_green_on = 1; break;
  case dim:
    new_green_on = (pwmCount < 1); break;
  }
  if (green_on != new_green_on){
    green_on = new_green_on;
    led_changed = 1;
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





