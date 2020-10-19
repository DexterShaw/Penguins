#include <stdio.h>

struct board
{
	int border;
	int fish;
	int playerid;
	int cursor;
	int selected;
};

struct player
{
	int id;
	int score;
	char name[30];
}p[9];

struct settings
{
	char phase[30];
	char input[30];
	char output[30];
	int penguins;
	int id;
	int dimx;
	int dimy;
	int score;
	int numofplayers;
}set1;
