#include "Menu.h"

Menu::Menu(SDL_Rect Clips[20]) : Start(false), Options(false), Quit(false) {
	this->Menu_Buttons[MENU_START].Set_Params(Clips[CLIP_MENU_START_DARK], Clips[CLIP_MENU_START_LIGHT], 75, 150);
	this->Menu_Buttons[MENU_OPTIONS].Set_Params(Clips[CLIP_MENU_OPTIONS_DARK], Clips[CLIP_MENU_OPTIONS_LIGHT], 75, 250);
	this->Menu_Buttons[MENU_QUIT].Set_Params(Clips[CLIP_MENU_QUIT_DARK], Clips[CLIP_MENU_QUIT_LIGHT], 75, 350);
}

Menu::~Menu() { }

void Menu::Render(Texture& Buttons_Textures, SDL_Renderer* Renderer) {
	for (int i = 0; i < MENU_TOTAL; ++i) {
		this->Menu_Buttons[i].Render(Buttons_Textures, Renderer);
	}
}

void Menu::RenderQuit(Texture& Button_Textures, SDL_Renderer* Renderer) {
	this->Menu_Buttons[MENU_QUIT].Render(Button_Textures, Renderer);
}

void Menu::CheckEvents(SDL_Event* Mouse_Event) {
	for (int i = 0; i < MENU_TOTAL; ++i) {
		this->Menu_Buttons[i].Check_Event(Mouse_Event);
	}
	Menu_Actions();
	Reset_Buttons();
}

void Menu::CheckEventsQuit(SDL_Event* Mouse_Event) {
	this->Menu_Buttons[MENU_QUIT].Check_Event(Mouse_Event);
	Menu_Actions();
	Reset_Buttons();
}

void Menu::Menu_Actions() {
	if (this->Menu_Buttons[MENU_START].GetisClicked() == true) {
		this->Start = true;
	}
	else if (this->Menu_Buttons[MENU_OPTIONS].GetisClicked() == true) {
		this->Options = true;
	}
	else if (this->Menu_Buttons[MENU_QUIT].GetisClicked() == true) {
		this->Quit = true;
	}
}

void Menu::Reset_Buttons() {
	this->Menu_Buttons[MENU_START].ResetisCliced();
	this->Menu_Buttons[MENU_OPTIONS].ResetisCliced();
	this->Menu_Buttons[MENU_QUIT].ResetisCliced();
}

bool Menu::GetStart() {
	return this->Start;
}

bool Menu::GetOptions() {
	return this->Options;
}

bool Menu::GetQuit() {
	return this->Quit;
}

void Menu::Reset_Start() {
	this->Start = false;
}

void Menu::Reset_Options() {
	this->Options = false;
}

void Menu::Reset_Quit() {
	this->Quit = false;
}

void QuitAction(bool& isQuit, Menu& Game_Menu) {
	if (isQuit) {
		Game_Menu.Reset_Options();
		Game_Menu.Reset_Quit();
		isQuit = false;
	}
	else if (Game_Menu.GetQuit()) {
		isQuit = true;
	}
}