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
	
	for(n=0;n<y;n++)
	{
	for(m=0;m<x*3+1;m++)
	{
		board[n][m]=fgetc(file);
		//printf("%c", board[n][m]);
	}
	}
	
	char cmd[20];
	int a=0;
	int b=0;
	int tempa;
	int tempb;
	char tempc;
	while(1)
	{
	for(n=0;n<y;n++)
	{
	for(m=0;m<x*3+1;m++)
	{
		if(board[n][m]=='1' && m%3==1 && m != x*3+1)
			{
			if(a==n && b==m-1)
		{
			printf("<=> ");
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
		}else{
			printf(" X  ");
			}
		}
		if(board[n][m]=='1' && board[n][m+1]=='0' && m%3==0 && m !=x*3+1)
		{
			if(a==n && b==m)
		{
			printf("<=> ");
		}else{
			printf("-|- ");
			}
		}
		if(board[n][m]=='2' && board[n][m+1]=='0' && m%3==0 && m !=x*3+1)
		{
			if(a==n && b==m)
		{
			printf("<=> ");
		}else{
			printf("|-| ");
			}
		}
		if(board[n][m]=='3' && board[n][m+1]=='0' && m%3==0 && m !=x*3+1)
		{
			if(a==n && b==m)
		{
			printf("<=> ");
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
	scanf("%s", cmd);
	if(strcmp(cmd, "d")==0)
	{
		b=b+3;
	}
	if(strcmp(cmd, "a")==0)
	{
		b=b-3;
	}
	if(strcmp(cmd, "w")==0)
	{
		a=a-1;
	}
	if(strcmp(cmd, "s")==0)
	{
		a=a+1;
	}
	if(strcmp(cmd, "place1")==0)
	{
		board[a][b+1]='1';
		score1=score1+board[a][b]-'0';
		board[a][b]='0';
	}
	if(strcmp(cmd, "place2")==0)
	{
		board[a][b+1]='2';
		score2=score2+board[a][b]-'0';
		board[a][b]='0';
	}
	if(strcmp(cmd, "exit")==0)
	{
		return 0;
	}
	if(strcmp(cmd, "select")==0)
	{
		tempa=a;
		tempb=b;
		tempc=board[a][b+1];
	}
	if(strcmp(cmd, "move")==0 && board[a][b+1]=='0')
	{
		board[a][b+1]=tempc;
		if(tempc == '1')
		{
			score1=score1+(board[a][b]-'0');
		}
		if(tempc == '2')
		{
			score2=score2+(board[a][b]-'0');
		}
		board[tempa][tempb+1]='0';
		tempc='0';
	}
	for(n=0;n<y;n++)
	{
	for(m=0;m<x*3+1;m++)
	{
		//printf("%c", board[n][m]);
	}
	}
	system("cls");
}
}
