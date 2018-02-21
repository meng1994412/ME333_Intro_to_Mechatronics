#include "NU32.h"
#include "helper2.h"


int main(void) {

  Investment inv;

  // code altered here
  NU32_Startup();

  while(getUserInput(&inv)) {
      inv.invarray[0] = inv.inv0;
      calculateGrowth(&inv);
      sendOutput(inv.invarray, inv.years);

  }
  return(0);
}
