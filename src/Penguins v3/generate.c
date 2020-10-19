#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
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
}
