#include <stdio.h>

int main()
{
	int i;
	int x, y;
	char dim[4];
	FILE* file;
	file=fopen("board.txt", "r");
	
	for(i=0;i<4;i++)
	{
		dim[i]=fgetc(file);
		if(i==0)
		{
			x=dim[i]-'0';
		}
		if(i==2)
		{
			y=dim[i]-'0';
		}
	}
	
	for(i=0;i<4;i++)
	{
		//printf("%c", dim[i]);
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
	
	int nboard[y][x*2];
	int w=-1;
	
	for(n=0;n<y;n++)
	{
	for(m=0;m<x*3+1;m++)
	{
		if(board[n][m] != ' ' && board[n][m] != '\n')
		{
			w++;
		nboard[n][w]=board[n][m]-'0';
		//printf("%d ", nboard[n][w]);
		}
		w=-1;
	}
	}
	
	//printf("\n");
	
	
	char cmd[20];
	int a=0;
	int b=0;
	
	while(1)
	{
	for(n=0;n<y;n++)
	{
	for(m=0;m<x*3+1;m++)
	{
		if(board[n][m]=='1' && m%3==1 && m != x*3+1)
			{
			printf("P.1 ");
			board[n][m-1]='0';
			}
		if(board[n][m]=='2' && m%3==1 && m != x*3+1)
			{
			printf("P.2 ");
			board[n][m-1]='0';
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
	}
	if(strcmp(cmd, "place2")==0)
	{
		board[a][b+1]='2';
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
