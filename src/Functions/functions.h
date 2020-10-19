#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

void dummy(FILE *file)// goes through the first line of the text file without doing anything else
{
	char dim[20];
	int o=0;
	for(o=0;o<20;o++)
	{
		dim[o]=fgetc(file);
		if(dim[o]=='\n')
		{
			break;
		}
	}
}

void loaddim(FILE *file, int *first, int *scnd)//loads board dimensions and converts them to integers
{
	char dim[20];
	int o=0;
	int x=0;
	int y=0;
	
	for(o=0;o<20;o++)
	{
		dim[o]=fgetc(file);
		if(dim[o]=='\n')
		{
			break;
		}
	}
	
	int q;
	int l1=0;
	int l2=0;
	for(q=0;dim[q]!= ' ';q++)
	{
		l1++;
	}
	for(q=q+1;dim[q]!= '\n';q++)
	{
		l2++;
	}
	
	for(q=0;dim[q] != ' ';q++)
	{
		x=x+(dim[q]-'0')*pow(10, l1-1);
		l1--;
	}
	for(q=q+1;dim[q] != '\n';q++)
	{
		y=y+(dim[q]-'0')*pow(10, l2-1);
		l2--;
	}
	
	*first=x;
	*scnd=y;
}

int npenguins()//returns the number of penguins
{
	printf("Enter the number of penguins per player: ");
	int penguins;
	scanf("%d", &penguins);
	return penguins;
	
}

void drawboard(FILE *file,int x, int y, int a, int b)//draws the board based on the board dimensions
{
	
	char board[y][x*3+1];
	int m, n;
	char selected;
	
	for(n=0;n<y;n++)
	{
	for(m=0;m<x*3+1;m++)
	{
		board[n][m]=fgetc(file);
	}
	}
	
	for(n=0;n<y;n++)
	{
	for(m=0;m<x*3+1;m++)
	{
		if(board[n][m]=='1' && m%3==1 && m != x*3+1)
			{
			if(a==n && b==m-1)
		{
			printf("<=> ");
			selected='4';
		}else{
			printf("P.1 ");
			board[n][m-1]='0';
			}
			}
		if(board[n][m]=='2' && m%3==1 && m != x*3+1)
			{
			if(a==n && b==m-1)
		{
			printf("<=> ");
			selected='5';
		}else{
			printf("P.2 ");
			board[n][m-1]='0';
			}
			}
		if(board[n][m]=='0' && board[n][m+1]=='0' && m%3==0 && m !=x*3+1)
		{
			if(a==n && b==m)
		{
			printf("<=> ");
			selected=board[a][b];
		}else{
			printf(" X  ");
			}
		}
		if(board[n][m]=='1' && board[n][m+1]=='0' && m%3==0 && m !=x*3+1)
		{
			if(a==n && b==m)
		{
			printf("<=> ");
			selected=board[a][b];
		}else{
			printf("-|- ");
			}
		}
		if(board[n][m]=='2' && board[n][m+1]=='0' && m%3==0 && m !=x*3+1)
		{
			if(a==n && b==m)
		{
			printf("<=> ");
			selected=board[a][b];
		}else{
			printf("|-| ");
			}
		}
		if(board[n][m]=='3' && board[n][m+1]=='0' && m%3==0 && m !=x*3+1)
		{
			if(a==n && b==m)
		{
			printf("<=> ");
			selected=board[a][b];
		}else{
			printf("||| ");
			}
		}
		if(board[n][m]=='\n')
		{
			printf("\n\n");
		}
	}
	}
	}
	
	char commands(char cmd, int a, int b, int *first, int *scnd)//currently it only handles movement
	{
		if(cmd=='d')
	{
		b=b+3;
	}
	if(cmd=='a')
	{
		b=b-3;
	}
	if(cmd=='w')
	{
		a=a-1;
	}
	if(cmd=='s')
	{
		a=a+1;
	}
	*first=a;
	*scnd=b;
	system("cls");
	}
	
	void generate()//created a text file with randomly generated map
	{
	FILE* file;
	int x;
	int y;
	label:
	printf("Enter board dimensions\n");
	printf("Horizontal: ");
	scanf("%d", &x);
	printf("Vertical: ");
	scanf("%d", &y);
		
		if(x<0 || y<0)
		{
			printf("Both values must be greater then 0!\n\n");
			goto label;
		}

	int i=0;
	int j=0;
	int r;
	char q;
	
	srand(time(NULL));
	
	file=fopen("board.txt", "w");
	
	fprintf(file,"%d ", x);
	fprintf(file,"%d\n", y);
	
	for(i=0;i<y;i++)
	{	
		for(j=0;j<x;j++)
		{
			r = (rand()%100);
			if(r<=10)
			{
				q='0';
			}
			if(r>10 && r<=50)
			{
				q='1';
			}
			if(r>50 && r<=80)
			{
				q='2';
			}
			if(r>80)
			{
				q='3';
			}
			fprintf(file,"%c", q);
			fprintf(file,"0 ");
		}
		fprintf(file, "\n");
	}
	fclose(file);
	}
