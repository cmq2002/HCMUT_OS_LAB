#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "calcLogic.h"

char input[MAX_INPUT] = "";

char oprd1[MAX_SUBSTR] = "";

char oprd2[MAX_SUBSTR] = "";

char operator[MAX_SUBSTR] = "";

char plus[MAX_SUBSTR] = "+";

char minus[MAX_SUBSTR] = "-";

char mul[MAX_SUBSTR] = "*";

char divWithR[MAX_SUBSTR] = "/";

char integerDiv[MAX_SUBSTR] = "%";

char nullChar[MAX_SUBSTR] = "";

char getOut[MAX_SUBSTR] = "EXIT";

float result = 0;

void getStrInput(void){
	printf(">> ");
	scanf("%[^\n]s",input);
}

void seperateStr(void){
	size_t i=0;
	for (; i<strlen(input); i++){
		if (input[i] == ' ' || input[i] == '\0') break;
		oprd1[i] = input[i];
	}
	
	i++;
	size_t j = 0;
	for (; i<strlen(input); i++){
		if (input[i] == ' ' || input[i] == '\0') break;
		operator[j] = input[i];
		j++;
	}
	
	i++;
	j = 0;
	for (; i<strlen(input); i++){
		if (input[i] == ' ' || input[i] == '\0') break;
		oprd2[j] = input[i];
		j++;
	}
}

void clearStr(void){
	strcpy(input, "");
	strcpy(oprd1, "");
	strcpy(oprd2, "");
	strcpy(operator, "");
}

void printResult(void){
	if (strcmp(operator,divWithR)==0) printf("%.2f\n", result);
	else printf("%.0f\n",result);
}

void runCalc(void){
	if (strcmp(operator, plus)==0) result = atoi(oprd1) + atoi(oprd2);
	else if (strcmp(operator,minus)==0) result = atoi(oprd1) - atoi(oprd2);
	else if (strcmp(operator,mul)==0) result = atoi(oprd1) * atoi(oprd2);
	else if (strcmp(operator,integerDiv)==0) {
		result = atoi(oprd1) / atoi(oprd2);
	}
	else if (strcmp(operator,divWithR)==0){
	  	result = atoi(oprd1)*1.00 / atoi(oprd2);
	}
}


