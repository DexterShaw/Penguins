#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

#define ID "FishEater69"

int main(int argc, char* argv[])
{

	if (argc > 1)
	{
	char *commands[6]={ "phase=placement", "phase=movement", "id", "inputboard.txt", "outputboard.txt" };
	int *p;
	int a=0;
	int npeng, nplay;
	p=&a;
	char *boardname[2];


	if (argc > 1)
	{
		if(*argv[1]==*commands[2])
		{
			printf("%s", ID);
			return 0;
		}else if(strcmp("phase=placement", argv[1])==0)
		
		{
			boardname[0]=argv[3];
			struct board** brd;
			brd=LoadBoardAuto(boardname[0]);
			brd=CompPlacement(brd);
			PrintBoardAuto(brd);
			OverwriteFile(brd, 1, argv[4]);
			free(brd);
			
		} else if (strcmp("phase=movement", argv[1])==0)
			{
				
				printf("qwweqw");
				struct board** brd;
			brd=LoadBoardAuto(argv[3]);
				nplay=LoadNplayers();
				npeng=LoadNpenguins(brd, nplay);
				
				ComputerMovement(brd, 0, p, set1.numofplayers, npeng);
				OverwriteFile(brd, 1, argv[4]);
			PrintBoardAuto(brd);	
			}

		
	}else printf("bruh");
	
	return 0;
	}
	else
	{
		int i, j;
		int turn = 0;
		int nplayers;
		int npenguins;
		struct board** board;
		int gamemode = Menu();
		if (gamemode == 11)
		{
			system("cls");
			board = LoadBoard("board.txt");
			nplayers = LoadNplayers();
			npenguins = LoadNpenguins(board, nplayers);
			strcpy(set1.phase, "movement");
			system("cls");

			while (CanMove(board, turn, &turn, nplayers, npenguins) == 1)
			{
				CheckNpenguins(board, npenguins, nplayers);
				PrintBoard(board, turn, nplayers);
				if (turn % nplayers == 0)
				{
					board = Commands(board, turn, &turn, nplayers, set1.phase);
				}
				else
				{
					if (strcmp(set1.phase, "placement") == 0)
					{
						board = ComputerPlacement(board, turn, &turn, nplayers, npenguins);
					}
					if (strcmp(set1.phase, "movement") == 0)
					{
						board = ComputerMovement(board, turn, &turn, nplayers, npenguins);
					}
				}
				if (turn % nplayers == 0)
				{
					OverwriteFile(board, nplayers, "board.txt");
				}
				system("cls");
			}
		}
		if (gamemode == 12)
		{
			system("cls");
			printf("Enter the number of players");
			scanf("%d", &nplayers);
			printf("Enter the number of penguins per player");
			scanf("%d", &npenguins);
			BoardGeneration("INTERACTIVE_D", nplayers);
			board = LoadBoard("board.txt");
			strcpy(set1.phase, "placement");
			system("cls");

			while (CanMove(board, turn, &turn, nplayers, npenguins) == 1)
			{
				CheckNpenguins(board, npenguins, nplayers);
				PrintBoard(board, turn, nplayers);
				if (turn % nplayers == 0)
				{
					board = Commands(board, turn, &turn, nplayers, set1.phase);
				}
				else
				{
					if (strcmp(set1.phase, "placement") == 0)
					{
						board = ComputerPlacement(board, turn, &turn, nplayers, npenguins);
					}
					if (strcmp(set1.phase, "movement") == 0)
					{
						board = ComputerMovement(board, turn, &turn, nplayers, npenguins);
					}
				}
				if (turn % nplayers == 0)
				{
					OverwriteFile(board, nplayers, "board.txt");
				}
				system("cls");
			}
		}
		if (gamemode == 21)
		{
			system("cls");
			board = LoadBoard("board.txt");
			nplayers = LoadNplayers();
			npenguins = LoadNpenguins(board, nplayers);
			strcpy(set1.phase, "movement");
			system("cls");

			while (CanMove(board, turn, &turn, nplayers, npenguins) == 1)
			{
				CheckNpenguins(board, npenguins, nplayers);
				PrintBoard(board, turn, nplayers);
				board = Commands(board, turn, &turn, nplayers, set1.phase);
				if (turn % nplayers == 0)
				{
					OverwriteFile(board, nplayers, "board.txt");
				}
				system("cls");
			}
		}
		if (gamemode == 22)
		{
			system("cls");
			printf("Enter the number of players");
			scanf("%d", &nplayers);
			printf("Enter the number of penguins per player");
			scanf("%d", &npenguins);
			BoardGeneration("INTERACTIVE", nplayers);
			board = LoadBoard("board.txt");
			strcpy(set1.phase, "placement");
			system("cls");

			while (CanMove(board, turn, &turn, nplayers, npenguins) == 1)
			{
				CheckNpenguins(board, npenguins, nplayers);
				PrintBoard(board, turn, nplayers);
				board = Commands(board, turn, &turn, nplayers, set1.phase);
				if (turn % nplayers == 0)
				{
					OverwriteFile(board, nplayers, "board.txt");
				}
				system("cls");
			}
		}
	}
}
