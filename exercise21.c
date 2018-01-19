#include <stdio.h>

int main (void) {

  unsigned char i = 60, j = 80, k = 200;
  unsigned char sum1, sum2, sum3;

  sum1 = i + j;
  sum2 = i + k;
  sum3 = j + k;

  printf("char1:   %3d + %3d = %3d \n", i, j, sum1);
  printf("char2:   %3d + %3d = %3d \n", i, k, sum2);
  printf("char3:   %3d + %3d = %3d \n", j, k, sum3);


}
