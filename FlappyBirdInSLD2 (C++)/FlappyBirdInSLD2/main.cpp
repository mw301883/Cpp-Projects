#include "SDL.h"
#include "SDL_image.h"
#include "System.h"
#include <string>
#include <iostream>

//Design pattern - Composit
int main(int argc, char* argv[]) {

	System Game_System;

	Game_System.Play();

	return 0;
}