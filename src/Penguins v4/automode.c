#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv){
	
	int score;
	char a, b, c, control;
	int h, w;
	int i, k, l;
	int fish=0;
	int op, sp;
	char name[20];
	
	FILE *board;
	
	board = fopen("board.txt", "r");
	
	fscanf(board, "%d %d", &h, &w);
	
	int **memboard;
	memboard = malloc(h*sizeof(int*));
	for(i=0; i<h; i++){
		memboard[i]=malloc(w*sizeof(int*));
	}
	
	printf("%d %d \n", h, w );
	
	fscanf(board, "%c", &c);
	
	for(i=0; i<h; i++){
	
		for(k=0; k<w; k++){
			fscanf(board, "%c%c ", &a, &b);
			printf("%c%c ", a, b);
			op = a - '0';
			sp = b - '0';
			if(op==1)
			{
				fish++;
				memboard[i][k]=1;
			}else 
			if(op==2)
			{
				fish+=2;
				memboard[i][k]=2;
			}else 
			if(op==3)
			{
				fish+=3;
				memboard[i][k]=3;
			}else memboard[i][k]=4;
			
		}
		printf("\n");
	}
	printf("\n");
	
	printf("there are %d fish \n", fish);
	fscanf(board, "%s ", &name);
	printf("name is %s \n", name);
	for(i=0; i<h; i++){
		for(k=0; k<w; k++){
			if(memboard[i][k]==1)
			{
				memboard[i][k]=7;
				control=1;
				break;
			}
		}
		if(control==1){break;}
	}
	
	for(i=0; i<h; i++){
		for(k=0; k<w; k++){
		printf("%2d", memboard[i][k]);
		}
		printf("\n");
	}
	free(memboard);
	//board=fopen("board.txt", "a+");
	//fprintf(board, "%s", "Fpenguins");
	fclose(board);
	
}
