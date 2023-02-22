#include "System.h"
#include "Button.h"

Button::Button() : Dark(), Light(), isLight(true), isClicked(false) {
	this->Position.x = 0;
	this->Position.y = 0;
}

Button::~Button() { }

void Button::Set_Params(SDL_Rect Dark, SDL_Rect Light, int x, int y) {
	this->Dark = Dark;
	this->Light = Light;
	this->Position.x = x;
	this->Position.y = y;
}

void Button::Render(Texture& Button_Texture, SDL_Renderer* Renderer) {
	if (this->isLight) {
		Button_Texture.Render(this->Position.x, this->Position.y, Renderer, &this->Light);
	}
	else {
		Button_Texture.Render(this->Position.x, this->Position.y, Renderer, &this->Dark);
	}
}

void Button::Check_Event(SDL_Event* Mouse_Event) {
	bool isLight = false;
	int x, y;
	if (Mouse_Event->type == SDL_MOUSEMOTION || Mouse_Event->type == SDL_MOUSEBUTTONDOWN) {
		SDL_GetMouseState(&x, &y);

		if (this->Position.x > x || this->Position.x + this->Dark.w < x) {
			isLight = false;
		}
		else if (this->Position.y > y || this->Position.y + this->Dark.h < y) {
			isLight = false;
		}
		else {
			isLight = true;
		}
	}
	if (Mouse_Event->type == SDL_MOUSEBUTTONDOWN && isLight == true) {
		this->isClicked = true;
	}
	
	this->isLight = isLight;
}

bool Button::GetisClicked() {
	return this->isClicked;
}

void Button::ResetisCliced() {
	this->isClicked = false;
}