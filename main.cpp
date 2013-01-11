//Karolis Stasaitis IF-1/7
//7 Uzdavinys: Valdoves

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h> 

int count = 0;
SDL_Surface* screen = NULL;
SDL_Surface* queen = NULL;

void print_barrier(int);
void solve(int, int, int*);
void print_board(int, int*);

int main(int argc, char* args[])
{
	int n = 8;
	int queens[n];

	SDL_Init( SDL_INIT_EVERYTHING );
	
	screen = SDL_SetVideoMode( 16*n,16*n,32,SDL_SWSURFACE);
	queen = IMG_Load("queen.png");	

	solve(n, 0, queens);
	
	SDL_FreeSurface(queen);
	SDL_Quit();

	return 0;
}

void print_barrier(int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("+-");
	}
	printf("+\n");
}

void print_board(int n, int *queens)
{
	printf("\nNr %d:\n", ++count);
	for (int y = 0; y < n; y++)
		printf(" %d",queens[y]+1);
	putchar('\n');
		
	print_barrier(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) {
			SDL_Rect block;
			block.x = 16*j;
			block.y = 16*i;
			block.w = 16;
			block.h = 16;
			printf("|%c",i == queens[j] ? 'Q' : ((i + j) & 1) ? ' ' : '#');
			SDL_FillRect(screen, &block, ((i + j) & 1) ? 0x000000FF : 0xFFFFFFFF);
			if (i == queens[j]) SDL_BlitSurface(queen,NULL,screen,&block);
		}
		printf("|\n");
	}
	print_barrier(n);

	SDL_Flip(screen);

	char filename[50];
	sprintf(filename,"queens-%d.bmp",count);
	SDL_SaveBMP(screen,filename);
}

void solve(int n, int col, int *queens)
{
	if (col == n) {
		print_board(n,queens);
		return;
	}
 
	for (int i = 0, j = 0; i < n; i++) {
		for (j = 0; j < col && !(queens[j] == i || abs(queens[j] - i) == col - j); j++);
		
		if (j < col) continue;
		
		for (int y=col; y<n; y++) queens[y] = -1;
		
		queens[col] = i;
		solve(n, col + 1, queens);
	}
}
