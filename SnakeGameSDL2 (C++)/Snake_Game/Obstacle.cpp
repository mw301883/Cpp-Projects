import Obstacle;
import Texture;
import Core;

Obstacle::Obstacle() : PosX(0), PosY(0), AnimPosX(0), AnimPosY(0), is_Eaten(false), is_Start(true) {
	this->Collision.Load_Chunk(PATHS::COLLISION_SOUND_PATH);
}

Obstacle::Obstacle(Texture Game_Texture[SURFACES_TEXTURES_ENUM::TOTAL], SDL_Rect Game_Clips[CLIPS_ENUM::TOTAL])
	: Obstacle_Texture(&Game_Texture[SURFACES_TEXTURES_ENUM::OBSTACLE]), Obstacle_Clip(Game_Clips[CLIPS_ENUM::OBSTACLE]),
	PosX(0), PosY(0), AnimPosX(0), AnimPosY(0), is_Eaten(false), is_Start(true) {
	this->Collision.Load_Chunk(PATHS::COLLISION_SOUND_PATH);
}

Obstacle::~Obstacle() {}

void Obstacle::Render(SDL_Renderer* Renderer, const int& x, const int& y) {
	if (this->is_Start) { //mozliwosc ustawienia pierwszego rederowania zgodnie z parametrami
		this->PosX = x;
		this->PosY = y;
	}
	if (is_Eaten) {
		Get_Animation(Renderer);
	}
	this->Obstacle_Texture->Render(this->PosX, this->PosY, Renderer, &this->Obstacle_Clip, 0);
}

void Obstacle::Interaction(Snake& Snake_Obj) {
	if ((Snake_Obj.Get_PosX() + 20 >= this->PosX && Snake_Obj.Get_PosX() + 20 <= this->PosX + 64)
		&& (Snake_Obj.Get_PosY() + 20 >= this->PosY && Snake_Obj.Get_PosY() + 20 <= this->PosY + 64)) {
		Snake_Obj.Minus_Score();
		Set_Anim_Pos();
		Set_New_Pos();
		this->is_Eaten = true;
		this->is_Start = false;
		this->Collision.Play_Chunk();
	}
	else {
		this->is_Eaten = false;
	}
}

void Obstacle::Set_New_Pos() {
	this->PosX = Get_Random_Integer(200, 1800);
	this->PosY = Get_Random_Integer(200, 900);
}

void Obstacle::Set_Anim_Pos() {
	this->AnimPosX = this->PosX;
	this->AnimPosY = this->PosY;
}

void Obstacle::Get_Animation(SDL_Renderer* Renderer) {
	for (int i = 0; i < 1000; ++i) {
		switch (Get_Random_Integer(1, 5)) {
		case 1:
			SDL_SetRenderDrawColor(Renderer, 128, 0, 0, 255);
			break;
		case 2:
			SDL_SetRenderDrawColor(Renderer, 165, 42, 42, 255);
			break;
		case 3:
			SDL_SetRenderDrawColor(Renderer, 139, 69, 19, 255);
			break;
		case 4:
			SDL_SetRenderDrawColor(Renderer, 160, 82, 45, 255);
			break;
		case 5:
			SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);
			break;
		}
		int x = Get_Random_Integer(Get_Random_Integer(0, 31), Get_Random_Integer(32, 64)) + this->AnimPosX;
		int y = Get_Random_Integer(Get_Random_Integer(0, 31), Get_Random_Integer(32, 64)) + this->AnimPosY;
		SDL_RenderDrawPoint(Renderer, x, y);
	}
}