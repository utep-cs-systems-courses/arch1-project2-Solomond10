#ifndef switches_included
#define switches_included

#define SW1 BIT0                           /* switch1 is p2.0 */
#define SW2 BIT1                           /* switch2 is p2.1 */
#define SW3 BIT2                           /* switch3 is p2.2 */
#define SW4 BIT3                           /* switch4 is p2.3 */
#define SWITCHES (BIT0 | BIT1 | BIT2 | BIT3)     /* 4 switches on this board */

void switch_init();
void switch_interrupt_handler();

extern char button1_down, button2_down, button3_down, button4_down, switch_state_changed;
/* effectively boolean */

#endif // included
