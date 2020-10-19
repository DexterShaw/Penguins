#include "functions.h"

int main()
{
	
	FILE* file; 
	file=fopen("board.txt", "r");
	int x, y;
	int a=0; 
	int b=0;
	
	generate();//created a text file with randomly generated map
	
	loaddim(file, &x, &y);//loads board dimensions and converts them to integers
	
	int penguins=npenguins();//returns the number of penguins
	system("cls");
	
while(1)
{
	drawboard(file, x, y, a, b);//draws the board based on the board dimensions
	
	commands(getch(), a, b, &a, &b);//currently it only handles movement

	fclose(file);
	file=fopen("board.txt", "r");
	
	dummy(file);// goes through the first line of the text file without doing anything else
}
	
}
