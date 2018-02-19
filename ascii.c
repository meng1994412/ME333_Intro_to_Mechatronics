/* This program generate ASCII values
 * for 33 to 127. The output should be
 * two columns: the left side with number
 * and the right side with the corresponding
 * character
 *
 * History
 * Jan 10, 2017       Chenyang Meng */

#include <stdio.h>

void printTable(int num);

int main(void) {

  int start = 33;
  int end = 127;
  int i;

  printf("Table (33 to 127):\n");
  for (i = start; i <= end; i++) {
    printTable(i);
  }
  return(0);
}

void printTable(int num) {
  printf("%3d    %4c\n", num, num);
}
