#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int dimcheck(int a, int b){
	if(a>0 && b>0){
		return 1;
	}else {return 0;}
}




int main(int argc, char *argv[]){
	int h,w; //board dimenions
	int i, k, l; //counters for fors
	int fypos, fxpos; 
	int tile = "o";
	int fish[6];
	fish[0]="f";
	fish[1]=" ff";
	fish[2]="  fff";
	fish[3]=" ff";
	fish[4]="f";
	fish[5]="f";
	
	int fnum;
	
	int fishcount;
	if(argc<3){
		printf("give board dimensions, height, width \n");
		scanf("%d %d", &h, &w);
		if(dimcheck(h, w)==1){
			printf("board dimensions are %d, %d \n", h, w);
	}else{
		printf("dimensions must be larger than 0 \n");
		return 0;
	}
	}else {
		h=atoi(argv[1]);
		w=atoi(argv[2]);
		
		if(dimcheck(h, w)==1){
			printf("board dimensions are %d, %d \n", h, w);
		}else{
			printf("dimensions must be larger than 0 \n");
			return 0;
		}
			
			
	}
	//^checking and printing board dimensions^//
	
	int board[h][w];
	
	
	
	
	for(i = 0; i < h; i++){
		for( k=0; k<w; k++ ){
			board[i][k]= tile;
		}
	} 
	
	fishcount=(h*w)*0.15;
	srand(time(0));
	
	for(l=0;l<fishcount;l++){
		fypos=(rand() % (h-1));
		fxpos=(rand() % (w-1));
		fnum=(rand() % 6);
		board[fypos][fxpos]= fish[fnum];
	}	
	
	//assigning values to the board
	
		for(i = 0; i < h; i++){
			for( k=0; k<w; k++ ){
				printf("%4s", board[i][k]);
		}
		printf("\n \n");
	} 
	//printing the board
	return 0;
}
