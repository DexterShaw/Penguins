#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <windows.h>

struct board** LoadBoard();// initializes an array based on the file provided and returns is. The size of the array is X:x+2, Y:y+2. First and last columns and rows have .border values set to 1 and the rest are set to 0. It also fills the global array 'struct player p[9]' with information about players from the file
struct board** ComputerPlacement(struct board** brd, int turn, int* retu, int nplayers, int npenguins);// randomly places a penguin on a tile with 1 fish. The id of the penguin is determined by the turn and n players with the following formula: turn%nplayers+1
struct board** ComputerMovement(struct board** brd, int turn, int* retu, int nplayers, int npenguins);// randomly choses a penguin and moves it to a nearest tiel with the most fish. The id of the penguin is determined by the turn and n players with the following formula: turn%nplayers+1
void OverwriteFile(struct board** brd, int nplayers);// overwrites the file with the array 'struct board' provided
int LoadNpenguins(struct board** brd, int nplayers); //returns the number of penguins per player. It should be used in movement phase.
int LoadNpenguins(struct board** brd, int nplayers); //returns the number of penguins per player It should be used in movement phase.


int LeglityCheck(struct board** brd); //check whether selected tile is eligible for a move, returns 1 if the selected tile is a valid position to move else returns 0
void BoardGeneration(); //generates the board
void ArgumnetHandling(int number, char** console);
void PrintBoard(struct board** brd, int turn, int nplayers); //prints the board
struct board** Commands(struct board** brd, int turn, int* retu, int nplayers, char* phase); //modifies the board based on the command, returns the modified board
void CheckNpenguins(struct board** brd, int npenguins, int nplayers); //checks whether all penguins have been placed. If so changes the pase to movement
int LoadNplayers(); //return the number of players
int LoadNpenguins(struct board** brd, int nplayers); //returns the number of penguins per player
int CanMove(struct board** brd, int turn, int* retu, int nplayers, int npenguins); //checks whether any penguins can move if not skips the turn and returns 1. If no penguins can move returns 0 
int Menu(); //menu
void OverwriteFile(struct board** brd, int nplayers);
int IsBlocked(struct board** brd, int y, int x);
int Nblocked(struct board** brd, int y, int x);
int* Bubblesort(int* array, int size);
struct board** ComputerPlacement(struct board** brd, int turn, int* retu, int nplayers, int npenguins);
struct board** ComputerMovement(struct board** brd, int turn, int* retu, int nplayers, int npenguins);

int LeglityCheck(struct board** brd)
{
	int i, j;
	int x, y;//cursor coords
	int n, m;//selected coords

	int wCheck=0, sCheck=0, aCheck=0, dCheck=0;

	int SameAxis = 0;

	int GucciLength = 0;

	for (i = 0; i < set1.dimy + 2; i++)
	{
		for (j = 0; j < set1.dimx + 2; j++)
		{
			if (brd[i][j].cursor == 1)
			{
				y = i;
				x = j;
			}
		}
	}

	for (i = 0; i < set1.dimy + 2; i++)
	{
		for (j = 0; j < set1.dimx + 2; j++)
		{
			if (brd[i][j].selected == 1)
			{
				n = i;
				m = j;
			}
		}

	}
	//axis check
	if (n == y || m == x)
	{
		SameAxis = 1;
	}

	//length check
	for (i = n - 1; brd[i][m].fish != 0 && brd[i][m].border != 1; i--)
	{
		wCheck++;
	}
	for (i = n + 1; brd[i][m].fish != 0 && brd[i][m].border != 1; i++)
	{
		sCheck++;
	}
	for (i = m - 1; brd[n][i].fish != 0 && brd[n][i].border != 1; i--)
	{
		aCheck++;
	}
	for (i = m + 1; brd[n][i].fish != 0 && brd[n][i].border != 1; i++)
	{
		dCheck++;
	}

	if (abs(n - y) <= wCheck && y < n)
	{
		GucciLength = 1;
	}
	if (abs(n - y) <= sCheck && y > n)
	{
		GucciLength = 1;
	}
	if (abs(m - x) <= aCheck && x < m)
	{
		GucciLength = 1;
	}
	if (abs(m - x) <= dCheck && x > m)
	{
		GucciLength = 1;
	}

	if (GucciLength == 1 && SameAxis == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void BoardGeneration(char *mode, int nplayers)
{
	int x, y;
	int i, j;
	int r;

	printf("Enter x dimension of the board: ");
	scanf("%d", &x);
	printf("Enter y dimension of the board: ");
	scanf("%d", &y);

	FILE* file;

	file = fopen("board.txt", "w");

	fprintf(file, "%d %d\n", x, y);

	srand(time(0));

	for (i = 0; i < y; i++)
	{
		for (j = 0; j < x; j++)
		{
			r = rand() % 100;

			if (r < 10)
			{
				fprintf(file, "00 ");
			}
			if (r >= 10 && r < 60)
			{
				fprintf(file, "10 ");
			}
			if (r >= 60 && r < 80)
			{
				fprintf(file, "20 ");
			}
			if (r >= 80)
			{
				fprintf(file, "30 ");
			}
		}
		fprintf(file, "\n");
	}

	if (strcmp(mode, "INTERACTIVE") == 0)
	{
		char name[9][30];


		for (i = 0; i < nplayers; i++)
		{
			printf("Enter player%d's name: ", i + 1);
			scanf("%s", name[i]);
			fprintf(file, "%d %s 0\n", i + 1, name[i]);
		}
		fclose(file);
	}

	if (strcmp(mode, "INTERACTIVE_D") == 0)
	{
		char name[9][30] =
		{
			{"Player1"},
			{"Player2"},
			{"Player3"},
			{"Player4"},
			{"Player5"},
			{"Player6"},
			{"Player7"},
			{"Player8"},
			{"Player9"},
		};



		for (i = 0; i < nplayers; i++)
		{
			fprintf(file, "%d %s 0\n", i + 1, name[i]);
		}
		fclose(file);
	}

	fclose(file);
}

void ArgumnetHandling(int number, char **console)
{	
	int i = 0;
	int j = 0;
	int k;
	char temp[30];
	char set[30];

	if (number == 5)
	{
		//phase
		while (console[1][i] != '=')
		{
			i++;
		}
		i++;
		while (console[1][i] != '\0')
		{
			set1.phase[j] = console[1][i];
			i++;
			j++;
		}

		i = 0;
		j = 0;

		//penguins
		while (console[2][i] != '=')
		{
			i++;
		}
		i++;
		while (console[2][i] != '\0')
		{
			set1.penguins = console[2][i] -'0'; //It can only take single digit numbers while it should handle all
			i++;
		}

		i = 0;
		j = 0;

		//input
		while (console[3][i] != '\0')
		{
			set1.input[i] = (console[3][i]);
			i++;
		}

		i = 0;
		j = 0;

		//output
		while (console[4][i] != '\0')
		{
			set1.output[i] = (console[4][i]);
			i++;
		}

		printf("Phase: %s\n", set1.phase);
		printf("Penguins: %d\n", set1.penguins);
		printf("Input: %s\n", set1.input);
		printf("Output: %s\n", set1.output);
	}
	if (number == 4)
	{
		//phase
		while (console[1][i] != '=')
		{
			i++;
		}
		i++;
		while (console[1][i] != '\0')
		{
			set1.phase[j] = console[1][i];
			i++;
			j++;
		}

		i = 0;
		j = 0;

		//input
		while (console[2][i] != '\0')
		{
			set1.input[i] = (console[2][i]);
			i++;
		}

		i = 0;
		j = 0;

		//output
		while (console[3][i] != '\0')
		{
			set1.output[i] = (console[3][i]);
			i++;
		}

		printf("Phase: %s\n", set1.phase);
		printf("Input: %s\n", set1.input);
		printf("Output: %s\n", set1.output);
	}
	if (number == 2)
	{
		
	}
}

struct board** LoadBoard()
{
	int i, j;
	int x=0, y=0;
	char dim[20];
	struct board **brd;
	FILE* file;
	file = fopen("board.txt", "r");

	//load dimensions
	for (i = 0; i < 20; i++)
	{
		dim[i] = fgetc(file);
		if (dim[i] == '\n')
		{
			break;
		}
	}

	int l1 = 0;
	int l2 = 0;

	for (i = 0; dim[i] != ' '; i++)
	{
		l1++;
	}
	for (i = i + 1; dim[i] != '\n'; i++)
	{
		l2++;
	}

	for (i = 0; dim[i] != ' '; i++)
	{
		x = x + (dim[i] - '0') * pow(10, l1 - 1);
		l1--;
	}
	for (i = i + 1; dim[i] != '\n'; i++)
	{
		y = y + (dim[i] - '0') * pow(10, l2 - 1);
		l2--;
	}

	brd = (struct board**)malloc((y+2) * sizeof(struct board*));
	for (i = 0; i < y+2; i++)
	{
		brd[i] = (struct board*)malloc((x+2) * sizeof(struct board));
	}

	char* temp = (char*)malloc((x * 3 + 1) * sizeof(char));

	int k;
	//load tiles
	for (i = 0; i < y + 2; i++)
	{
		for (j = 0; j < x + 2; j++)
		{
			if (i == 0 || i == y + 2 - 1 || j == 0 || j == x + 2 - 1)
			{
				brd[i][j].border = 1;
				brd[i][j].cursor = 0;
				brd[i][j].fish = 0;
				brd[i][j].playerid = 0;
				brd[i][j].selected = 0;
			}
		}
	}

	for (i = 1; i < y+2-1; i++)
	{
		for (k = 0; k < x * 3 + 1; k++)
		{
			temp[k] = fgetc(file);
		}
		k = 0;
		for (j = 1; j < x+2-1; j++)
		{
			brd[i][j].fish = temp[k*3] - '0';
			brd[i][j].playerid = temp[k*3+1] - '0';
			brd[i][j].border = 0;
			brd[i][j].cursor = 0;
			brd[i][j].selected = 0;
			k++;
		}
	}
	char convert[9][30];
	int score[9];
	int o = 0;
	int c = 0;
	int spaces = 0;
	int length = 0;
	int player = 1;
	int l;

	//load player info
	for (i = 0; i < 9; i++)
	{
		score[i] = 0;
	}
	do
	{
		char temp2 = fgetc(file);
		
		if (feof(file))
		{
			break;
		}
		if (spaces == 0)
		{
			p[player - 1].id = temp2 - '0';
		}
		if (spaces == 1)
		{
			if (temp2 != ' ')
			{
				p[player - 1].name[c] = temp2;
				c++;
			}
		}
		if (temp2 == '\n')
		{
			l = length;
			for (i = 0; i<l; i++)
			{
				score[player - 1] = score[player - 1]+(convert[player - 1][i] - '0') * pow(10, length - 1);
				length--;
			}
			p[player - 1].score = score[player - 1];
			p[player-1].id = player;
			spaces = 0;
			length = 0;
			o = 0;
			c = 0;
			player++;
		}
		if (spaces == 2)
		{
			length++;
			convert[player - 1][o] = temp2;
			o++;
		}
		if (temp2 == ' ')
		{
			spaces++;
		}

	} while (1);

	fclose(file);

	brd[(y + 2) / 2][(x + 2) / 2].cursor = 1;

	set1.dimx = x;
	set1.dimy = y;

	return brd;
}

void PrintBoard(struct board** brd, int turn, int nplayers)
{
	int i, j, k;

	printf("%s's turn \nphase: %s\n",p[turn%nplayers].name , set1.phase);

	for (i = 0; i < set1.dimy + 2; i++)
	{
		for (j = 0; j < set1.dimx + 2; j++)
		{
			if (brd[i][j].border == 1)
			{
				if (i == 0 || i == set1.dimy + 2 - 1)
				{
					printf("# ");
					if (j == set1.dimx + 2 - 1)
					{
						for (k = 0; k < set1.dimx; k++)
						{
							printf("# ");
						}
					}
				}
				else
				{
					printf("# ");
				}
			}
			if (brd[i][j].border == 0 && brd[i][j].fish!=0 && brd[i][j].playerid==0 && brd[i][j].cursor == 0)
			{
				printf(" %d  ", brd[i][j].fish);
			}
			if (brd[i][j].border == 0 && brd[i][j].fish == 0 && brd[i][j].playerid == 0 && brd[i][j].cursor == 0)
			{
				printf(" X  ");
			}
			if (brd[i][j].border == 0 && brd[i][j].fish == 0 && brd[i][j].playerid != 0 && brd[i][j].cursor==0)
			{
				printf("P-%d ", brd[i][j].playerid);
			}
			if (brd[i][j].border == 0 && brd[i][j].cursor == 1)
			{
				printf("<=> ");
			}
		}
		printf("\n\n");
	}
	for (i = 0; i < nplayers; i++)
	{
		printf("%s's score: %d\n", p[i].name, p[i].score);
	}
}

struct board** Commands(struct board** brd, int turn, int* retu , int nplayers, char *phase)
{
	int x, y;
	int i, j;
	int n, m;
	char cmd;
	cmd = getch();

	for (i = 0; i < set1.dimy + 2; i++)
	{
		for (j = 0; j < set1.dimx + 2; j++)
		{
			if (brd[i][j].cursor == 1)
			{
				y = i;
				x = j;
			}
		}
	}
	if (cmd == 'w')
	{
		if (brd[y - 1][x].border == 0)
		{
			brd[y][x].cursor = 0;
			y = y - 1;
			brd[y][x].cursor = 1;
		}
	}
	if (cmd == 's')
	{
		if (brd[y + 1][x].border == 0)
		{
			brd[y][x].cursor = 0;
			y = y + 1;
			brd[y][x].cursor = 1;
		}
	}
	if (cmd == 'a')
	{
		if (brd[y][x-1].border == 0)
		{
			brd[y][x].cursor = 0;
			x = x - 1;
			brd[y][x].cursor = 1;
		}
	}
	if (cmd == 'd')
	{
		if (brd[y][x + 1].border == 0)
		{
			brd[y][x].cursor = 0;
			x = x + 1;
			brd[y][x].cursor = 1;
		}
	}
	if (cmd == 'e' && strcmp(set1.phase, "movement")==0)
	{
		for (i = 0; i < set1.dimy + 2; i++)
		{
			for (j = 0; j < set1.dimx + 2; j++)
			{
				brd[i][j].selected = 0;
			}
		}

		brd[y][x].selected = 1;
	}
	if (cmd == 'r' && strcmp(set1.phase, "movement") == 0)
	{
		int initialized = 0;
		for (i = 0; i < set1.dimy + 2; i++)
		{
			for (j = 0; j < set1.dimx + 2; j++)
			{
				if (brd[i][j].selected == 1)
				{
					n = i;
					m = j;
					initialized = 1;
				}
			}
		}
		if (initialized == 1)
		{

			if (brd[y][x].fish!=0 && brd[n][m].playerid != 0 && brd[n][m].playerid== turn % nplayers + 1 && LeglityCheck(brd)==1)
			{
				p[(turn % nplayers)].score = p[(turn % nplayers)].score + brd[y][x].fish;
				brd[n][m].playerid = 0;
				brd[n][m].selected = 0;
				brd[y][x].playerid = turn % nplayers+1;
				brd[y][x].fish = 0;
				turn = turn + 1;
			}
		}
	}
	if (cmd == 'x' && brd[y][x].fish && brd[y][x].fish==1 && strcmp(phase, "placement")==0)
	{
		p[(turn % nplayers)].score = p[(turn % nplayers)].score + brd[y][x].fish;
		brd[y][x].fish = 0;
		brd[y][x].playerid = p[(turn % nplayers)].id;
		turn = turn+1;
	}

	*retu = turn;

	return brd;
}

void CheckNpenguins(struct board** brd, int npenguins, int nplayers)
{
	int i, j;
	int n = 0;

	for (i = 1; i < set1.dimy + 2-1; i++)
	{
		for (j = 1; j < set1.dimx + 2-1; j++)
		{
			if (brd[i][j].playerid != 0)
			{
				n++;
			}
		}
	}

	if (n == npenguins * nplayers)
	{
		strcpy(set1.phase, "movement");
	}
}

int LoadNplayers()
{
	int i=0;
	int nplayers=0;
	while (p[i].id != 0)
	{
		nplayers++;
		i++;
	}
	return nplayers;
}

int LoadNpenguins(struct board** brd, int nplayers)
{
	int i, j;
	int n = 0;

	for (i = 1; i < set1.dimy + 2 - 1; i++)
	{
		for (j = 1; j < set1.dimx + 2 - 1; j++)
		{
			if (brd[i][j].playerid != 0)
			{
				n++;
			}
		}
	}

	return (n / nplayers);
}

int CanMove(struct board** brd, int turn, int *retu, int nplayers, int npenguins)
{

	int i, j;

	int immovable=0;
	int PlayersOut = 0;
	int *sort = (int*)malloc(sizeof(int) * nplayers);

	for (i = 0; i < nplayers; i++)
	{
		sort[i] = p[i].score;
	}

	int temp;
	int count = 0;

	while (1)
	{
		for (i = 0; i < nplayers - 1; i++)
		{
			if (sort[i] > sort[i + 1])
			{
				temp = sort[i + 1];
				sort[i + 1] = sort[i];
				sort[i] = temp;
			}
			else
			{
				count++;
			}
		}
		if (count == nplayers - 1)
		{
			break;
		}
		count = 0;
	}

	if (strcmp(set1.phase, "placement") == 0)
	{
		return 1;
	}
	if (strcmp(set1.phase, "movement") == 0)
	{
		while (PlayersOut != nplayers)
		{
			for (i = 0; i < set1.dimy + 2; i++)
			{
				for (j = 0; j < set1.dimx + 2; j++)
				{
					if (brd[i][j].playerid == turn % nplayers + 1)
					{
						if ((brd[i - 1][j].fish == 0 || brd[i - 1][j].border == 1) && (brd[i + 1][j].fish == 0 || brd[i + 1][j].border == 1) && (brd[i][j - 1].fish == 0 || brd[i][j - 1].border == 1) && (brd[i][j + 1].fish == 0 || brd[i][j + 1].border == 1))
						{
							immovable++;
						}
					}
				}
			}
			if (immovable == npenguins)
			{
				turn = turn + 1;
				immovable = 0;
				PlayersOut++;
				*retu = turn;
			}
			else
			{
				return 1;
			}
			if (PlayersOut == nplayers)
			{
				return 0;
			}
			if (PlayersOut == nplayers - 1 && p[turn % nplayers].score == sort[nplayers - 1] && p[turn % nplayers].score != sort[nplayers - 2])
			{
				printf("Gameover %s wins", p[turn % nplayers].name);
				return 0;
			}
		}
	}
}

int Menu()
{
	int i, j;

	int menu;
	int pointer = 0;
	int layer = 0;
	char cmd='0';

	int sizeoflayer[] = { 3,3,3 };

	char layer0[3][30] =
	{
		{"1. Singleplayer"},
		{"2. Multiplayer"},
		{"3. Exit"}
	};

	char layer1[3][30] =
	{
		{"1. Continue"},
		{"2. New game"},
		{"3. Go back"}
	};

	char layer2[3][30] =
	{
		{"1. Continue"},
		{"2. New game"},
		{"3. Go back"}
	};

	while (1)
	{
		printf("The Penguins Game\n\n");

			switch (layer)
			{
			case 0: 
				for (i = 0; i < sizeoflayer[layer]; i++)
				{
					printf("%s", layer0[i]);
					if (pointer == i)
					{
						printf("<");
					}
					printf("\n");
				}

				cmd = getch();

				if (cmd == 'e')
				{
					switch (pointer)
					{
					case 0:
						pointer = 0;
						layer = 1;
						break;
					case 1:
						pointer = 0;
						layer = 2;
						break;
					case 2:
						exit(1);
						break;
					}
				}
				break;

			case 1:
				for (i = 0; i < sizeoflayer[layer]; i++)
				{
					printf("%s", layer1[i]);
					if (pointer == i)
					{
						printf("<");
					}
					printf("\n");
				}

				cmd = getch();

				if (cmd == 'e')
				{
					switch (pointer)
					{
					case 0:
						return 11;
						break;
					case 1:
						return 12;
						break;
					case 2:
						pointer = 0;
						layer = 0;
						break;
					}
				}
				break;

			case 2:
				for (i = 0; i < sizeoflayer[layer]; i++)
				{
					printf("%s", layer2[i]);
					if (pointer == i)
					{
						printf("<");
					}
					printf("\n");
				}

				cmd = getch();

				if (cmd == 'e')
				{
					switch (pointer)
					{
					case 0:
						return 21;
						break;
					case 1:
						return 22;
						break;
					case 2:
						pointer = 0;
						layer = 0;
						break;
					}
				}
				break;
			}

		if (pointer != 0 && cmd == 'w')
		{
			pointer--;
		}
		if (pointer != sizeoflayer[layer] - 1 && cmd == 's')
		{
			pointer++;
		}

		system("cls");
	}
}

void OverwriteFile(struct board** brd, int nplayers)
{
	int i, j;

	FILE* file;
	file=fopen("board.txt", "w");

	fprintf(file, "%d %d\n", set1.dimx, set1.dimy);

	for (i = 1; i < set1.dimy+2-1; i++)
	{
		for (j = 1; j < set1.dimx+2-1; j++)
		{
			if (brd[i][j].border == 0)
			{
				fprintf(file, "%d%d ", brd[i][j].fish, brd[i][j].playerid);
			}
		}
		fprintf(file, "\n");
	}

	for (i = 0; i < nplayers; i++)
	{
		fprintf(file, "%d %s %d\n", p[i].id, p[i].name, p[i].score);
	}
}

int IsBlocked(struct board** brd, int y, int x)
{
	int dirblocked = 0;

	if (brd[y-1][x].fish == 0 || brd[y-1][x].border == 1)
	{
		dirblocked++;
	}
	if (brd[y+1][x].fish == 0 || brd[y+1][x].border == 1)
	{
		dirblocked++;
	}
	if (brd[y][x-1].fish == 0 || brd[y][x-1].border == 1)
	{
		dirblocked++;
	}
	if (brd[y][x+1].fish == 0 || brd[y][x+1].border == 1)
	{
		dirblocked++;
	}

	if (dirblocked == 4)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int Nblocked(struct board** brd, int y, int x)
{
	int dirblocked = 0;

	if (brd[y - 1][x].fish == 0 || brd[y - 1][x].border == 1)
	{
		dirblocked++;
	}
	if (brd[y + 1][x].fish == 0 || brd[y + 1][x].border == 1)
	{
		dirblocked++;
	}
	if (brd[y][x - 1].fish == 0 || brd[y][x - 1].border == 1)
	{
		dirblocked++;
	}
	if (brd[y][x + 1].fish == 0 || brd[y][x + 1].border == 1)
	{
		dirblocked++;
	}

	return dirblocked;
}

float** LoadDesireability(struct board** brd)
{
	int i, j;

	float** desireability;

	desireability = (float**)malloc(sizeof(float*) * set1.dimy);
	{
		for (i = 0; i < set1.dimy; i++)
		{
			desireability[i] = (float*)malloc(sizeof(float) * set1.dimx);
		}
	}

	for (i = 1; i < set1.dimy + 2 - 1;i++)
	{
		for (j = 1; j < set1.dimx + 2 - 1;j++)
		{
			if (brd[i][j].fish == 3)
			{
				desireability[i - 1][j - 1] = 1.0;
			}
			if (brd[i][j].fish == 2)
			{
				desireability[i - 1][j - 1] = 0.8;
			}
			if (brd[i][j].fish == 1)
			{
				desireability[i - 1][j - 1] = 0.5;
			}
			if (brd[i][j].fish == 0)
			{
				desireability[i - 1][j - 1] = 0.0;
			}
			if (Nblocked(brd, i, j) != 0 && desireability[i - 1][j - 1] != 0.0)
			{
				desireability[i - 1][j - 1] = desireability[i - 1][j - 1] - 0.1 * Nblocked(brd, i, j);
			}
		}
	}
	return desireability;
}

int* Bubblesort(int* array, int size)
{
	int i, j;

	int count = 0;
	int temp;

	while (1)
	{
		for (i = 0; i < size-1; i++)
		{
			if (array[i] > array[i + 1])
			{
				temp = array[i + 1];
				array[i + 1] = array[i];
				array[i] = temp;
			}
			else
			{
				count++;
			}
		}
		if (count == size - 1)
		{
			break;
		}
		count = 0;
	}

	return array;
}

struct board** ComputerPlacement(struct board** brd, int turn, int* retu, int nplayers, int npenguins)
{

		int i, j;
		int ry, rx;

		srand(time(0));

		while (1)
		{
			ry = rand() % set1.dimy + 1;
			rx = rand() % set1.dimx + 1;
			if (brd[ry][rx].fish == 1 && brd[ry][rx].playerid == 0 && brd[ry][rx].border == 0)
			{
				break;
			}
		}

		brd[ry][rx].playerid = turn % nplayers + 1;
		brd[ry][rx].fish = 0;
		p[turn % nplayers].score = p[turn % nplayers].score + 1;

		Sleep(500);

		turn = turn + 1;
		*retu = turn;
		return brd;

}

struct board** ComputerMovement(struct board** brd, int turn, int* retu, int nplayers, int npenguins)
{
	int i, j, k = 0;

	//locate penguins

	int* n = (int*)malloc(sizeof(int) * npenguins);
	int* m = (int*)malloc(sizeof(int) * npenguins);

	for (i = 1; i < set1.dimy + 2 - 1; i++)
	{
		for (j = 1; j < set1.dimx + 2 - 1; j++)
		{
			if (brd[i][j].playerid == turn % nplayers + 1)
			{
				n[k] = i;
				m[k] = j;
				k++;
			}
		}
	}

	//select a penguin

	int r;
	srand(time(0));
	while (1)
	{
		r = rand() % npenguins;
		if (Nblocked(brd, n[r], m[r]) != 4)
		{
			break;
		}
	}

	//check distance

	int wCheck = 0, sCheck = 0, aCheck = 0, dCheck = 0;

	for (i = n[r] - 1; brd[i][m[r]].fish != 0 && brd[i][m[r]].border != 1; i--)
	{
		wCheck++;
	}
	for (i = n[r] + 1; brd[i][m[r]].fish != 0 && brd[i][m[r]].border != 1; i++)
	{
		sCheck++;
	}
	for (i = m[r] - 1; brd[n[r]][i].fish != 0 && brd[n[r]][i].border != 1; i--)
	{
		aCheck++;
	}
	for (i = m[r] + 1; brd[n[r]][i].fish != 0 && brd[n[r]][i].border != 1; i++)
	{
		dCheck++;
	}

	//load fish

	int* fish = (int*)malloc(sizeof(int) * (wCheck + sCheck + aCheck + dCheck));

	k = 0;

	for (i = n[r] - 1; brd[i][m[r]].fish != 0 && brd[i][m[r]].border != 1; i--)
	{
		fish[k] = brd[i][m[r]].fish;
		k++;
	}
	for (i = n[r] + 1; brd[i][m[r]].fish != 0 && brd[i][m[r]].border != 1; i++)
	{
		fish[k] = brd[i][m[r]].fish;
		k++;
	}
	for (i = m[r] - 1; brd[n[r]][i].fish != 0 && brd[n[r]][i].border != 1; i--)
	{
		fish[k] = brd[n[r]][i].fish;
		k++;
	}
	for (i = m[r] + 1; brd[n[r]][i].fish != 0 && brd[n[r]][i].border != 1; i++)
	{
		fish[k] = brd[n[r]][i].fish;
		k++;
	}

	//sort fish

	int* sort;
	sort = Bubblesort(fish, (wCheck + sCheck + aCheck + dCheck));

	int r2;
	int brk = 0;

	//choose a place to move

	while (brk==0)
	{
		r2 = rand() % 4 + 1;

		if (r2 == 1)
		{
			for (i = n[r] - 1; brd[i][m[r]].fish != 0 && brd[i][m[r]].border != 1; i--)
			{
				if (brd[i][m[r]].fish == sort[(wCheck + sCheck + aCheck + dCheck) - 1])
				{
					brd[n[r]][m[r]].playerid = 0;
					brd[i][m[r]].playerid = turn % nplayers + 1;
					p[turn % nplayers].score = p[turn % nplayers].score + brd[i][m[r]].fish;
					brd[i][m[r]].fish = 0;
					brk = 1;
					break;
				}
			}
		}
		if (r2 == 2)
		{
			for (i = n[r] + 1; brd[i][m[r]].fish != 0 && brd[i][m[r]].border != 1; i++)
			{
				if (brd[i][m[r]].fish == sort[(wCheck + sCheck + aCheck + dCheck) - 1])
				{
					brd[n[r]][m[r]].playerid = 0;
					brd[i][m[r]].playerid = turn % nplayers + 1;
					p[turn % nplayers].score = p[turn % nplayers].score + brd[i][m[r]].fish;
					brd[i][m[r]].fish = 0;
					brk = 1;
					break;
				}
			}
		}
		if (r2 == 3)
		{
			for (i = m[r] - 1; brd[n[r]][i].fish != 0 && brd[n[r]][i].border != 1; i--)
			{
				if (brd[n[r]][i].fish == sort[(wCheck + sCheck + aCheck + dCheck) - 1])
				{
					brd[n[r]][m[r]].playerid = 0;
					brd[n[r]][i].playerid = turn % nplayers + 1;
					p[turn % nplayers].score = p[turn % nplayers].score + brd[n[r]][i].fish;
					brd[n[r]][i].fish = 0;
					brk = 1;
					break;
				}
			}
		}
		if (r2 == 4)
		{
			for (i = m[r] + 1; brd[n[r]][i].fish != 0 && brd[n[r]][i].border != 1; i++)
			{
				if (brd[n[r]][i].fish == sort[(wCheck + sCheck + aCheck + dCheck) - 1])
				{
					brd[n[r]][m[r]].playerid = 0;
					brd[n[r]][i].playerid = turn % nplayers + 1;
					p[turn % nplayers].score = p[turn % nplayers].score + brd[n[r]][i].fish;
					brd[n[r]][i].fish = 0;
					brk = 1;
					break;
				}
			}
		}
	}

	Sleep(500);

	turn = turn + 1;
	*retu = turn;
	return brd;
}