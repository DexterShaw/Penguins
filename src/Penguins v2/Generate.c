#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	FILE* file;
	int x;
	int y;
	printf("Enter board dimensions\n");
	printf("Horizontal: ");
	scanf("%d", &x);
	printf("Vertical: ");
	scanf("%d", &y);

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
}
