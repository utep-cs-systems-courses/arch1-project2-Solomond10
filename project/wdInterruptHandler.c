#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "assembly.h"
#include "soundChange.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;
  static char sound_count = 0;

  switch(current_state){


    /* Button 2*/
  case 2:
    if(++blink_count == 75){
      change_states();
      blink_count = 0;

    }
    break;

    /* Button 3*/
  case 3:
    if(++blink_count == 25){
      change_states();
      sm_slow_clock();
      sm_sound();
      blink_count = 0;
    }
    sound_speed();
    sm_fast_clock();
    sm_update_led();
    led_update();
    break;

    /*Button 4*/
  case 4:  
    if(++blink_count == 95){
      change_states();
      sm_slow_clock();
      sm_sound();
      blink_count = 0;
    }
    sound_speed();
    sm_fast_clock();
    sm_update_led();
    led_update();
    break;

    /*Button 1 - OFF BUTTON*/
    case 1:
    if(++blink_count == 125){
      sm_off();
    }
    break;
  }
}
