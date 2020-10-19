//#include "structures.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <windows.h>

#define ID "FishEater69"

int main(int argc, char*argv[]){
	char *commands[6]={ "phase=placement", "phase=movement", "id", "inputboard.txt", "outputboard.txt" };
	int *p;
	int a=0, npeng, nplay;
	p=&a;
	char *boardname[2];

	if (argc > 1)
	{
		if(*argv[1]==*commands[2])
		{
			printf("%s", ID);
			return 0;
		}else if(*argv[1]==*commands[0])
		
		{

			*boardname[0]=*argv[1];
			*boardname[1]=*argv[2];
			//BoardGeneration("INTERACTIVE_D", 2);
			struct board** brd;
			brd=LoadBoard(boardname[0]);
			printf("%d", 1);
			ComputerPlacement(brd, 0, p, 1, 1);
			printf("%d", 2);
			OverwriteFile(brd, 1, boardname[1]);
			printf("%d", 3);
			PrintBoard(brd, 1, 1);
			printf("%d", 4);	
			
		} else if (*argv[1]==*commands[1])
			{
				nplay=LoadNplayers
				npeng=LoadNpenguins;
				
				ComputerMovement(brd, 0, p, nplay, npeng)
			}
		
	}else printf("bruh");
	
	return 0;
}

//autor - Mikołaj Linczewski
