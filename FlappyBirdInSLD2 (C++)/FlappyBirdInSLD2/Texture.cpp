#include "Texture.h"
#include <iostream>

Texture::Texture() : ActualTexture(nullptr), Width(0), Height(0) {}

Texture::~Texture() {
	Free();
}

void Texture::Create(SDL_Surface* Texture_Surface, SDL_Renderer* Renderer) {
	Free();
	SDL_Texture* New_Texture = nullptr;
	if (Texture_Surface == nullptr) {
		std::cout << "\nUError - unable to load surface : " << SDL_GetError;
	}
	else {
		SDL_SetColorKey(Texture_Surface, SDL_TRUE, SDL_MapRGB(Texture_Surface->format, 153, 217, 234));
		New_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
		if (New_Texture == nullptr) {
			std::cout << "\nUError - unable to create Texture from loaded surface : " << SDL_GetError;
		}
		else {
			this->Width = Texture_Surface->w;
			this->Height = Texture_Surface->h;
		}
		this->ActualTexture = New_Texture;
	}
}

bool Texture::Create_TTF(SDL_Renderer* Renderer, TTF_Font*& Font, std::string& Text, SDL_Colour& FontColour) {
	Free();
	bool success = false;
	SDL_Texture* New_Texture = nullptr;
	SDL_Surface* TextSurface = TTF_RenderText_Solid(Font, Text.c_str(), FontColour);
	if (TextSurface == nullptr) {
		std::cout << "\nError - unable to create Text Surface : " << TTF_GetError;
	}
	else {
		New_Texture = SDL_CreateTextureFromSurface(Renderer, TextSurface);
		if(New_Texture == nullptr) {
			std::cout << "\nUError - unable to create Text Texture from loaded surface : " << TTF_GetError;
		}
		else {
			this->Width = TextSurface->w;
			this->Height = TextSurface->h;
			success = true;
		}
		this->ActualTexture = New_Texture;
	}
	SDL_FreeSurface(TextSurface);
	return success;
}

void Texture::Free() {
	if (this->ActualTexture != nullptr) {
		SDL_DestroyTexture(this->ActualTexture);
		this->ActualTexture = nullptr;
		this->Width = 0;
		this->Height = 0;
	}
}

void Texture::Render(int x, int y, SDL_Renderer* Renderer, SDL_Rect* Clip) {
	SDL_Rect RenderTexture{ x, y, this->Width, this->Height };

	if (Clip != nullptr) {
		RenderTexture.w = Clip->w;
		RenderTexture.h = Clip->h;
	}

	SDL_RenderCopy(Renderer, this->ActualTexture, Clip, &RenderTexture);
}

int Texture::GetWidth() {
	return this->Width;
}

int Texture::GetHeight() {
	return this->Height;
}