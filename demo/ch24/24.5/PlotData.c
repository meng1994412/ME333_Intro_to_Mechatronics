#include "NU32.h"
#include <stdio.h>
#include "LCD.h"

#define NUMSAMPS 1000       // number of points in waveform
#define PLOTPTS 200         // number of data points to plot
#define DECIMATION 10       // plot every 10th point
#define SAMPLE_TIME 10      // 10 core timer ticks = 250 ns
#define MSG_LEN 20          // max length of the message on the LCD screen

static volatile int Waveform[NUMSAMPS];   // waveform
static volatile int ADCarrary[PLOTPTS];   // measured values to plot
static volatile int REFarrary[PLOTPTS];   // reference values to plot
static volatile int StoringData = 0;      // if this flag = 1, currently stroing plot data
static volatile float Kp = 0, Ki = 0;     // control gains
static volatile float eint = 0;           // integral error for PI Control

void makeWaveform();
void printGainsToLCD();


void __ISR(_TIMER_2_VECTOR, IPL5SOFT) Controller(void) {
  static int counter = 0;           // initialize counter once
  static int plotind = 0;           // index for data arrays; counts up to PLOTPTS
  static int decctr = 0;            // counts to store data one every DECIMATION
  static int adcval = 0;
  static float e;                     // proportional error for PI Control
  static float u;
  static float unew;

  // read ADC values
  unsigned elapsed = 0, finish_time = 0;
  AD1CHSbits.CH0SA = 0;         // connect the chosen pin to MUXA for sampling
  AD1CON1bits.SAMP = 1;          // start manual sampling
  elapsed = _CP0_GET_COUNT();
  finish_time = elapsed + SAMPLE_TIME;
  while (_CP0_GET_COUNT() < finish_time) {
    ;
  }
  AD1CON1bits.SAMP = 0;          // stop sampling and start converting
  AD1CON1bits.SSRC = 0b111;     // auto conversion
  while (!AD1CON1bits.DONE) {   // wait for conversion process to finish
    ;
  }
  adcval = ADC1BUF0;

  // PI Controller
  e = Waveform[counter] - adcval;            // proportional error
  eint = eint + e;                           // sum of integral error
  u = Kp * e + Ki * eint;                    // output of PI Controller
  unew = u + 50.0;
  if (unew > 100.0) {
    unew = 100.0;
  } else if (unew < 0.0) {
    unew = 0.0;
  }

  OC1RS = (unsigned int) ((unew / 100.0) * PR3);        // insert line(s) to set OC1RS

  // Save data to the Arrays
  if (StoringData) {
    decctr++;
    if (decctr == DECIMATION) {     // after DECIMATION control loops
      decctr = 0;                   // reset the DECIMATION counter
      ADCarrary[plotind] = adcval;  // store data in global arrays
      REFarrary[plotind] = Waveform[counter];
      plotind++;                    // increment plot data index
    }
    if (plotind == PLOTPTS) {       // if max number of plot points plot is reached
      plotind = 0;
      StoringData = 0;
    }
  }
  counter++;                          // add one to counter every time ISR is entered
  if (counter == NUMSAMPS) {
    counter = 0;                    // rollover counter ove when end of waveform reached
  }
  IFS0bits.T2IF = 0;                // clear interrupt flag
}


int main(void) {
  NU32_Startup();
  LCD_Setup();
  char message[100];                  // message to and from Matlab
  float kptemp = 0, kitemp = 0;       // temporary local gains
  int i = 0;                          // plot data loop counter

  __builtin_disable_interrupts();
  // Timer 3
  T3CONbits.TCKPS = 0b000;
  PR3 = 3999;
  TMR3 = 0;

  // Timer 2
  T2CONbits.TCKPS = 0b011;
  PR2 = 9999;
  TMR2 = 0;

  // Output Compare
  OC1CONbits.OCTSEL = 1; //
  OC1CONbits.OCM = 0b110;
  OC1RS = 3000;
  OC1R = 3000;

  // ADC
  AD1PCFGbits.PCFG0 = 0;    // AN0 is an adc point
  AD1CON3bits.ADCS = 2;     // ADC period clock
  AD1CON1bits.ADON = 1;     // turn on A/D converter

  T2CONbits.ON = 1;
  T3CONbits.ON = 1;
  OC1CONbits.ON = 1;

  makeWaveform();
  // Interrupt
  IPC2bits.T2IP = 5;      // interrupt priority
  IPC2bits.T2IS = 0;      // interrupt subpriority
  IFS0bits.T2IF = 0;      // interrupt flag status
  IEC0bits.T2IE = 1;      // enable interrupt
  __builtin_disable_interrupts();

  while (1) {
    NU32_ReadUART3(message, sizeof(message));     // wait for a meesage from Matlab
    sscanf(message, "%f %f", &kptemp, &kitemp);
    __builtin_disable_interrupts();               // keep ISR disabled as briefly as possible
    Kp = kptemp;                                  // copy local variables to global variables used by ISR
    Ki = kitemp;
    printGainsToLCD();
    __builtin_enable_interrupts();                // only 2 simple c commands while ISRs disabled
    StoringData = 1;                              // message to ISR to start storing data
    while (StoringData) {
      ; // do nothing
    }
    for (i = 0; i < PLOTPTS; i++) {               // send plot data to Matlab
                                                  // when first number sent = 1, Matlab knows we're done
      sprintf(message, "%d %d %d\r\n", PLOTPTS - i, ADCarrary[i], REFarrary[i]);
      NU32_WriteUART3(message);
    }

  }
}

void makeWaveform() {
  int i = 0, center = 500, A = 300;
  for (i = 0; i < NUMSAMPS; ++i) {
    if (i < NUMSAMPS / 2) {
      Waveform[i] = center + A;
    } else {
      Waveform[i] = center - A;
    }
  }
}

void printGainsToLCD() {
  char first[MSG_LEN];
  char second[MSG_LEN];

  LCD_Clear();
  LCD_Move(0, 0);
  sprintf(first, "Kp: %4.1f", Kp);
  LCD_WriteString(first);
  LCD_Move(1, 0);
  sprintf(second, "Ki: %4.1f", Ki);
  LCD_WriteString(second);
}
