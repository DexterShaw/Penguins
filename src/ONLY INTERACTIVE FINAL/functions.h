#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <conio.h>


char **board;
int y=0, x=0;
int a=0, b=0;
int score1=0, score2=0;
int phase=0, turn=0;
int tempa, tempb;
char tempc;
int penguins;
int check;
int ld=0, la=0, lw=0, ls=0;
int end=0;

void print();
void readf();
void generate();
void commands(char cmd);
void npenguins();
void gameOver();

void readf()
{
    FILE* file;
    file=fopen("board.txt", "r");
    char dim[20];
    int o=0;
    int i, j;

    for(o=0; o<20; o++)
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

    for(q=0; dim[q]!= ' '; q++)
    {
        l1++;
    }
    for(q=q+1; dim[q]!= '\n'; q++)
    {
        l2++;
    }

    for(q=0; dim[q] != ' '; q++)
    {
        x=x+(dim[q]-'0')*pow(10, l1-1);
        l1--;
    }
    for(q=q+1; dim[q] != '\n'; q++)
    {
        y=y+(dim[q]-'0')*pow(10, l2-1);
        l2--;
    }

    board=(char**)malloc(y*sizeof(char*));
    for(i=0; i<y; i++)
    {
        board[i]=(char*)malloc((x*3+1)*sizeof(char));
    }

    for(j=0; j<y; j++)
    {
        for(i=0; i<x*3+1; i++)
        {
            board[j][i]=fgetc(file);
        }
    }
    fclose(file);
}

void print()
{
    int n,m;
	
	if(end==1)
    {
    	a=-1;
    	b=-1;
    }
	
    if(phase==0)
    {
        printf("Phase: placement\n");
    }
    else
    {
        printf("Phase: movement\n");
    }
    printf("Player%d's turn\n\n", (turn%2)+1);

    for(n=0; n<y; n++)
    {
        for(m=0; m<x*3+1; m++)
        {
            if(board[n][m]=='1' && m%3==1 && m != x*3+1)
            {
                if(a==n && b==m-1)
                {
                    printf("<=> ");
                }
                else
                {
                    printf("P.1 ");
                    board[n][m-1]='0';
                }
            }
            if(board[n][m]=='2' && m%3==1 && m != x*3+1)
            {
                if(a==n && b==m-1)
                {
                    printf("<=> ");
                }
                else
                {
                    printf("P.2 ");
                    board[n][m-1]='0';
                }
            }
            if(board[n][m]=='0' && board[n][m+1]=='0' && m%3==0 && m !=x*3+1)
            {
                if(a==n && b==m)
                {
                    printf("<=> ");
                }
                else
                {
                    printf(" X  ");
                }
            }
            if(board[n][m]=='1' && board[n][m+1]=='0' && m%3==0 && m !=x*3+1)
            {
                if(a==n && b==m)
                {
                    printf("<=> ");
                }
                else
                {
                    printf("-|- ");
                }
            }
            if(board[n][m]=='2' && board[n][m+1]=='0' && m%3==0 && m !=x*3+1)
            {
                if(a==n && b==m)
                {
                    printf("<=> ");
                }
                else
                {
                    printf("|-| ");
                }
            }
            if(board[n][m]=='3' && board[n][m+1]=='0' && m%3==0 && m !=x*3+1)
            {
                if(a==n && b==m)
                {
                    printf("<=> ");
                }
                else
                {
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

    char sel[3];

    if(board[a][b]=='0' && board[a][b+1]=='0')
    {
        strcpy(sel, " X ");
    }
    if(board[a][b]=='1' && board[a][b+1]=='0')
    {
        strcpy(sel, "-|-");
    }
    if(board[a][b]=='2' && board[a][b+1]=='0')
    {
        strcpy(sel, "|-|");
    }
    if(board[a][b]=='3' && board[a][b+1]=='0')
    {
        strcpy(sel, "|||");
    }
    if(board[a][b+1]=='1')
    {
        strcpy(sel, "P.1");
    }
    if(board[a][b+1]=='2')
    {
        strcpy(sel, "P.2");
    }

    printf("Currently selected tile: %s", sel);
    
    if(end==1)
    {
    	sleep(3);
    	exit(0);
	}
}

void commands(char cmd)
{
    char h;
    int first=0;
    if(cmd=='\e')
    {
        while(1)
        {
            if(first==0)
            {
                printf("\n\nAre you sure you want to exit the program? y/n");
                first=1;
            }
            h=getch();
            if(h=='y')
            {
                exit(0);
            }
            if(h=='n')
            {
                break;
            }
        }
    }
    if(cmd=='d')
    {
        b=b+3;
        if(b>=x*3)
        {
            b=b-3;
        }
    }
    if(cmd=='a')
    {
        b=b-3;
        if(b<0)
        {
            b=b+3;
        }
    }
    if(cmd=='w')
    {
        a=a-1;
        if(a<0)
        {
            a=a+1;
        }
    }
    if(cmd=='s')
    {
        a=a+1;
        if(a>=y)
        {
            a=a-1;
        }
    }

    if(phase==0)
    {
        if(cmd=='x' && turn%2==0 && board[a][b]!='0' && board[a][b+1]=='0')
        {
            board[a][b+1]='1';
            score1=score1+board[a][b]-'0';
            board[a][b]='0';
            turn++;
            cmd='\0';
        }
        if(cmd=='x' && turn%2==1 && board[a][b]!='0' && board[a][b+1]=='0')
        {
            board[a][b+1]='2';
            score2=score2+board[a][b]-'0';
            board[a][b]='0';
            turn++;
            cmd='\0';
        }
    }

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
            if(b==tempb)
            {
                if(tempa-a>0 && tempa-a<=lw)
                {
                    board[a][b+1]='1';
                    score1=score1+(board[a][b]-'0');
                    board[a][b]='0';
                    board[tempa][tempb+1]='0';
                    turn=1;
                    tempc='0';
                }
                if(a-tempa>0 && a-tempa<=ls)
                {
                    board[a][b+1]='1';
                    score1=score1+(board[a][b]-'0');
                    board[a][b]='0';
                    board[tempa][tempb+1]='0';
                    turn=1;
                    tempc='0';
                }
            }

            if(a==tempa)
            {
                if(tempb-b>0 && tempb-b<=la*3)
                {
                    board[a][b+1]='1';
                    score1=score1+(board[a][b]-'0');
                    board[a][b]='0';
                    board[tempa][tempb+1]='0';
                    turn=1;
                    tempc='0';
                }
                if(b-tempb>0 && b-tempb<=ld*3)
                {
                    board[a][b+1]='1';
                    score1=score1+(board[a][b]-'0');
                    board[a][b]='0';
                    board[tempa][tempb+1]='0';
                    turn=1;
                    tempc='0';
                }
            }
        }
        if(cmd=='r' && turn%2==1 && board[a][b+1]=='0' && tempc=='2')
        {
            if(b==tempb)
            {
                if(tempa-a>0 && tempa-a<=lw)
                {
                    board[a][b+1]='2';
                    score2=score2+(board[a][b]-'0');
                    board[a][b]='0';
                    board[tempa][tempb+1]='0';
                    turn=0;
                    tempc='0';
                }
                if(a-tempa>0 && a-tempa<=ls)
                {
                    board[a][b+1]='2';
                    score2=score2+(board[a][b]-'0');
                    board[a][b]='0';
                    board[tempa][tempb+1]='0';
                    turn=0;
                    tempc='0';
                }
            }
            if(a==tempa)
            {
                if(tempb-b>0 && tempb-b<=la*3)
                {
                    board[a][b+1]='2';
                    score2=score2+(board[a][b]-'0');
                    board[a][b]='0';
                    board[tempa][tempb+1]='0';
                    turn=0;
                    tempc='0';
                }
                if(b-tempb>0 && b-tempb<=ld*3)
                {
                    board[a][b+1]='2';
                    score2=score2+(board[a][b]-'0');
                    board[a][b]='0';
                    board[tempa][tempb+1]='0';
                    turn=0;
                    tempc='0';
                }
            }
        }
        lw=0;
        ls=0;
        ld=0;
        la=0;

        for(check=tempa; check>0; check--)
        {
            if(board[check-1][tempb] != '0')
            {
                lw++;
            }
            else
            {
                check=check-1;
                break;
            }
        }
        for(check=tempa; check<y-1; check++)
        {
            if(board[check+1][tempb] != '0')
            {
                ls++;
            }
            else
            {
                check=check+1;
                break;
            }
        }
        for(check=tempb; check>0; check-3)
        {
            if(board[tempa][check-3] != '0')
            {
                la++;
                check=check-3;
            }
            else
            {
                break;
            }
        }
        for(check=tempb; check<x*3-3; check+3)
        {
            if(board[tempa][check+3] != '0')
            {
                ld++;
                check=check+3;
            }
            else
            {
                break;
            }
        }
    }



    if(turn==2*penguins)
    {
        phase=1;
    }
    system("cls");
}

void gameOver()
{
    int n, m;
    int nOutside=0;
    int nBlocked=0;
    int winner;
    int cantMove1=0, cantMove2=0;

    for(n=0; n<y; n++)
    {
        for(m=0; m<x*3+1; m++)
        {
            if(board[n][m]!='0' && m%3==1 && m!=x*3+1)
            {
                if(n==0)
                {
                    nOutside++;
                }
                else
                {
                    if(board[n-1][m-1]=='0')
                    {
                        nBlocked++;
                    }
                }
                if(n==y-1)
                {
                    nOutside++;
                }
                else
                {
                    if(board[n+1][m-1]=='0')
                    {
                        nBlocked++;
                    }
                }
                if(m==1)
                {
                    nOutside++;
                }
                else
                {
                    if(board[n][m-1-3]=='0')
                    {
                        nBlocked++;
                    }
                }
                if(m==x*3-2)
                {
                    nOutside++;
                }
                else
                {
                    if(board[n][m-1+3]=='0')
                    {
                        nBlocked++;
                    }
                }
                if(board[n][m]=='1')
                {
                    if(nOutside+nBlocked==4)
                    {
                        cantMove1++;
                    }
                }
                if(board[n][m]=='2')
                {
                    if(nOutside+nBlocked==4)
                    {
                        cantMove2++;
                    }
                }
                if(cantMove1==penguins)
                {
                    turn=1;
                }
                if(cantMove2==penguins)
                {
                    turn=0;
                }
                if((cantMove1==penguins && cantMove2==penguins) || (cantMove1==penguins && score1<score2) || (cantMove2==penguins && score1>score2))
                {
                    if(score1>score2 && score1!=score2)
                    {
                        winner=1;
                        printf("\n#### Game over! Player%d wins! ####\n\n", winner);
                        end=1;
                    }
                    else if(score1<score2 && score1!=score2)
                    {
                        winner=2;
                        printf("\n#### Game over! Player%d wins! ####\n\n", winner);
                        end=1;
                    }
                    if(score1==score2)
                    {
                        printf("\n#### Game over! Draw! ####\n\n");
                        end=1;
                        
                    }
                }
                nOutside=0, nBlocked=0;
            }
            if(end==1)
            {
            	break;
            }
        }
    }

}

void generate()
{
    char ask;
    printf("Generate new board? y/n\n");
    while(1)
    {
        ask=getch();
        if(ask=='y')
        {
            FILE* file;
            file=fopen("board.txt", "w");
            int c, v, i, j, r;
            char q;
label2:
            system("cls");
            printf("Enter board dimensions\n");
            printf("Horizontal: ");
            scanf("%d", &c);
            printf("Vertical: ");
            scanf("%d", &v);

            if(c<0 || v<0)
            {
                printf("Both values must be greater then 0!\n\n");
                goto label2;
            }

            srand(time(NULL));

            fprintf(file,"%d ", c);
            fprintf(file,"%d\n", v);

            for(i=0; i<v; i++)
            {
                for(j=0; j<c; j++)
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
            system("cls");
            break;
        }
        if(ask=='n')
        {
            system("cls");
            break;
        }
    }
}

void npenguins()
{
    printf("Enter the number of penguins per player: ");
    scanf("%d", &penguins);
    system("cls");
}
