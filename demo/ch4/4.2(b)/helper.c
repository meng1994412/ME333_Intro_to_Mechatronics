#include "NU32.h"
#include "helper.h"

void calculateGrowth(Investment *invp) {

  int i;

  for (i = 1; i <= invp->years; i = i + 1) {
    invp->invarray[i] = invp->growth * invp->invarray[i - 1];
  }
}

int getUserInput(Investment *invp) {

  int valid;
  // code altered here
  char intro[100];
  char inputMsg[100];
  char checkMsg1[100];
  char checkMsg2[100];

  // code alter here
  sprintf(intro, "Enter investment, growth rate, number of yrs (up to %d): ", MAX_YEARS);
  NU32_WriteUART3(intro);

  NU32_ReadUART3(inputMsg, MAX_MESSAGE_LENGTH);
  sscanf(inputMsg, "%lf %lf %d",  &(invp->inv0), &(invp->growth), &(invp->years));

  valid = (invp->inv0 > 0) && (invp->growth > 0) &&
    (invp->years > 0) && (invp->years <= MAX_YEARS);
  sprintf(checkMsg1, "Valid input?  %d\n", valid);
  NU32_WriteUART3(checkMsg1);
  if (!valid) {
    // code altered here
    sprintf(checkMsg2, "Invalide input; exiting.\n");
    NU32_WriteUART3(checkMsg2);
  }
  return (valid);
}

void sendOutput(double *arr, int yrs) {

  int i;
  char outstring[100];

  // code altered here
  char result[100];
  sprintf(result, "\nRESULTS:\n\n");
  NU32_WriteUART3(result);
  for (i = 0; i <= yrs; i++) {
    sprintf(outstring, "Year %3d: %10.2f\n", i, arr[i]);
    NU32_WriteUART3(outstring);
  }
  NU32_WriteUART3("\n");
}
