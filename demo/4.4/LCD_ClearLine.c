#include "NU32.h"
#include "LCD.h"
#include <stdio.h>

#define MSG_LEN 20

void LCD_ClearLine(int ln) {
    char message[MSG_LEN];
    for (int i = 0; i <= MSG_LEN; i++) {
      message[i] = ' ';
    }
    if (ln == 0) {
      LCD_Move(0, 0);
      LCD_WriteString(message);
    } else {
      LCD_Move(1, 0);
      LCD_WriteString(message);
    }

}
