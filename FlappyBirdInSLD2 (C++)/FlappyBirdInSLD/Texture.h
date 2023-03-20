#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include "SDL_ttf.h"

class Texture {
public:
	Texture();
	~Texture();
	//Create normal texture from PNG file
	void Create(SDL_Surface* Texture_Surface, SDL_Renderer* Renderer);
	//Create texture from TTF file (text texture)
	bool Create_TTF(SDL_Renderer* Renderer, TTF_Font*& Font, std::string& Text, SDL_Colour& FontColour);
	void Free();
	void Render(int x, int y, SDL_Renderer* Renderer, SDL_Rect* Clip = nullptr);
	int GetWidth();
	int GetHeight();
private:
	SDL_Texture* ActualTexture;
	int Width;
	int Height;
};