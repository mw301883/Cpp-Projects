import Button;
import Core;
import "SDL.h";
import <stdio.h>;

Button::Button() {}
Button::Button(Texture& Button_Texture_NOT_Clicked, Texture& Button_Texture_Clicked, Texture& Button_Texture_BLACK, SDL_Rect Button_Clip) : Button_Texture_NOT_Clicked(&Button_Texture_NOT_Clicked), Button_Texture_Clicked(&Button_Texture_Clicked), Button_Texture_BLACK(&Button_Texture_BLACK), Button_Clip(Button_Clip),is_Light(true), is_Main_Button(false), Anim_Frames(0), Index(0) {
	this->Position.x = 0;
	this->Position.y = 0;
}
Button::Button(Texture Button_Texture_Animation[CLIPS_ENUM::Main_Buttons_Anim_Count], SDL_Rect Button_Clip, const int& begin, const int& end) : Button_Clip(Button_Clip), is_Light(true), is_Main_Button(true), Anim_Frames(0), Index(0) {
	int j = 0;
	for (int i = begin; i <= end; ++i, ++j) {
		this->Button_Texture_Animation[j] = &Button_Texture_Animation[i];
	}
	this->Position.x = 0;
	this->Position.y = 0;
}

Button::~Button() {
	this->Button_Texture_NOT_Clicked = nullptr;
	this->Button_Texture_Clicked = nullptr;
	this->Button_Texture_BLACK = nullptr;
	for (int i = 0; i < CLIPS_ENUM::Main_Buttons_Anim_Count; ++i) {
		this->Button_Texture_Animation[i] = nullptr;
	}
}

void Button::Check_Event(SDL_Event* Mouse_Event) {
	bool is_Light = false;
	int x, y;
	if (Mouse_Event->type == SDL_MOUSEMOTION || Mouse_Event->type == SDL_MOUSEBUTTONDOWN) {
		SDL_GetMouseState(&x, &y);
		if (this->Position.x > x || this->Position.x + this->Button_Clip.w < x) {
			is_Light = false;
		}
		else if (this->Position.y > y || this->Position.y + this->Button_Clip.h < y) {
			is_Light = false;
		}
		else {
			is_Light = true;
		}
	}
	if (Mouse_Event->type == SDL_MOUSEBUTTONDOWN && is_Light == true) {
		this->is_Clicked = true;
	}
	this->is_Light = is_Light;
}


bool Button::Get_is_Clicked() {
	return this->is_Clicked;
}

void Button::Animation(const int& x, const int& y, SDL_Renderer* Renderer) {
	this->Button_Texture_Animation[this->Index]->Render(x, y, Renderer, &this->Button_Clip, 0);
	if (this->Index < CLIPS_ENUM::Main_Buttons_Anim_Count-1) {
		++this->Index;
	}
	else {
		this->Index = 0;
	}
}

void Button::Reset_is_Clicked() {
	this->is_Clicked = false;
}

void Button::Render(const int& x, const int& y, SDL_Renderer* Renderer) {
	this->Position.x = x;
	this->Position.y = y;
	if (this->is_Main_Button) {
		if (this->is_Light) {
			Animation(x, y , Renderer);
		}
		else {
			this->Index = 0;
			this->Button_Texture_Animation[CLIPS_ENUM::Main_Buttons_Anim_Count-1]->Render(x, y, Renderer, &this->Button_Clip, 0);
		}
	}
	else {
		if (this->is_Light) {
			this->Button_Texture_BLACK->Render(x, y - 10, Renderer, &this->Button_Clip, 0);
			this->Button_Texture_Clicked->Render(x, y, Renderer, &this->Button_Clip, 0);
		}
		else {
			this->Button_Texture_BLACK->Render(x, y - 10, Renderer, &this->Button_Clip, 0);
			this->Button_Texture_NOT_Clicked->Render(x, y, Renderer, &this->Button_Clip, 0);
		}
	}
}