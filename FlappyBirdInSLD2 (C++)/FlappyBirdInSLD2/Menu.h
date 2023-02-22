#pragma once

#include "System.h"
#include "Button.h"

enum BUTTON_ENUM {
	MENU_START,
	MENU_OPTIONS,
	MENU_QUIT,
	MENU_TOTAL
};

//Represent game main manu and menages a button objects.
class Menu {
public:
	Menu(SDL_Rect Clips[20]);
	~Menu();
	//Render every Menu Buttons
	void Render(Texture& Buttons_Textures, SDL_Renderer* Renderer);
	//Render only Quit Button (used to return from Play and Options Pages to Main Menu Page)
	void RenderQuit(Texture& Button_Textures, SDL_Renderer* Renderer);
	//Check User's clicks for all buttons
	void CheckEvents(SDL_Event* Mouse_Event);
	//Check User's clicks only for Quit button
	void CheckEventsQuit(SDL_Event* Mouse_Event);
	bool GetStart();
	bool GetOptions();
	bool GetQuit();
	void Reset_Start();
	void Reset_Options();
	void Reset_Quit();
private:
	Button Menu_Buttons[MENU_TOTAL];
	bool Start, Options, Quit;
	void Menu_Actions();
	void Reset_Buttons();
};
//Makes the Quick button to return to Main Menu page from Subpages 
void QuitAction(bool& isQuit, Menu& Game_Menu);
