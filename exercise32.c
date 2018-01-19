#include <stdio.h>

int main(void) {

  unsigned char a = 0x0D, b = 0x03, c;
  c = ~a;
  printf("(a): %x\n", c);
  c = a & b;
  printf("(b): %x\n", c);
  c = a | b;
  printf("(c): %x\n", c);
  c = a ^ b;
  printf("(d): %x\n", c);
  c = a >> 3;
  printf("(e): %x\n", c);
  c = a << 3;
  printf("(f): %x\n", c);
  c &= b;
  printf("(g): %x\n", c);

  return(0);
}
