#include "NU32.h"          // constants, funcs for startup and UART
#include <stdio.h>
#include "LCD.h"

#define MSG_LEN 16

void __ISR(11, IPL6SRS) button(void) { // step 1: the ISR
  float time;
  char timeperiod[MSG_LEN];
  _CP0_SET_COUNT(0);
  while(_CP0_GET_COUNT() < 10000000/25) { ; }
  if (PORTDbits.RD7 == 0) {
    LCD_Clear();
    while (PORTDbits.RD7 == 0) { ; }      // wait until the button is released
    _CP0_SET_COUNT(0);
    LCD_WriteString("Press Again");
    while (PORTDbits.RD7 == 1) { ; }      // wait until the next time the button is pressed
    time = _CP0_GET_COUNT();
    time = time * 0.000000025;
    LCD_Clear();
    LCD_Move(0, 0);
    sprintf(timeperiod, "Time is %5.3fs", time);
    LCD_WriteString(timeperiod);
    LCD_Move(1, 0);
    LCD_WriteString("Press USER");
  }
  IFS0bits.INT2IF = 0;            // clear interrupt flag IFS0<3>

}

int main(void) {
  NU32_Startup(); // cache on, min flash wait, interrupts on, LED/button init, UART init
  LCD_Setup();
  LCD_Clear();
  LCD_Move(0, 0);
  LCD_WriteString("Press USER");
  NU32_LED1 = 1;
  NU32_LED2 = 1;

  __builtin_disable_interrupts(); // step 2: disable interrupts
  INTCONbits.INT2EP = 0;          // step 3: INT0 triggers on falling edge
  IPC2bits.INT2IP = 6;            // step 4: interrupt priority 2
  IPC2bits.INT2IS = 0;            // step 4: interrupt priority 1
  IFS0bits.INT2IF = 0;            // step 5: clear the int flag
  IEC0bits.INT2IE = 1;            // step 6: enable INT0 by setting IEC0<3>
  __builtin_enable_interrupts();  // step 7: enable interrupts
                                  // Connect RD7 (USER button) to INT0 (RD0)
  while(1) {
      ; // do nothing, loop forever
  }

  return 0;
}
