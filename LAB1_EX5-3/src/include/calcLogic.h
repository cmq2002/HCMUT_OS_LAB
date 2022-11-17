#ifndef __CALC_LOGIC_H__
#define __CALC_LOGIC_H__


#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAGIC_TERMINAL_CLEANER "\e[1;1H\e[2J"
#define MAX_INPUT 100
#define MAX_SUBSTR 10


extern char input[MAX_INPUT];

extern char oprd1[MAX_SUBSTR];

extern char oprd2[MAX_SUBSTR];

extern char operator[MAX_SUBSTR];

extern char plus[MAX_SUBSTR];

extern char minus[MAX_SUBSTR];

extern char mul[MAX_SUBSTR];

extern char integerDiv[MAX_SUBSTR];

extern char divWithR[MAX_SUBSTR];

extern char nullChar[MAX_SUBSTR];

extern char getOut[MAX_SUBSTR];

extern float result;

void getStrInput(void);

void seperateStr(void);

void clearStr(void);

void printResult(void);

void runCalc(void);

#endif 
