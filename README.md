nQueens
=========

This little application was made to solve the n-queen problem. By using SDL it visualizes it's results, but it can also be stripped all of the sdl code and print its results to std::out

Building nQueens
-------------

Make sure you have SDL, SDL_image and SDL_ttf installed (http://www.libsdl.org/). If you have them just run:

	$ gcc -std=c99 -o nQueens main.c `sdl-config --cflags --libs` -lSDL_image -lSDL_ttf -D PRNT_STEPS
	
Have fun!