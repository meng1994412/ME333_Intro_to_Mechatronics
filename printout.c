#include <stdio.h>
int main(void) {
  int i; float f; double d; char c;

  i = 32; f = 4.278; d = 4.278; c = 'k';
  printf("Formatted output: \n");
  printf(" i = %4d c = '%c'\n", i, c);
  printf(" f = %19.17f\n", f);
  printf(" d = %19.17lf\n", d);
  return(0);

}
