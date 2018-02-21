The following are in the helper.h file:
preprocess comand for header file, constants such as: 
#include <xc.h>, #include <stdio.h>, #include <sys/attribs.h> 
#define MAX_YEARS 100, #define MAX_MESSAGE_LENGTH 200

structure Investment

function prototype such as:
int getUserInput(Investment *invp)
void calculateGrowth(Investment *invp)
void sendOutput(double *arr, int years)


The following are in the helper.c file:
preprocess command for header file such as:
#include "NU32.h", #include "helper.h"

each function details
int getUserInput(Investment *invp)
void calculateGrowth(Investment *invp)
void sendOutput(double *arr, int years)


The following are in the main.c:
preprocessor command for header files, such as:
#include "NU32.h", #include "helper.h"

main function