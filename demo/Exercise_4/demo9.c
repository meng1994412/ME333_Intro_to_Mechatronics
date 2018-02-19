#include "NU32.h"
#include "LCD.h"
#include <stdio.h>

#define MSG_LEN 20
#define MAXCYCLES 5000000

void delay(int cycles);

int main(void) {
  char count[MSG_LEN];
  char msg[MSG_LEN];
  int i = 5;
  int cycles = MAXCYCLES;

  NU32_Startup();
  LCD_Setup();

  while (i >= 0) {
    delay(cycles);
    LCD_Clear();
    LCD_Move(0, 7);
    sprintf(count, "%d", i);
    LCD_WriteString(count);
    i = i - 1;
  }
  LCD_Move(1, 5);
  sprintf(msg, "W00T!");
  LCD_WriteString(msg);


  return (0);
}

void delay(int cycles) {
  int j;
  for (j = 0; j < cycles; j++) { // number is 1 million
    while(!PORTDbits.RD7) {
        ;   // Pin D7 is the USER switch, low (FALSE) if pressed.
    }
  }
}
