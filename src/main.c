#include "functions.h"
#include <stdio.h>

int main(int argc, char* argv[])
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
		board = LoadBoard();
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
				OverwriteFile(board, nplayers);
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
		board = LoadBoard();
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
				OverwriteFile(board, nplayers);
			}
			system("cls");
		}
	}
	if (gamemode == 21)
	{
		system("cls");
		board = LoadBoard();
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
				OverwriteFile(board, nplayers);
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
		BoardGeneration("INTERACTIVE_D", nplayers);
		board = LoadBoard();
		strcpy(set1.phase, "placement");
		system("cls");

		while (CanMove(board, turn, &turn, nplayers, npenguins) == 1)
		{
			CheckNpenguins(board, npenguins, nplayers);
			PrintBoard(board, turn, nplayers);
			board = Commands(board, turn, &turn, nplayers, set1.phase);
			if (turn % nplayers == 0)
			{
				OverwriteFile(board, nplayers);
			}
			system("cls");
		}
	}
}