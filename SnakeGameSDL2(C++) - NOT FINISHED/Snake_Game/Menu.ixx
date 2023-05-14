export module Menu;

import Button;
import "SDL.h";
import Core;
import Snake;

export namespace BUTTON_ENUM {
	enum {
		PLAY,
		OPTION,
		QUIT,
		SOUND_ON,
		SOUND_OFF,
		MUSIC_ON,
		MUSIC_OFF,
		RANKING,
		CANCEL,
		TOTAL
	};
}

export class Menu {
private:
	Button Game_buttons[BUTTON_ENUM::TOTAL];
	Texture* Title_TEXT_BLACK;
	Texture* Title_TEXT_WHITE;
	Texture* Author_TEXT_BLACK;
	Texture* Author_TEXT_WHITE;
	bool Play_Bool, Option_Bool, Quit_Bool, Sound_Bool, Music_Bool, Ranking_Bool;
	void Menu_Actions();
	void Reset_Buttons();
	void Render_Title_Author(SDL_Renderer* Renderer);
	void SubMenu_Actions();
	void Button_ON_OFF(const int& Button_Index, bool& Button_Bool);
public:
	Menu();
	Menu(Texture Game_Textures[SURFACES_TEXTURES_ENUM::TOTAL], SDL_Rect Game_Clips[CLIPS_ENUM::TOTAL], Texture& Title_TEXT_BLACK, Texture& Title_TEXT_WHITE, Texture& Author_TEXT_BLACK, Texture& Author_TEXT_WHITE);
	~Menu();
	void Check_Events(SDL_Event Event);
	void Render_Menu(SDL_Renderer* Renderer);
	bool Get_Play_Bool();
	bool Get_Options_Bool();
	bool Get_Quit_Bool();
	void Render_SubMenu(SDL_Renderer* Renderer);
	void Reset_Play_Bool();
	void Reset_Option_Bool();
	void Button_GmOv_Menu();
	Button& Return_Cancel_Button();
	void Check_Events_Return_Cancel_Button(SDL_Event Event);
};