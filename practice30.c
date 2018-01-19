#include <stdio.h>

int main(void) {

  int x[5] = {30, 6, 9, 55, 102};

  printf("\nsize of the array x = %d\n", sizeof(x));
  printf("\n");

  printf("answer = %3d\n", x[1]); // return the second value in the array
  printf("answer = %3d\n", x[3]);
  printf("answer = %3d\n", x[5]);
  printf("\n");

  printf("answer = %3d\n", *x); //return the first value in the array
  printf("answer = %3d\n", *(x + 1));
  printf("answer = %3d\n", *(x + 2));
  printf("answer = %3d\n", *(x + 4));
  printf("answer = %3d\n", *(x + 5));
  printf("\n");

  printf("address = %3d\n", &x); //return the first value address in the array
  printf("address = %3d\n", &x[0]);
  printf("address = %3d\n", &x[1]);
  printf("address = %3d\n", &x[2]);
  printf("address = %3d\n", &x[3]);
  printf("address = %3d\n", &x[4]);
  printf("address = %3d\n", &x[5]);
  printf("address = %3d\n", &x[6]);
  printf("\n");

  printf("address = %3d\n", x); //return the value same as &x
  printf("\n");

  printf("value = %3d\n", *(&(x[1])));
  printf("value = %3d\n", *(&(x[1]) + 1));
  printf("value = %3d\n", *(&(x[1]) + 3));

}
