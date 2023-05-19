export module Button;

import Texture;
import "SDL.h";
import Core;
import Sound;

export class Button {
private:
	bool is_Light, is_Clicked, is_Main_Button; //Detect if the button is the main menu button or submenu button
	int Anim_Frames; //Frames counters during animation process in the main menu
	int Index; //used in main menu buttons animation 
	Texture* Button_Texture_NOT_Clicked;
	Texture* Button_Texture_Clicked;
	Texture* Button_Texture_BLACK;
	Texture* Button_Texture_Animation[CLIPS_ENUM::Main_Buttons_Anim_Count];
	SDL_Rect Button_Clip;
	SDL_Point Position;
	void Animation(const int& x, const int& y, SDL_Renderer* Renderer);
	Sound Selected, Clicked;
public:
	Button();
	Button(Texture& Button_Texture_NOT_Clicked, Texture& Button_Texture_Clicked,Texture& Button_Texture_BLACK, SDL_Rect Button_Clip);
	Button(Texture Button_Texture_Animation[CLIPS_ENUM::Main_Buttons_Anim_Count], SDL_Rect Button_Clip, const int& begin, const int& end);
	~Button();
	void Check_Event(SDL_Event* Mouse_Event);
	bool Get_is_Clicked();
	void Reset_is_Clicked();
	void Render(const int& x, const int& y, SDL_Renderer* Renderer);
};