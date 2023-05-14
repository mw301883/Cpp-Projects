import Coin;

import Texture;
import Core;

Coin::Coin() : PosX(0), PosY(0), AnimPosX(0), AnimPosY(0), is_Eaten(false), is_Start(true) {}

Coin::Coin(Texture Game_Texture[SURFACES_TEXTURES_ENUM::TOTAL], SDL_Rect Game_Clips[CLIPS_ENUM::TOTAL])
	: PosX(0), PosY(0), AnimPosX(0), AnimPosY(0), is_Eaten(false), is_Start(true) {
	int j = 0;
	for (int i = SURFACES_TEXTURES_ENUM::COIN_1; i <= SURFACES_TEXTURES_ENUM::COIN_6; ++i, ++j) {
		this->Coin_Texture[j] = &Game_Texture[i];
	}
	j = 0;
	for(int i = CLIPS_ENUM::COIN_1; i <= CLIPS_ENUM::COIN_6; ++i, ++j){
		this->Coin_Clips[j] = Game_Clips[i];
	}
}

Coin::~Coin() {}

void Coin::Render(SDL_Renderer* Renderer, const int& x, const int& y) {
	if (this->is_Start) { //mozliwosc ustawienia pierwszego rederowania zgodnie z parametrami
		this->PosX = x;
		this->PosY = y;
	}
	if (is_Eaten) {
		Get_Animation(Renderer);
	}
	switch (this->Anim_Int) {
	case COIN_ENUM::COIN_1:
		this->Coin_Texture[COIN_ENUM::COIN_1]->Render(this->PosX, this->PosY, Renderer, &this->Coin_Clips[COIN_ENUM::COIN_1], 1);
		break;
	case COIN_ENUM::COIN_2:
		this->Coin_Texture[COIN_ENUM::COIN_2]->Render(this->PosX, this->PosY, Renderer, &this->Coin_Clips[COIN_ENUM::COIN_2], 1);
		break;
	case COIN_ENUM::COIN_3:
		this->Coin_Texture[COIN_ENUM::COIN_3]->Render(this->PosX, this->PosY, Renderer, &this->Coin_Clips[COIN_ENUM::COIN_3], 1);
		break;
	case COIN_ENUM::COIN_4:
		this->Coin_Texture[COIN_ENUM::COIN_4]->Render(this->PosX, this->PosY, Renderer, &this->Coin_Clips[COIN_ENUM::COIN_4], 1);
		break;
	case COIN_ENUM::COIN_5:
		this->Coin_Texture[COIN_ENUM::COIN_5]->Render(this->PosX, this->PosY, Renderer, &this->Coin_Clips[COIN_ENUM::COIN_5], 1);
		break;
	case COIN_ENUM::COIN_6:
		this->Coin_Texture[COIN_ENUM::COIN_6]->Render(this->PosX, this->PosY, Renderer, &this->Coin_Clips[COIN_ENUM::COIN_6], 1);
		break;
	default:
		this->Coin_Texture[COIN_ENUM::COIN_6]->Render(this->PosX, this->PosY, Renderer, &this->Coin_Clips[COIN_ENUM::COIN_6], 1);
		this->Anim_Int = -1;
		break;
	}
	++this->Anim_Int;
}

void Coin::Interaction(Snake& Snake_Obj) {
	if ((Snake_Obj.Get_PosX() + 20 >= this->PosX && Snake_Obj.Get_PosX() + 20 <= this->PosX + 64)
		&& (Snake_Obj.Get_PosY() + 20 >= this->PosY && Snake_Obj.Get_PosY() + 20 <= this->PosY + 64)) {
		Snake_Obj.Add_Score();
		Set_Anim_Pos();
		Set_New_Pos();
		this->is_Eaten = true;
		this->is_Start = false;
	}
	else {
		this->is_Eaten = false;
	}
}

void Coin::Set_New_Pos() {
	this->PosX = Get_Random_Integer(200, 1800);
	this->PosY = Get_Random_Integer(200, 900);
}

void Coin::Set_Anim_Pos() {
	this->AnimPosX = this->PosX;
	this->AnimPosY = this->PosY;
}

void Coin::Get_Animation(SDL_Renderer* Renderer) {
	for (int i = 0; i < 1000; ++i) {
		switch (Get_Random_Integer(1, 5)) {
		case 1:
			SDL_SetRenderDrawColor(Renderer, 255, 255, 224, 255);
			break;
		case 2:
			SDL_SetRenderDrawColor(Renderer, 250, 250, 210, 255);
			break;
		case 3:
			SDL_SetRenderDrawColor(Renderer, 255, 255, 0, 255);
			break;
		case 4:
			SDL_SetRenderDrawColor(Renderer, 240, 230, 140, 255);
			break;
		case 5:
			SDL_SetRenderDrawColor(Renderer, 255, 255, 102, 255);
			break;
		}
		int x = Get_Random_Integer(Get_Random_Integer(0, 31), Get_Random_Integer(32, 64)) + this->AnimPosX;
		int y = Get_Random_Integer(Get_Random_Integer(0, 31), Get_Random_Integer(32, 64)) + this->AnimPosY;
		SDL_RenderDrawPoint(Renderer, x, y);
	}
}