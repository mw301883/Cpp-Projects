#include "Background.h"
#include <iostream>

Background::Background(SDL_Rect Texture_Clips[20]) : Clip_Day(Texture_Clips[CLIP_BACKGROUND_DAY]), Clip_Night(Texture_Clips[CLIP_BACKGROUND_NIGHT]), Time_Mode(true), Counter_Day(10), Counter_Night(10) {}

Background::~Background() {}

void Background::Render_Static(Texture& Background_Texture, SDL_Renderer* &Renderer) {
	if (this->Time_Mode == true) {
		Background_Texture.Render(0, 0, Renderer, &this->Clip_Day);
	}
	else {
		Background_Texture.Render(0, 0, Renderer, &this->Clip_Night);
	}
}

void Background::Render_Scrolling(Texture& Background_Texture, SDL_Renderer* &Renderer, int& ScrollingXPos) {
	if (this->Time_Mode == true) {
		Background_Texture.Render(ScrollingXPos - 360, 0, Renderer, &this->Clip_Day);
		Background_Texture.Render(ScrollingXPos, 0, Renderer, &this->Clip_Day);
		if (ScrollingXPos == 0) {
			ScrollingXPos = 360;
		}
		if (this->Counter_Day == 0) {
			--ScrollingXPos;
			this->Counter_Day = 10;
		}
		this->Counter_Day = this->Counter_Day - 1;
	}
	else {
		Background_Texture.Render(ScrollingXPos - 360, 0, Renderer, &this->Clip_Night);
		Background_Texture.Render(ScrollingXPos, 0, Renderer, &this->Clip_Night);
		if (ScrollingXPos == 0) {
			ScrollingXPos = 360;
		}
		if (this->Counter_Night == 0) {
			--ScrollingXPos;
			this->Counter_Night = 10;
		}
		this->Counter_Night = this->Counter_Night - 1;
	}
}

void Background::SetDay() {
	this->Time_Mode = true;
}

void Background::SetNight() {
	this->Time_Mode = false;
}

