#pragma once

#include "Texture.h"
#include "Menu.h"
#include "Background.h"
#include "Bird.h"
#include "Pipe.h"
#include"Button.h"
#include "Selector.h"
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Sound.h"

enum SURFACE_ENUM {
	Screen_SURFACE,
	Background_SURFACE,
	Menu_SURFACE,
	Bird_SURFACE,
	Pipe_SURFACE,
	Total_SURFACE
};

enum TEXTURE_ENUM {
	Background_TEXTURE,
	Menu_TEXTURE,
	Bird_TEXTURE,
	Pipe_TEXTURE,
	Title_Fond_TEXTURE,
	Background_Fond_TEXTURE,
	Day_Fond_TEXTURE,
	Night_Fond_TEXTURE,
	Sound_Fond_TEXTURE,
	Selector_Right_Fond_TEXTURE,
	Selector_Left_Fond_TEXTURE,
	On_Fond_TEXTURE,
	Off_Fond_TEXTURE,
	Score_Fond_TEXTURE,
	Score_Num_Fond_TEXTURE,
	Author_Fond_TEXTURE,
	Instruction_One_Fond_TEXTURE,
	Instruction_Two_Fond_TEXTURE,
	Total_TEXTURE
};

enum CLIP_ENUM {
	CLIP_BACKGROUND_DAY,
	CLIP_BACKGROUND_NIGHT,
	CLIP_MENU_START_DARK,
	CLIP_MENU_OPTIONS_DARK,
	CLIP_MENU_QUIT_DARK,
	CLIP_MENU_START_LIGHT,
	CLIP_MENU_OPTIONS_LIGHT,
	CLIP_MENU_QUIT_LIGHT,
	CLIP_BIRD_MOVE_UP,
	CLIP_BIRD_MOVE_DOWN,
	CLIP_BIRD_DEAD_UP,
	CLIP_BIRD_DEAD_DOWN,
	CLIP_PIPE_UP_HIGH,
	CLIP_PIPE_UP_MEDIUM,
	CLIP_PIPE_UP_LOW,
	CLIP_PIPE_DOWN_HIGH,
	CLIP_PIPE_DOWN_MEDIUM,
	CLIP_PIPE_DOWN_LOW,
	CLIP_PIPE_GAP_LOW,
	CLIP_PIPE_GAP_HIGH,
	CLIP_TOTAL
};

enum TEXT_ENUM {
	Title_TEXT,
	Background_TEXT,
	Day_TEXT,
	Night_TEXT,
	Sound_TEXT,
	Selector_Right_TEXT,
	Selector_Left_TEXT,
	On_TEXT,
	Off_TEXT,
	Score_TEXT,
	Score_Num_TEXT,
	Author_TEXT,
	Instruction_One_TEXT,
	Instruction_Two_TEXT,
	Total_TEXT
};

void Set_Clip(SDL_Rect& Clip, const int& x, const int& y, const int& w, const int& h);

//Managing system of the application.
//Main class which has access to others.
class System {
public:
	System();
	~System();
	//Core of the application
	void Play();
	//Initialisation of SDL functions
	bool Initialisation();
	SDL_Window* GetWindow();
	SDL_Renderer* GetRenderer();
	//Loading IMG files
	void Load_IMG_Surface(SDL_Surface*& Buff_Surface, SDL_Surface*& Optimized_Surface, bool& success, SDL_Surface*& Class_Member_Surface);
	//Loading TTF files (every subtitles in the application)
	void Load_TTF(TTF_Font*& TextFont, bool& success, std::string& Text, TEXTURE_ENUM Index);
	//Loading all files which arerequired to proper work of the application
	bool Load_Media(std::string& Backgound_Path, std::string& Menu_Path, std::string& Bird_Path, std::string& Pipe_Path, std::string& TTF_Path, TTF_Font*& TextFont);

	SDL_Surface* GetScreenSurface();
	SDL_Surface* GetBackgroundSurface();
	SDL_Surface* GetMenuSurface();
	SDL_Surface* GetBirdSurface();
	SDL_Surface* GetPipeSurface();

	Texture GetBackgroundTexture();
	Texture GetMenuTexture();
	Texture GetBirdTexture();
	Texture GetPipeTexture();
	//Check if the User pressed SPACE key and began the Game
	void Game_Begin_Communicate(SDL_Event* Game_Event, bool& Game_Start);
private:
	SDL_Window* Window;
	SDL_Renderer* Renderer;
	TTF_Font* TextFont;
	SDL_Surface* Surfaces[Total_SURFACE];
	Texture Textures[Total_TEXTURE];
	SDL_Rect Texture_Clips[CLIP_TOTAL];
	std::string Text[Total_TEXT];
	int Width, Height;
};
//Controlling the speed of the Game
int Game_Speed_Controller(int& Game_Delay);
