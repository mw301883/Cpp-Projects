#include "Selector.h"

Selector::Selector() : isClicked(false) {
	Set_Clip(this->Position, 0, 0, 0, 0);
}

Selector::~Selector() { }

void Selector::Set_Selector(int x, int y, int w, int h) {
	Set_Clip(this->Position, x, y, w, h);
}

void Selector::Action(SDL_Event* MouseEvent) {
	int x, y;
	if (MouseEvent->type == SDL_MOUSEBUTTONDOWN) {
		SDL_GetMouseState(&x, &y);
		if (this->Position.x <= x && this->Position.x + this->Position.w >= x && this->Position.y <= y && this->Position.y + this->Position.h >= y) {
			if (!this->isClicked) {
				this->isClicked = true;
			}
			else {
				this->isClicked = false;
			}
		}
	}
}

bool Selector::GetisClicked() {
	return this->isClicked;
}