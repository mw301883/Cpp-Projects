#include "Pipe.h"
#include <random>
#include <iostream>

Pipe::Pipe() : Pipe_Current(), Double_Collision_Area(false), isCollision(false), X(-125), Y(0), Distance_Out_Screen(125), Counter(10), Const_Counter(8), ColliderHight_Up(0),  ColliderHight_Down(0) {}

Pipe::~Pipe() {}

void Pipe::Render(Texture& Pipe_Texture, SDL_Renderer*& Renderer) {
	Pipe_Texture.Render(this->X, this->Y, Renderer, &this->Pipe_Current);
}

void Pipe::Move(int& Window_W, bool& CurrentPipe) {
	if (!this->isCollision) {
		if (CurrentPipe) {
			CurrentPipe = false;
		}

		if (this->X == 0 - this->Distance_Out_Screen) {
			this->X = 420;
			if (!CurrentPipe) {
				CurrentPipe = true;
			}
		}

		if (this->Counter == 0) {
			this->X = this->X - 1;
			this->Counter = this->Const_Counter;
		}
		this->Counter = this->Counter - 1;
	}
}

void Pipe::Set_is_Double_Collision_area(bool is_Double_Collision_Area) {
	this->Double_Collision_Area = is_Double_Collision_Area;
}

void Pipe::SetCollision() {
	this->isCollision = true;
}

void Pipe::ResetPipe() {
	this->isCollision = false;
	this->X = 360;
	this->Counter = 2;
}

void Pipe::Set_Clip(SDL_Rect Clip) {
	this->Pipe_Current = Clip;
}

void Pipe::Set_ColliderHight_Up(int ColliderHight) {
	this->ColliderHight_Up = ColliderHight;
}

void Pipe::Set_ColliderHight_Down(int ColliderHight) {
	this->ColliderHight_Down = ColliderHight;
}

int Pipe::GetX() {
	return this->X;
}

int Pipe::GetY() {
	return this->Y;
}

int Pipe::Get_ColliderHight_Up() {
	return this->ColliderHight_Up;
}

int Pipe::Get_ColliderHight_Down() {
	return this->ColliderHight_Down;
}

bool Pipe::Get_is_Double_Collision_Area() {
	return this->Double_Collision_Area;
}

void Game_Pipe_Init(SDL_Rect Clips[20], Pipe Pipes_Unset[PIPE_TOTAL]) {
	Pipes_Unset[PIPE_UP_HIGH].Set_Clip(Clips[CLIP_PIPE_UP_HIGH]);
	Pipes_Unset[PIPE_UP_HIGH].Set_is_Double_Collision_area(false);
	Pipes_Unset[PIPE_UP_HIGH].Set_ColliderHight_Up(408);
	Pipes_Unset[PIPE_UP_HIGH].Set_ColliderHight_Down(0);


	Pipes_Unset[PIPE_UP_MEDIUM].Set_Clip(Clips[CLIP_PIPE_UP_MEDIUM]);
	Pipes_Unset[PIPE_UP_MEDIUM].Set_is_Double_Collision_area(false);
	Pipes_Unset[PIPE_UP_MEDIUM].Set_ColliderHight_Up(303);
	Pipes_Unset[PIPE_UP_MEDIUM].Set_ColliderHight_Down(0);


	Pipes_Unset[PIPE_UP_LOW].Set_Clip(Clips[CLIP_PIPE_UP_LOW]);
	Pipes_Unset[PIPE_UP_LOW].Set_is_Double_Collision_area(false);
	Pipes_Unset[PIPE_UP_LOW].Set_ColliderHight_Up(45);
	Pipes_Unset[PIPE_UP_LOW].Set_ColliderHight_Down(0);


	Pipes_Unset[PIPE_DOWN_HIGH].Set_Clip(Clips[CLIP_PIPE_DOWN_HIGH]);
	Pipes_Unset[PIPE_DOWN_HIGH].Set_is_Double_Collision_area(false);
	Pipes_Unset[PIPE_DOWN_HIGH].Set_ColliderHight_Up(0);
	Pipes_Unset[PIPE_DOWN_HIGH].Set_ColliderHight_Down(245);


	Pipes_Unset[PIPE_DOWN_MEDIUM].Set_Clip(Clips[CLIP_PIPE_DOWN_MEDIUM]);
	Pipes_Unset[PIPE_DOWN_MEDIUM].Set_is_Double_Collision_area(false);
	Pipes_Unset[PIPE_DOWN_MEDIUM].Set_ColliderHight_Up(0);
	Pipes_Unset[PIPE_DOWN_MEDIUM].Set_ColliderHight_Down(375);


	Pipes_Unset[PIPE_DOWN_LOW].Set_Clip(Clips[CLIP_PIPE_DOWN_LOW]);
	Pipes_Unset[PIPE_DOWN_LOW].Set_is_Double_Collision_area(false);
	Pipes_Unset[PIPE_DOWN_LOW].Set_ColliderHight_Up(0);
	Pipes_Unset[PIPE_DOWN_LOW].Set_ColliderHight_Down(470);

	
	Pipes_Unset[PIPE_GAP_LOW].Set_Clip(Clips[CLIP_PIPE_GAP_LOW]);
	Pipes_Unset[PIPE_GAP_LOW].Set_is_Double_Collision_area(true);
	Pipes_Unset[PIPE_GAP_LOW].Set_ColliderHight_Up(390);;
	Pipes_Unset[PIPE_GAP_LOW].Set_ColliderHight_Down(545);;


	Pipes_Unset[PIPE_GAP_HIGH].Set_Clip(Clips[CLIP_PIPE_GAP_HIGH]);
	Pipes_Unset[PIPE_GAP_HIGH].Set_is_Double_Collision_area(true);
	Pipes_Unset[PIPE_GAP_HIGH].Set_ColliderHight_Up(225);;
	Pipes_Unset[PIPE_GAP_HIGH].Set_ColliderHight_Down(375);;
	
}

int Random_Index() {
	std::random_device device;
	std::default_random_engine engine(device());
	std::uniform_int_distribution<int> limit(0, PIPE_TOTAL - 1);

	return limit(engine);
}

void Pipe::Set_Const_Counter(const int& New_Counter) {
	this->Const_Counter = New_Counter;
}