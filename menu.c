#include <stdio.h>
#include <ctype.h>
#include "menu.h"

int menu(void){
	char strChoice[3];
	char c;
	int i, isNum;
	int choice;
	// Menu presentation
		decorText('#',40, 1);
		decorText('#',4, 0); printf("Do you want to start a new game?"); decorText('#',4, 1);
		decorText('#',40, 1);
		do{
			printf("\n1. New game\n2. Exit\n\n");
			//clear stdin stream
			fflush(stdin);
			//maximum characters input in fgets = 3
			//One character is \0, the other the expected 1 or 2 and the third to check for
			//invalid input. If max length was set to 2 then, and the input was e.g. 15 or 25 or 2sdf the
			//program couldn't detect that the input would be invalid. It would store only the first digit,
			//that is 1 or 2 along with '\0' in strChoice[] string.
			//The program would continue as if the user had pressed 1 or 2 instead of the possible wrong
			//inputs 15, 25, 2[space], 1dsdf dkkd, etc.
			if (fgets(strChoice, 3, stdin) != NULL){
				isNum = isNumber(strChoice, 3);
				if (isNum == 1) choice = atoi(strChoice);		
				system("cls");
			}	
		
			if (!(choice == 1 || choice == 2)){
				system("cls");
				printf("\nCAUTION: Only choices available are: 1 and 2 !!\n");
		    }
		}while(!(choice == 1 || choice == 2));
		return choice;
}

void decorText(char character, int n, int newline){
	int i;
	for(i = 0 ; i < n; i++ )
		printf("%c", character);
	if (newline){
		printf("\n");
	}
}

int isNumber(char strChoice[], int n){
	int i, isNum = 0;
	char c;
	for (i=0;i<n;i++){
		c = strChoice[i];
		if (isdigit(c) || c=='\0' || c=='\n'){
			isNum = 1;
		}else{						
			printf("That was not a number!\n");
			isNum = 0;
			system("pause");
			// /*pause for Linux:*/
			//system("read -p \"Press a key to continue\" ");
			break;
		}
	}
	return isNum;
}
