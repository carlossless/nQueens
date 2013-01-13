#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"

int solved_count = 0, step_count = 0;
SDL_Surface *screen = NULL;
SDL_Surface *bqueen = NULL, *wqueen = NULL;

TTF_Font *font = NULL;
SDL_Surface *info = NULL;

int init(int);
int deinit();
void print_barrier(int);
void print_board(int, int*);
void solve(int, int, int*);

int main(int argc, char* args[])
{
	int n = 8;
	if (argc == 2)
		n = (int) (*args[1] - '0');
	int queens[n];
    
    if (init(n) == 0)
	    solve(n, 0, queens);
    
    deinit();
	
    return 0;
}

int init(int n)
{

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
        fprintf(stderr, "SDL could not init\r\n");
	    return -1;	
	}
	
	screen = SDL_SetVideoMode( 16*(n+1),16*(n+2),32,SDL_SWSURFACE);
	if (screen == NULL)
    {
        fprintf(stderr, "Screen could not init\r\n");
        return -2;
    }

    if (TTF_Init() < 0)
    {
        fprintf(stderr, "SDL_ttf could not init\r\n");
        return -3;
    }

    wqueen = IMG_Load("wqueen.png");
    bqueen = IMG_Load("bqueen.png");
    if (wqueen == NULL || bqueen == NULL)
    {
        fprintf(stderr, "Queen image could not be loaded\r\n");
        return -4;
    }
    
    font = TTF_OpenFont("visitor1.ttf",10);
    if (font == NULL)
    {
    	fprintf(stderr, "Font couldn't be loaded");
    	return -5;
    }

    SDL_WM_SetCaption("nQueens", NULL);

    return 0;
}

int deinit()
{
	SDL_FreeSurface(bqueen);
	SDL_FreeSurface(wqueen);
	SDL_FreeSurface(info);
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

void print_info(char* text, int x, int y)
{
	info = TTF_RenderText_Solid(font, text, (SDL_Color) {0xFF,0xFF,0xFF});
	SDL_Rect block = {x, y, screen->clip_rect.w, 10};
	SDL_BlitSurface(info, NULL, screen, &block);
}

void print_board(int n, int *queens)
{
	char string_buffer[50];

	SDL_FillRect(screen, NULL, 0x000000FF);

	printf("\nNr %d:\n", step_count);
	for (int y = 0; y < n; y++)
		printf(" %d",queens[y]+1);
	putchar('\n');
	
	sprintf(string_buffer,"Step: %d",step_count + solved_count);
	print_info(string_buffer,8,6);
    sprintf(string_buffer,"Solved: %d",solved_count);
    print_info(string_buffer,8,14);
		
	print_barrier(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) {
			SDL_Rect block = {(16*j)+8,(16*i)+24,16,16 };
			printf("|%c",i == queens[j] ? 'Q' : ((i + j) & 1) ? ' ' : '#');
			SDL_FillRect(screen, &block, ((i + j) & 1) ? 0x000000FF : 0xFFFFFFFF);
			if (i == queens[j]) SDL_BlitSurface(((i + j) & 1) ? wqueen : bqueen, NULL, screen, &block);
		}
		printf("|\n");
	}
	print_barrier(n);

	SDL_Flip(screen);

	//sprintf(string_buffer,"queens-%d.bmp",count);
	//SDL_SaveBMP(screen,filename);
	SDL_Delay(50);
}

void solve(int n, int col, int *queens)
{
	if (col == n) {
		solved_count++;
		print_board(n,queens);
		SDL_Delay(1000);
		return;
	}
 
	for (int i = 0, j = 0; i < n; i++) {
		for (j = 0; j < col && !(queens[j] == i || abs(queens[j] - i) == col - j); j++);
		
		if (j < col) continue;
		
		for (int y=col; y<n; y++) 
			queens[y] = -1;
			
		step_count++;

#ifdef PRNT_STEPS
		print_board(n,queens);
#endif
		
		queens[col] = i;
		solve(n, col + 1, queens);
	}
}
