#pragma once

#include "System.h"
#include "Texture.h"

class Background {
public:
	Background(SDL_Rect Texture_Clips[20]);
	~Background();
	//Render static Background (without scrolling)
	void Render_Static(Texture& Background_Texture, SDL_Renderer* &Renderer);
	//Render scrolling Background
	void Render_Scrolling(Texture& Background_Texture, SDL_Renderer* &Renderer, int& ScrollingXPos);
	//Set Day Texture
	void SetDay();
	//Set Night Texture
	void SetNight();
private:
	SDL_Rect Clip_Day, Clip_Night;
	bool Time_Mode;
	int Counter_Day, Counter_Night;
};