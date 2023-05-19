export module Obstacle;

import Game_Object;
import Texture;
import Core;
import Sound;

export class Obstacle : public Game_Object {
private:
	Texture* Obstacle_Texture;
	SDL_Rect Obstacle_Clip;
	int PosX, PosY, AnimPosX, AnimPosY;
	static int Anim_Int;
	bool is_Eaten, is_Start;
	void Set_New_Pos();
	void Set_Anim_Pos();
	void Get_Animation(SDL_Renderer* Renderer);
	Sound Collision;
public:
	Obstacle();
	Obstacle(Texture Game_Texture[SURFACES_TEXTURES_ENUM::TOTAL], SDL_Rect Game_Clips[CLIPS_ENUM::TOTAL]);
	~Obstacle();
	virtual void Render(SDL_Renderer* Renderer, const int& x = 0, const int& y = 0) override;
	virtual void Interaction(Snake& Snake_Obj) override;
};