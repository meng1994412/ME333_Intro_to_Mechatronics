#include <xc.h>          // Load the proper header for the processor

#define MAXCYCLES 1500000
#define DELTACYCLES 50000

void delay(int cycles);

int main(void) {
  TRISF = 0xFFFC;        // Pins 0 and 1 of Port F are LED1 and LED2.  Clear
                         // bits 0 and 1 to zero, for output.  Others are inputs.
  LATFbits.LATF0 = 0;    // Turn LED1 on and LED2 off.  These pins sink current
  LATFbits.LATF1 = 1;    // on the NU32, so "high" (1) = "off" and "low" (0) = "on"

  int cycles = MAXCYCLES;
  while(1) {
    delay(cycles);
    LATFINV = 0x0003;    // toggle LED1 and LED2; same as LATFINV = 0x3;
    cycles = cycles - DELTACYCLES;
    if (cycles < 0) {
      cycles = MAXCYCLES;
    }
  }
  return 0;
}

void delay(int cycles) {
  int j;
  for (j = 0; j < cycles; j++) { // number is 1 million
    while(!PORTDbits.RD7) {
        ;   // Pin D7 is the USER switch, low (FALSE) if pressed.
    }
  }
}
