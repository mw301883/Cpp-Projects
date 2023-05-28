export module Snake;

import Core;
import <SDL.h>;
import Texture;
import Time_Counter;
import <deque>;
import <tuple>;
import <SDL_ttf.h>;
import Button;
import Sound;
import <algorithm>;
import <fstream>;
import External_Functions;

namespace SNAKE_ENUM {
	enum {
		SNAKE_TAIL_DOWN,
		SNAKE_TAIL_RIGHT,
		SNAKE_TAIL_LEFT,
		SNAKE_TAIL_UP,
		SNAKE_BODY_VER,
		SNAKE_BODY_HOR,
		SNAKE_HEAD_UP,
		SNAKE_HEAD_DOWN,
		SNAKE_HEAD_RIGHT,
		SNAKE_HEAD_LEFT,
		SNAKE_DN_RIGHT,
		SNAKE_UP_RIGHT,
		SNAKE_UP_LEFT,
		SNAKE_DN_LEFT,
		TOTAL
	};
}

namespace DIRECTION {
	enum {
		UP,
		DOWN,
		RIGHT,
		LEFT,
		NONE
	};
}

export class Snake {
public:
	Snake();
	Snake(SDL_Window* Screen_Window, Texture Game_Texture[SURFACES_TEXTURES_ENUM::TOTAL], SDL_Rect Game_Clips[CLIPS_ENUM::TOTAL]);
	~Snake();
	bool Render(SDL_Renderer* Renderer);
	void Check_Events(SDL_Event& Game_Event);
	void Grow();
	void Add_Score();
	void Minus_Score();
	static const int Width = 40, Height = 40;
	void Move();
	int Get_PosX();
	int Get_PosY();
	int Get_Score();
	std::string Get_Time();
	void Set_Score(const int& New_Score);
	void Display_Statis(SDL_Renderer* Renderer, TTF_Font* Font, Texture* Score_White, Texture* Score_Black, Texture* Time_White, Texture* Time_Black);
	void Begining_Text(SDL_Renderer* Renderer, Texture* Text_Texture_White, Texture* Text_Texture_Black);
	void Start_Timer(const int& Prev_Time);
	bool Display_GmOv_Statis(SDL_Renderer* Renderer, TTF_Font* Font, Texture* Score_White, Texture* Score_Black, Texture* Time_White, Texture* Time_Black, Texture* Gm_Ov_White, Texture* Gm_Ov_Black, Button& Cancel_Button);
	void Reset();
private:
	Texture* Snake_Texture;
	SDL_Rect Snake_Clips[SNAKE_ENUM::TOTAL];
	Time_Counter Counter;
	int PosX, PosY, Screen_Width, Screen_Height, Lenght, Direction, Speed, Score, Time;
	bool is_Colision, New_Play, is_Add_Score, is_Minus_Score, is_Back_To_Menu;
	std::deque<std::tuple<int, int, SDL_Rect, int>> Snake_Body;
	Sound Collision;
private:
	void Set_Segments();
	SDL_Rect Set_Snake_Head_Clip();
	int Calculate_Segment(const int& Prev_Pos, const int& Pos);
	SDL_Rect Set_Snake_Body_Clip(const int& Clip_Num);
	SDL_Rect Set_Snake_Tail_Clip(const int& Clip_Num);
	void Check_If_Collision();
	void Display_New_Record_Text(SDL_Renderer* Renderer, TTF_Font* Font);
};