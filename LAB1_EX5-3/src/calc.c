#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "calcLogic.h"

#define BUFFER_SIZE 200
char dashLine[BUFFER_SIZE] = "------------------------------------------------------------------------------------";


int main(){
	
	printf("%s\n",dashLine);
	while (1){
		clearStr();
		getStrInput();
		seperateStr();
		if (strcmp(operator,plus)!=0 && strcmp(operator,minus)!=0 && strcmp(operator,mul)!=0 && strcmp(operator,integerDiv)!=0 && strcmp(operator,divWithR)!=0 && strcmp(operator,nullChar)!=0){
			printf("SYNTAX ERROR\n");
			clearStr();
			continue;		
		}
		else if ((atoi(oprd2)==0 && strcmp(operator,divWithR)==0) || (atoi(oprd2)==0 && strcmp(operator,integerDiv)==0)){
			printf("MATH ERROR\n");
			clearStr();
			continue;
		}
		else if (strcmp(oprd1,getOut)==0){
			break;
		}
		else {runCalc(); printResult(); clearStr();}
		getchar();
			
	}
	return 0;
}
