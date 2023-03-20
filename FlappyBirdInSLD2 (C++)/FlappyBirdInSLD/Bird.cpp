#include "Bird.h"

#include <iostream>

Bird::Bird(SDL_Rect Clips[20]) : isDead(false), Motion(true), Collision(false), Alive_Up(Clips[CLIP_BIRD_MOVE_UP]), Alive_Down(Clips[CLIP_BIRD_MOVE_DOWN]), Dead_Up(Clips[CLIP_BIRD_DEAD_UP]), Dead_Down(Clips[CLIP_BIRD_DEAD_DOWN]), X(10), Y(250), VelY(0), Height(89), Counter(100) {}

Bird::~Bird() {}

void Bird::Render(Texture& Bird_Texture, SDL_Renderer*& Renderer) {
	if (!this->isDead) {
		if (this->Motion) {
			Bird_Texture.Render(this->X, this->Y, Renderer, &this->Alive_Up);
			if (this->Counter == 0) {
				this->Motion = false;
				this->Counter = 100;
			}
		}
		else {
			Bird_Texture.Render(this->X, this->Y, Renderer, &this->Alive_Down);
			if (this->Counter == 0) {
				this->Motion = true;
				this->Counter = 100;
			}
		}
	}
	else {
		if (this->Motion) {
			Bird_Texture.Render(this->X, this->Y, Renderer, &this->Dead_Up);
			if (this->Counter == 0) {
				this->Motion = false;
				this->Counter = 100;
			}
		}
		else {
			Bird_Texture.Render(this->X, this->Y, Renderer, &this->Dead_Down);
			if (this->Counter == 0) {
				this->Motion = true;
				this->Counter = 100;
			}
		}
	}
	this->Counter = this->Counter - 1;
}

void Bird::Move(int& Window_H) {
	if (this->Counter % 2 == 0) {
		this->Y = this->Y - this->VelY;
	}
	if (!this->isDead) {
		if (this->Y < 0) {
			this->Y = this->Y + this->VelY;
		}
		else if (this->Y + this->Height > Window_H) {
			this->Y = this->Y + this->VelY;
		}
	}
}

void Bird::CheckEvent(SDL_Event* Mouse_Event) {
	if (!this->isDead) {
		if (Mouse_Event->type == SDL_KEYDOWN && Mouse_Event->key.repeat == 0) {
			if (Mouse_Event->key.keysym.sym == SDLK_SPACE) {
				this->VelY = 1;
			}
		}
		else if (Mouse_Event->type == SDL_KEYUP && Mouse_Event->key.repeat == 0) {
			if (Mouse_Event->key.keysym.sym == SDLK_SPACE) {
				this->VelY = -1;
			}
		}
	}
	else {
		this->VelY = 1;
	}
}

bool Bird::Collision_Detection(int PipeX, int PipeUpHeight, int PipeDownHeight, bool isDoublePipe) {
	int Bird_PosX_Up{ this->X + 40};
	int Bird_PosY_Down{ this->Y + 40 };

	if (isDoublePipe) {
		if (Bird_PosX_Up != PipeX || Bird_PosY_Down >= PipeUpHeight && Bird_PosY_Down <= PipeDownHeight) {
			return false;
		}
		else {
			this->isDead = true;
			return true;
		}
	}

	if (Bird_PosX_Up != PipeX || this->Y >= PipeUpHeight && PipeDownHeight == 0) {
		return false;
	}
	else if (Bird_PosX_Up != PipeX || Bird_PosY_Down <= PipeDownHeight && PipeUpHeight == 0){
		return false;
	}
	this->isDead = true;
	return true;
}

//The current game is about to end when the Bird will reach special Y position after hitting the Pipe (Up or Down position).
bool Bird::is_End(bool& EndGame) {
	if (this->Y == 720 || this->Y == -120) {
		EndGame = true;
		return true;
	}
	else {
		return false;
	}
}

void Bird::Reset_Bird() {
	this->Y = 250;
	this->Counter = 100;
	this->isDead = false;
}