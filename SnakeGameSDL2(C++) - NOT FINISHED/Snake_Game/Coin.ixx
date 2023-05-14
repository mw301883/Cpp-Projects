export module Coin;

import Game_Object;
import Texture;
import Core;

export namespace COIN_ENUM {
	enum {
		COIN_1, 
		COIN_2, 
		COIN_3, 
		COIN_4, 
		COIN_5, 
		COIN_6,
		TOTAL
	};
}

export class Coin : public Game_Object {
private:
	Texture* Coin_Texture[COIN_ENUM::TOTAL];
	SDL_Rect Coin_Clips[COIN_ENUM::TOTAL];
	int PosX, PosY, AnimPosX, AnimPosY;
	static int Anim_Int;
	bool is_Eaten, is_Start;
	void Set_New_Pos();
	void Set_Anim_Pos();
	void Get_Animation(SDL_Renderer* Renderer);

public:
	Coin();
	Coin(Texture Game_Texture[SURFACES_TEXTURES_ENUM::TOTAL], SDL_Rect Game_Clips[CLIPS_ENUM::TOTAL]);
	~Coin();
	virtual void Render(SDL_Renderer* Renderer, const int& x = 0, const int& y = 0) override;
	virtual void Interaction(Snake& Snake_Obj) override;
};

int Coin::Anim_Int = 0;