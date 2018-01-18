// 1. Program Commentgs (Purpose, history)

/*
 * invest.c
 *
 * This program takes an initial investment amount, an
 * expected annual return rate, and the number of years,
 * and calculates the growth of the investment. The
 * main point of this program, though, is to demonstrate
 * some C syntax.
 *
 * Hustory:
 * Jan 10, 2017   Created by Chenyang Meng
 */

 /****************************************
  * 2. Preprocessor Commands
*****************************************/

#include <stdio.h>
#define MAX_YEARS 100

/****************************************
 * 3. Data Type Definitions
*****************************************/

typedef struct {
  double inv0;
  double growth;
  int years;
  double invarray[MAX_YEARS + 1];
} Investment;

/****************************************
 * 4. Global Variables
*****************************************/

// no global variables in this Program

/****************************************
 * 5. Helper Function Prototype
*****************************************/

int getUserInput(Investment *invp);
void calculateGrowth(Investment *invp);
void sendOutput(double *arr, int years);

/****************************************
 * 6. Main Function
*****************************************/

int main(void) {

  Investment inv;

  while(getUserInput(&inv)) {
      inv.invarray[0] = inv.inv0;
      calculateGrowth(&inv);
      sendOutput(inv.invarray, inv.years);

  }
  return(0);
}

/****************************************
 * 7. Helper Functions
*****************************************/

void calculateGrowth(Investment *invp) {

  int i;

  for (i = 1; i <= invp->years; i = i + 1) {
    invp->invarray[i] = invp->growth * invp->invarray[i - 1];
  }
}

int getUserInput(Investment *invp) {

  int valid;

  printf("Enter investment, groth rate, number of yrs (up to %d): ", MAX_YEARS);
  scanf("%lf %lf %d",  &(invp->inv0), &(invp->growth), &(invp->years));
  valid = (invp->inv0 > 0) && (invp->growth > 0) &&
    (invp->years > 0) && (invp->years <= MAX_YEARS);
  printf("Valid input?  %d\n", valid);
  if (!valid) {
    printf("Invalide input; exiting.\n");
  }
  return (valid);
}

void sendOutput(double *arr, int yrs) {

  int i;
  char outstring[100];

  printf("\nRESULTS:\n\n");
  for (i = 0; i <= yrs; i++) {
    sprintf(outstring, "Year %3d: %10.2f\n", i, arr[i]);
    printf("%s", outstring);
  }
  printf("\n");
}
