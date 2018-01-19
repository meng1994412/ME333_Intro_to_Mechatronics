#include <stdio.h>

int main(void) {
  int a = 2, b = 3, c;
  float d = 1.0, e = 3.5, f;

  //a
  f = a / b;
  printf("f = %.3f\n", f);
  //b
  f = ((float) a) / b;
  printf("f = %.3f\n", f);
  //c
  f = (float) (a / b);
  printf("f = %.3f\n", f);
  //d
  c = e / d;
  printf("c = %d\n", c);
  //e
  c = (int) (e / d);
  printf("c = %d\n", c);
  //f
  f = ((int) e) / d;
  printf("f = %.3f\n", f);
}
