nQueens
=========

This little application was made to solve the n-queen problem. By using SDL it visualizes it's results, but it can also be stripped all of the sdl code and print its results to std::out

Building nQueens
-------------

Make sure you have both SDL and SDL_image (http://www.libsdl.org/). If you have them just run:

	$ g++ -o nQueens main.cpp `sdl-config --cflags --libs` -lSDL_image
	
Have fun!