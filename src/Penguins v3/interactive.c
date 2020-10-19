#include <stdio.h>
#include <math.h>

int main()
{
	char dim[20];
	FILE* file; 
	file=fopen("board.txt", "r");
	int o=0;
	int x=0;
	int y=0;
	
	int score1=0;
	int score2=0;
	
	//load dimensions
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
		
	char board[y][x*3+1];
	
	int m;
	int n;
	
	//load the board
	for(n=0;n<y;n++)
	{
	for(m=0;m<x*3+1;m++)
	{
		board[n][m]=fgetc(file);
	}
	}
	
	fclose(file);
	
	printf("Enter the number of penguins per player: ");
	int penguins;
	int num=0;
	scanf("%d", &penguins);
	system("cls");
	
	char cmd;
	int a=0;
	int b=0;
	int tempa;
	int tempb;
	char tempc;
	char selected;
	char sel[3];
	int phase=0;
	int turn=0;
	while(1)
	{
		if(phase==0)
	{
		printf("Phase: placement\n");
	}
	else
	{
		printf("Phase: movement\n");
	}
	printf("Player%d's turn\n\n", (turn%2)+1);
	for(n=0;n<y;n++)
	{
	for(m=0;m<x*3+1;m++)
	{
		//board drawing
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
	
	printf("Score 1: %d\n", score1);
	printf("Score 2: %d\n", score2);
	
	if(selected=='0')
	{
		strcpy(sel," X ");
	}
	if(selected=='1')
	{
		strcpy(sel,"-|-");
	}
	if(selected=='2')
	{
		strcpy(sel,"|-|");
	}
	if(selected=='3')
	{
		strcpy(sel,"|||");	
	}
	if(selected=='4')
	{
		strcpy(sel,"P.1");	
	}
	if(selected=='5')
	{
		strcpy(sel,"P.2");	
	}
	
	printf("Currently selected tile: %s\n", sel);
	
	cmd=getch();
	
	//cursor movement	
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
	
	//placement phase
	if(phase==0)
	{
	if(cmd=='x' && turn%2==0)
		{
			board[a][b+1]='1';
			score1=score1+board[a][b]-'0';
			board[a][b]='0';
			turn++;
			cmd='n';
		}
	if(cmd=='x' && turn%2==1)
		{
			board[a][b+1]='2';
			score2=score2+board[a][b]-'0';
			board[a][b]='0';
			turn++;
			cmd='n';
		}
	}
	
	//movement phase
	if(phase==1)
	{
		if(cmd=='e')
		{
			tempa=a;
			tempb=b;
			tempc=board[a][b+1];
		}
		if(cmd=='r' && turn%2==0 && board[a][b+1]=='0' && tempc=='1')
		{
			board[a][b+1]='1';
			score1=score1+(board[a][b]-'0');
			board[tempa][tempb+1]='0';
			turn++;
			tempc='0';
		}
		if(cmd=='r' && turn%2==1 && board[a][b+1]=='0' && tempc=='2')
		{
			board[a][b+1]='2';
			score2=score2+(board[a][b]-'0');
			board[tempa][tempb+1]='0';
			turn++;
			tempc='0';
		}
	}

	
	if(turn==penguins*2)
		{
			phase=1;
		}
		
	system("cls");
}
}
