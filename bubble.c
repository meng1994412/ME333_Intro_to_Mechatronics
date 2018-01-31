/*
 * bubble.c
 *
 * This program sorts a string of text in ascending order
 * according to the ASCII table values of characters.
 *
 * Hustory:
 * Jan 14, 2017   Chenyang Meng
 */

#include <stdio.h>
#include <string.h>
#define MAXLENGTH 100         // max length of string input

void getString(char *str);    // helper prototypes
void printResult(char *str);
int greaterThan(char ch1, char ch2);
void swap(char *str, int index1, int index2);

int main(void) {

  int len;                    // length of the entered string
  char str[MAXLENGTH];        // input should be no longer than MAXLENGTH
  int greater;                // check whether the first value is greater than second
                              // and will return 1 if first > second, and 0 if first < second
  getString(str);             // get input string
  len = strlen(str);          // get the length of the string, from string.h

  // the loop that sorts the string
  for (int i = 0; i <= len - 1; i++) {
    for (int j = 0; j <= len - 2; j++) {
      greater = greaterThan(str[j], str[j+1]);
      if (greater) {
        swap(str, j, j + 1);
      }
    }
  }
  // print out the result
  printResult(str);
  return(0);

}

// helper functions
void getString(char *str) {
  printf("Enter the string you would like to sort (up to %d):   ", MAXLENGTH);
  scanf("%s", str);
}

void printResult(char *str) {
  printf("Here is sorted string:  %s", str);
}

int greaterThan(char ch1, char ch2) {
  int valid;
  // compare the two values and return the boolean type value
  valid = ch1 > ch2;
  return valid;
}

void swap(char *str, int index1, int index2) {
  // create an temporary parameter to store the value
  char temp = str[index1];
  str[index1] = str[index2];
  str[index2] = temp;
}
