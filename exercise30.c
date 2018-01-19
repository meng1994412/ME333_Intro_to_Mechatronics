#include <stdio.h>

int main(void) {

  int x[4] = {4, 3, 2, 1};

  printf("(a) answer = %d\n", x[1]);
  printf("(b) address = %d\n", *x);
  printf("(c) value = %d\n", *(x + 2));
  printf("(d) value = %d\n", (*x) + 2);
  //printf("(e) value = %d\n", *x[3]);
  printf("(f) answer = %d\n", x[4]);
  printf("(g) value = %d\n", *(&(x[1]) + 1));
}
