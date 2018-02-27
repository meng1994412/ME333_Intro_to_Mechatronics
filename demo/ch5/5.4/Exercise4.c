#include "NU32.h"
#include <stdio.h>

int main(void) {
  unsigned int u1 = 33, u2 = 17, u3;

  u3 = u1 & u2;   // bitwise AND
  u3 = u1 | u2;   // bitwise OR
  u3 = u1 << 4;   // shift left 4 spaces, or multiply by 2^4 = 16
  u3 = u1 >> 3;   // shift right 3 spaces, or divide by 2^3 = 8
}
