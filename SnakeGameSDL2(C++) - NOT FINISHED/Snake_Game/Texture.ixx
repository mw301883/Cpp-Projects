export module Texture;

import <SDL.h>;
import <SDL_image.h>;
import <string>;
import <SDL_ttf.h>;

export class Texture {
private:
	SDL_Texture* ActualTexture;
	int Width;
	int Height;
public:
	Texture();
	~Texture();
	//Create normal texture from PNG file
	void Create(SDL_Surface* Texture_Surface, SDL_Renderer* Renderer);
	//Create texture from TTF file (text texture)
	bool Create_TTF(SDL_Renderer* Renderer, TTF_Font*& Font, std::string& Text, SDL_Colour& FontColour);
	void Free();
	void Render(const int& x, const int& y, SDL_Renderer* Renderer, SDL_Rect* Clip, const bool& Full_Format);
	int GetWidth();
	int GetHeight();
};