#pragma once

#include "System.h"
#include "Texture.h"
#include "SDL.h"
#include "SDL_image.h"

//Represent options avaible in main menu game.
class Button {
public:
	Button();
	~Button();
	void Set_Params(SDL_Rect Dark, SDL_Rect Light, int x, int y);
	void Render(Texture& Button_Texture, SDL_Renderer* Renderer);
	void Check_Event(SDL_Event* Mouse_Event);
	bool GetisClicked();
	void ResetisCliced();
private:
	SDL_Rect Dark, Light;
	SDL_Point Position;
	bool isLight, isClicked;
};
