#include "NU32.h"

#define NUMSAMPS 1000
static volatile int Waveform[NUMSAMPS];

void makeWaveform();

void __ISR(8, IPL5SOFT) Controller(void) {  // _TIMER_2_VECTOR = 8
  static int counter = 0;
  OC1RS = Waveform[counter];

  counter++;                    // add one to counter every time ISR is entered
  if (counter == NUMSAMPS) {
    counter = 0;                // roll the counter over when needed
  }
  IFS0bits.T2IF = 0;
}

int main(void) {
  NU32_Startup();
  __builtin_disable_interrupts();

  T3CONbits.TCKPS = 0b000;
  PR3 = 3999;
  TMR3 = 0;

  T2CONbits.TCKPS = 0b011;
  PR2 = 9999;
  TMR2 = 0;

  OC1CONbits.OCTSEL = 1; //
  OC1CONbits.OCM = 0b110;
  OC1RS = 3000;
  OC1R = 3000;
  T2CONbits.ON = 1;
  T3CONbits.ON = 1;
  OC1CONbits.ON = 1;

  makeWaveform();

  // Timer2 interrupt
  IPC2bits.T2IP = 5;      // interrupt priority
  IPC2bits.T2IS = 0;      // interrupt subpriority
  IFS0bits.T2IF = 0;      // interrupt flag status
  IEC0bits.T2IE = 1;      // enable interrupt
  __builtin_enable_interrupts();

  /*
  _CP0_SET_COUNT(0);
  while(_CP0_GET_COUNT() < 4 * 40000000) { ; }

  OC1RS = 3000;
  */
  while(1) { ; }
  return(0);
}

void makeWaveform() {
  int i = 0, center = 2000, A = 1000;
  for (i = 0; i < NUMSAMPS; ++i) {
    if (i < NUMSAMPS / 2) {
      Waveform[i] = center + A;
    } else {
      Waveform[i] = center - A;
    }
  }
}
