export module Apple;

import Texture;
import Game_Object;
import Core;

export class Apple : public Game_Object {
private:
	Texture* Apple_Texture;
	SDL_Rect Apple_Clip;
	void Animation();
	int PosX, PosY, AnimPosX, AnimPosY;
	static int Anim_Int;
	bool Anim_UP_DN, is_Eaten, is_Start;
	void Set_New_Pos();
	void Set_Anim_Pos();
	void Get_Animation(SDL_Renderer* Renderer);

public:
	Apple();
	Apple(Texture Game_Texture[SURFACES_TEXTURES_ENUM::TOTAL], SDL_Rect Game_Clips[CLIPS_ENUM::TOTAL]);
	~Apple();
	virtual void Render(SDL_Renderer* Renderer, const int& x = 0, const int& y = 0) override;
	virtual void Interaction(Snake& Snake_Obj) override;
};

int Apple::Anim_Int = 0;