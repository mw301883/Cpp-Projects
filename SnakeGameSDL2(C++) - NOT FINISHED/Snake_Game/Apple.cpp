import Apple;
import Texture;
import Core;

Apple::Apple() : PosX(0), PosY(0), AnimPosX(0), AnimPosY(0), Anim_UP_DN(true), is_Eaten(false), is_Start(true) {}

Apple::Apple(Texture Game_Texture[SURFACES_TEXTURES_ENUM::TOTAL], SDL_Rect Game_Clips[CLIPS_ENUM::TOTAL])
	: Apple_Texture(&Game_Texture[SURFACES_TEXTURES_ENUM::APPLE]), Apple_Clip(Game_Clips[CLIPS_ENUM::APPLE]), 
	PosX(0), PosY(0), AnimPosX(0), AnimPosY(0), Anim_UP_DN(true), is_Eaten(false), is_Start(true) {}

Apple::~Apple() {}

void Apple::Render(SDL_Renderer* Renderer, const int& x, const int& y) {
	if (this->is_Start) { //mozliwosc ustawienia pierwszego rederowania zgodnie z parametrami
		this->PosX = x;
		this->PosY = y;
	}
	if(is_Eaten) {
		Get_Animation(Renderer);
	}
	Animation();
	this->Apple_Texture->Render(this->PosX, this->PosY, Renderer, &this->Apple_Clip, 0);
}

void Apple::Interaction(Snake& Snake_Obj) {
	if ((Snake_Obj.Get_PosX() + 20 >= this->PosX && Snake_Obj.Get_PosX() + 20 <= this->PosX + 64)
		&& (Snake_Obj.Get_PosY() + 20 >= this->PosY && Snake_Obj.Get_PosY() + 20 <= this->PosY + 64)) {
		Snake_Obj.Grow();
		Set_Anim_Pos();
		Set_New_Pos();
		this->is_Eaten = true;
		this->is_Start = false;
	}
	else {
		this->is_Eaten = false;
	}
}

void Apple::Animation() {
	if (this->Anim_UP_DN) {
		++this->Anim_Int;
		++this->PosY;
		if (this->Anim_Int == 5)
			this->Anim_UP_DN = false;
	}
	else {
		--this->Anim_Int;
		--this->PosY;
		if (this->Anim_Int == 0)
			this->Anim_UP_DN = true;
	}
}

void Apple::Set_New_Pos() {
	this->PosX = Get_Random_Integer(200, 1800);
	this->PosY = Get_Random_Integer(200, 900);
}

void Apple::Set_Anim_Pos() {
	this->AnimPosX = this->PosX;
	this->AnimPosY = this->PosY;
}

void Apple::Get_Animation(SDL_Renderer* Renderer) {
	for (int i = 0; i < 1000; ++i) {
		switch (Get_Random_Integer(1, 5)) {
		case 1:
			SDL_SetRenderDrawColor(Renderer, 69, 75, 27, 255);
			break;
		case 2:
			SDL_SetRenderDrawColor(Renderer, 170, 255, 0, 255);
			break;
		case 3:
			SDL_SetRenderDrawColor(Renderer, 175, 225, 175, 255);
			break;
		case 4:
			SDL_SetRenderDrawColor(Renderer, 9, 121, 105, 255);
			break;
		case 5:
			SDL_SetRenderDrawColor(Renderer, 80, 200, 120, 255);
			break;
		}
		int x = Get_Random_Integer(Get_Random_Integer(0, 31), Get_Random_Integer(32, 64)) + this->AnimPosX;
		int y = Get_Random_Integer(Get_Random_Integer(0, 31), Get_Random_Integer(32, 64)) + this->AnimPosY;
		SDL_RenderDrawPoint(Renderer, x, y);
	}
}