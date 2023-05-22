export module Core;

import <SDL.h>;
import <SDL_mixer.h>;
import <SDL_ttf.h>;
import <SDL_image.h>;
import <vector>;
import <memory>;
import <string>;
import Texture;

/// <summary>
/// Przestrzen nazw wszystkich sciezek plikow zewnetrznych uzytych w programie
/// </summary>
export namespace PATHS {
	std::vector<std::string> PLAY_PATH{ "Graphics/Blue buttons/play blue button 300x80 hover/Play button blue 300x80 hover000001.png", "Graphics/Blue buttons/play blue button 300x80 hover/Play button blue 300x80 hover000002.png", "Graphics/Blue buttons/play blue button 300x80 hover/Play button blue 300x80 hover000003.png", "Graphics/Blue buttons/play blue button 300x80 hover/Play button blue 300x80 hover000004.png", "Graphics/Blue buttons/play blue button 300x80 hover/Play button blue 300x80 hover000005.png",
		"Graphics/Blue buttons/play blue button 300x80 hover/Play button blue 300x80 hover000006.png","Graphics/Blue buttons/play blue button 300x80 hover/Play button blue 300x80 hover000007.png","Graphics/Blue buttons/play blue button 300x80 hover/Play button blue 300x80 hover000008.png", "Graphics/Blue buttons/play blue button 300x80 hover/Play button blue 300x80 hover000009.png","Graphics/Blue buttons/play blue button 300x80 hover/Play button blue 300x80 hover000010.png", 
		"Graphics/Blue buttons/play blue button 300x80 hover/Play button blue 300x80 hover000011.png","Graphics/Blue buttons/play blue button 300x80 hover/Play button blue 300x80 hover000012.png", "Graphics/Blue buttons/play blue button 300x80 hover/Play button blue 300x80 hover000013.png", "Graphics/Blue buttons/play blue button 300x80 hover/Play button blue 300x80 hover000014.png", "Graphics/Blue buttons/play blue button 300x80 hover/Play button blue 300x80 hover000015.png", 
		"Graphics/Blue buttons/play blue button 300x80 hover/Play button blue 300x80 hover000016.png","Graphics/Blue buttons/play blue button 300x80 hover/Play button blue 300x80 hover000017.png", "Graphics/Blue buttons/play blue button 300x80 hover/Play button blue 300x80 hover000018.png", "Graphics/Blue buttons/play blue button 300x80 hover/Play button blue 300x80 hover000019.png", "Graphics/Blue buttons/play blue button 300x80 hover/Play button blue 300x80 hover000020.png",
		"Graphics/Blue buttons/play blue button 300x80 hover/Play button blue 300x80 hover000021.png", "Graphics/Blue buttons/play blue button 300x80 hover/Play button blue 300x80 hover000022.png", "Graphics/Blue buttons/play blue button 300x80 hover/Play button blue 300x80 hover000023.png", "Graphics/Blue buttons/play blue button 300x80 hover/Play button blue 300x80 hover000024.png", "Graphics/Blue buttons/play blue button 300x80 hover/Play button blue 300x80 hover000025.png", 
		"Graphics/Blue buttons/play blue button 300x80 hover/Play button blue 300x80 hover000026.png", "Graphics/Blue buttons/play blue button 300x80 hover/Play button blue 300x80 hover000027.png", "Graphics/Blue buttons/play blue button 300x80 hover/Play button blue 300x80 hover000028.png", "Graphics/Blue buttons/play blue button 300x80 hover/Play button blue 300x80 hover000029.png", "Graphics/Blue buttons/play blue button 300x80 hover/Play button blue 300x80 hover000030.png" };
	std::vector<std::string> OPTIONS_PATH{"Graphics/Blue buttons/options blue button 300x80 hover/option button blue 300x80 hover000001000001.png", "Graphics/Blue buttons/options blue button 300x80 hover/option button blue 300x80 hover000001000002.png","Graphics/Blue buttons/options blue button 300x80 hover/option button blue 300x80 hover000001000003.png","Graphics/Blue buttons/options blue button 300x80 hover/option button blue 300x80 hover000001000004.png",
		"Graphics/Blue buttons/options blue button 300x80 hover/option button blue 300x80 hover000001000005.png", "Graphics/Blue buttons/options blue button 300x80 hover/option button blue 300x80 hover000001000006.png", "Graphics/Blue buttons/options blue button 300x80 hover/option button blue 300x80 hover000001000007.png", "Graphics/Blue buttons/options blue button 300x80 hover/option button blue 300x80 hover000001000008.png",
		"Graphics/Blue buttons/options blue button 300x80 hover/option button blue 300x80 hover000001000009.png", "Graphics/Blue buttons/options blue button 300x80 hover/option button blue 300x80 hover000001000010.png", "Graphics/Blue buttons/options blue button 300x80 hover/option button blue 300x80 hover000001000011.png", "Graphics/Blue buttons/options blue button 300x80 hover/option button blue 300x80 hover000001000012.png", 
		"Graphics/Blue buttons/options blue button 300x80 hover/option button blue 300x80 hover000001000013.png", "Graphics/Blue buttons/options blue button 300x80 hover/option button blue 300x80 hover000001000014.png", "Graphics/Blue buttons/options blue button 300x80 hover/option button blue 300x80 hover000001000015.png", "Graphics/Blue buttons/options blue button 300x80 hover/option button blue 300x80 hover000001000016.png", 
		"Graphics/Blue buttons/options blue button 300x80 hover/option button blue 300x80 hover000001000017.png", "Graphics/Blue buttons/options blue button 300x80 hover/option button blue 300x80 hover000001000018.png", "Graphics/Blue buttons/options blue button 300x80 hover/option button blue 300x80 hover000001000019.png", "Graphics/Blue buttons/options blue button 300x80 hover/option button blue 300x80 hover000001000020.png", 
		"Graphics/Blue buttons/options blue button 300x80 hover/option button blue 300x80 hover000001000021.png", "Graphics/Blue buttons/options blue button 300x80 hover/option button blue 300x80 hover000001000022.png", "Graphics/Blue buttons/options blue button 300x80 hover/option button blue 300x80 hover000001000023.png", "Graphics/Blue buttons/options blue button 300x80 hover/option button blue 300x80 hover000001000024.png", 
		"Graphics/Blue buttons/options blue button 300x80 hover/option button blue 300x80 hover000001000025.png", "Graphics/Blue buttons/options blue button 300x80 hover/option button blue 300x80 hover000001000026.png", "Graphics/Blue buttons/options blue button 300x80 hover/option button blue 300x80 hover000001000027.png", "Graphics/Blue buttons/options blue button 300x80 hover/option button blue 300x80 hover000001000028.png", 
		"Graphics/Blue buttons/options blue button 300x80 hover/option button blue 300x80 hover000001000029.png", "Graphics/Blue buttons/options blue button 300x80 hover/option button blue 300x80 hover000001000030.png" };
	std::vector<std::string> MORE_PATH{ "Graphics/Blue buttons/more blue button 300x80 hover/more button blue 300x80 hover000001.png", "Graphics/Blue buttons/more blue button 300x80 hover/more button blue 300x80 hover000002.png", "Graphics/Blue buttons/more blue button 300x80 hover/more button blue 300x80 hover000003.png", "Graphics/Blue buttons/more blue button 300x80 hover/more button blue 300x80 hover000004.png", "Graphics/Blue buttons/more blue button 300x80 hover/more button blue 300x80 hover000005.png",
		"Graphics/Blue buttons/more blue button 300x80 hover/more button blue 300x80 hover000006.png", "Graphics/Blue buttons/more blue button 300x80 hover/more button blue 300x80 hover000007.png", "Graphics/Blue buttons/more blue button 300x80 hover/more button blue 300x80 hover000008.png", "Graphics/Blue buttons/more blue button 300x80 hover/more button blue 300x80 hover000009.png", "Graphics/Blue buttons/more blue button 300x80 hover/more button blue 300x80 hover000010.png",
		"Graphics/Blue buttons/more blue button 300x80 hover/more button blue 300x80 hover000011.png", "Graphics/Blue buttons/more blue button 300x80 hover/more button blue 300x80 hover000012.png", "Graphics/Blue buttons/more blue button 300x80 hover/more button blue 300x80 hover000013.png", "Graphics/Blue buttons/more blue button 300x80 hover/more button blue 300x80 hover000014.png", "Graphics/Blue buttons/more blue button 300x80 hover/more button blue 300x80 hover000015.png",
		"Graphics/Blue buttons/more blue button 300x80 hover/more button blue 300x80 hover000016.png", "Graphics/Blue buttons/more blue button 300x80 hover/more button blue 300x80 hover000017.png", "Graphics/Blue buttons/more blue button 300x80 hover/more button blue 300x80 hover000018.png", "Graphics/Blue buttons/more blue button 300x80 hover/more button blue 300x80 hover000019.png", "Graphics/Blue buttons/more blue button 300x80 hover/more button blue 300x80 hover000020.png",
		"Graphics/Blue buttons/more blue button 300x80 hover/more button blue 300x80 hover000021.png", "Graphics/Blue buttons/more blue button 300x80 hover/more button blue 300x80 hover000022.png", "Graphics/Blue buttons/more blue button 300x80 hover/more button blue 300x80 hover000023.png", "Graphics/Blue buttons/more blue button 300x80 hover/more button blue 300x80 hover000024.png", "Graphics/Blue buttons/more blue button 300x80 hover/more button blue 300x80 hover000025.png",
		"Graphics/Blue buttons/more blue button 300x80 hover/more button blue 300x80 hover000026.png", "Graphics/Blue buttons/more blue button 300x80 hover/more button blue 300x80 hover000027.png", "Graphics/Blue buttons/more blue button 300x80 hover/more button blue 300x80 hover000028.png", "Graphics/Blue buttons/more blue button 300x80 hover/more button blue 300x80 hover000029.png", "Graphics/Blue buttons/more blue button 300x80 hover/more button blue 300x80 hover000030.png" };
	std::vector<std::string> QUIT_PATH{ "Graphics/Blue buttons/Quit blue button 300x80 hover/Quit button blue 300x80 hover000001.png", "Graphics/Blue buttons/Quit blue button 300x80 hover/Quit button blue 300x80 hover000002.png", "Graphics/Blue buttons/Quit blue button 300x80 hover/Quit button blue 300x80 hover000003.png", "Graphics/Blue buttons/Quit blue button 300x80 hover/Quit button blue 300x80 hover000004.png", "Graphics/Blue buttons/Quit blue button 300x80 hover/Quit button blue 300x80 hover000005.png",
		"Graphics/Blue buttons/Quit blue button 300x80 hover/Quit button blue 300x80 hover000006.png", "Graphics/Blue buttons/Quit blue button 300x80 hover/Quit button blue 300x80 hover000007.png", "Graphics/Blue buttons/Quit blue button 300x80 hover/Quit button blue 300x80 hover000008.png", "Graphics/Blue buttons/Quit blue button 300x80 hover/Quit button blue 300x80 hover000009.png", "Graphics/Blue buttons/Quit blue button 300x80 hover/Quit button blue 300x80 hover000010.png",
		"Graphics/Blue buttons/Quit blue button 300x80 hover/Quit button blue 300x80 hover000011.png", "Graphics/Blue buttons/Quit blue button 300x80 hover/Quit button blue 300x80 hover000012.png", "Graphics/Blue buttons/Quit blue button 300x80 hover/Quit button blue 300x80 hover000013.png", "Graphics/Blue buttons/Quit blue button 300x80 hover/Quit button blue 300x80 hover000014.png", "Graphics/Blue buttons/Quit blue button 300x80 hover/Quit button blue 300x80 hover000015.png",
		"Graphics/Blue buttons/Quit blue button 300x80 hover/Quit button blue 300x80 hover000016.png", "Graphics/Blue buttons/Quit blue button 300x80 hover/Quit button blue 300x80 hover000017.png", "Graphics/Blue buttons/Quit blue button 300x80 hover/Quit button blue 300x80 hover000018.png", "Graphics/Blue buttons/Quit blue button 300x80 hover/Quit button blue 300x80 hover000019.png", "Graphics/Blue buttons/Quit blue button 300x80 hover/Quit button blue 300x80 hover000020.png",
		"Graphics/Blue buttons/Quit blue button 300x80 hover/Quit button blue 300x80 hover000021.png", "Graphics/Blue buttons/Quit blue button 300x80 hover/Quit button blue 300x80 hover000022.png", "Graphics/Blue buttons/Quit blue button 300x80 hover/Quit button blue 300x80 hover000023.png", "Graphics/Blue buttons/Quit blue button 300x80 hover/Quit button blue 300x80 hover000024.png", "Graphics/Blue buttons/Quit blue button 300x80 hover/Quit button blue 300x80 hover000025.png",
		"Graphics/Blue buttons/Quit blue button 300x80 hover/Quit button blue 300x80 hover000026.png", "Graphics/Blue buttons/Quit blue button 300x80 hover/Quit button blue 300x80 hover000027.png", "Graphics/Blue buttons/Quit blue button 300x80 hover/Quit button blue 300x80 hover000028.png", "Graphics/Blue buttons/Quit blue button 300x80 hover/Quit button blue 300x80 hover000029.png", "Graphics/Blue buttons/Quit blue button 300x80 hover/Quit button blue 300x80 hover000030.png" };
	std::vector<std::string> COIN_PATH{"Graphics/star coin animation Pack/star coin rotate/star coin rotate 1.png","Graphics/star coin animation Pack/star coin rotate/star coin rotate 2.png","Graphics/star coin animation Pack/star coin rotate/star coin rotate 3.png","Graphics/star coin animation Pack/star coin rotate/star coin rotate 4.png","Graphics/star coin animation Pack/star coin rotate/star coin rotate 5.png","Graphics/star coin animation Pack/star coin rotate/star coin rotate 6.png"};
	std::string BACKGROUND_PATH{ "Graphics/background.png" };
	std::string APPLE_PATH{ "Graphics/apple.png" };
	std::string SNAKE_PATH{ "Graphics/Snake.png"};
	std::string OBSTACLE_PATH{"Graphics/obstacle.png"};
	std::string FONT_PATH{"TTF_Fonts/Squirk-RMvV.ttf"};
	std::string MENU_THEME_PATH{ "Sounds/Menu_Theme.wav" };
	std::string BUTTON_CLICKED_SOUND_PATH{"Sounds/ButtonClicked.wav"};
	std::string BUTTON_SELECTED_SOUND_PATH{ "Sounds/ButtonSelected.wav" };
	std::string GET_APPLE_SOUND_PATH{ "Sounds/GetApple.wav" };
	std::string GET_COIN_SOUND_PATH{ "Sounds/GetCoin.wav" };
	std::string COLLISION_SOUND_PATH{ "Sounds/Collision.wav" };
}

export namespace SURFACES_TEXTURES_ENUM {
	enum Game_Surfaces_Textures_ENUM {
		PLAY_1, PLAY_2, PLAY_3, PLAY_4, PLAY_5, PLAY_6, PLAY_7, PLAY_8, PLAY_9, PLAY_10, PLAY_11, PLAY_12, PLAY_13, PLAY_14, PLAY_15, PLAY_16, PLAY_17, PLAY_18, PLAY_19, PLAY_20, PLAY_21, PLAY_22, PLAY_23, PLAY_24,
		PLAY_25, PLAY_26, PLAY_27, PLAY_28, PLAY_29, PLAY_30,

		OPTION_1, OPTION_2, OPTION_3, OPTION_4, OPTION_5, OPTION_6, OPTION_7, OPTION_8, OPTION_9, OPTION_10, OPTION_11, OPTION_12, OPTION_13, OPTION_14, OPTION_15, OPTION_16, OPTION_17, OPTION_18, OPTION_19, OPTION_20,
		OPTION_21, OPTION_22, OPTION_23, OPTION_24, OPTION_25, OPTION_26, OPTION_27, OPTION_28, OPTION_29, OPTION_30,

		QUIT_1, QUIT_2, QUIT_3, QUIT_4, QUIT_5, QUIT_6, QUIT_7, QUIT_8, QUIT_9, QUIT_10, QUIT_11, QUIT_12, QUIT_13, QUIT_14, QUIT_15, QUIT_16, QUIT_17, QUIT_18, QUIT_19, QUIT_20,
		QUIT_21, QUIT_22, QUIT_23, QUIT_24, QUIT_25, QUIT_26, QUIT_27, QUIT_28, QUIT_29, QUIT_30,

		COIN_1, COIN_2, COIN_3, COIN_4, COIN_5, COIN_6,

		BACKGROUND,
		APPLE,
		SNAKE,
		OBSTACLE,
		TITLE_TEXT_WHITE,
		TITLE_TEXT_BLACK,
		AUTHOR_TEXT_WHITE,
		AUTHOR_TEXT_BLACK,
		SOUND_ON_TEXT_NOT_SEL,
		SOUND_ON_TEXT_SEL,
		SOUND_ON_TEXT_BLACK,
		SOUND_OFF_TEXT_NOT_SEL,
		SOUND_OFF_TEXT_SEL,
		SOUND_OFF_TEXT_BLACK,
		MUSIC_ON_TEXT_NOT_SEL,
		MUSIC_ON_TEXT_SEL,
		MUSIC_ON_TEXT_BLACK,
		MUSIC_OFF_TEXT_NOT_SEL,
		MUSIC_OFF_TEXT_SEL,
		MUSIC_OFF_TEXT_BLACK,
		RANKING_TEXT_NOT_SEL,
		RANKING_TEXT_SEL,
		RANKING_TEXT_BLACK,
		CANCEL_TEXT_NOT_SEL,
		CANCEL_TEXT_SEL,
		CANCEL_TEXT_BLACK,
		SCORE_TEXT_WHITE,
		SCORE_TEXT_BLACK,
		TIME_TEXT_WHITE,
		TIME_TEXT_BLACK,
		START_TEXT_WHITE,
		START_TEXT_BLACK,
		GAME_OVER_TEXT_BLACK,
		GAME_OVER_TEXT_WHITE,
		TOTAL
	};
}

export namespace CLIPS_ENUM {
	const int Main_Buttons_Anim_Count = 30;
	enum Game_Clips_ENUM {
		PLAY,
		OPTION,
		QUIT,
		COIN_1, COIN_2, COIN_3, COIN_4, COIN_5, COIN_6,
		BACKGROUND,
		APPLE,
		SNAKE_TAIL_DOWN, SNAKE_TAIL_RIGHT, SNAKE_TAIL_LEFT, SNAKE_TAIL_UP, SNAKE_BODY_VER, SNAKE_BODY_HOR, SNAKE_HEAD_UP, SNAKE_HEAD_DOWN, SNAKE_HEAD_RIGHT, SNAKE_HEAD_LEFT, SNAKE_DN_RIGHT, SNAKE_UP_RIGHT, SNAKE_UP_LEFT, SNAKE_DN_LEFT, 
		OBSTACLE,
		SOUND_BOX,
		MUSIC_BOX,
		RANKING_BOX,
		CANCEL_BOX,
		TOTAL
	};
}

export namespace TEXT_TTF {
	std::string TITLE_TEXT{ "SNAKE GAME" },
		AUTHOR_TEXT{ "AUTHOR : MICHAL WIECZOREK" },
		SOUND_ON_TEXT{ "SOUNDS - ON" },
		SOUND_OFF_TEXT{ "SOUNDS - OFF" },
		MUSIC_ON_TEXT{ "MUSIC - ON" },
		MUSIC_OFF_TEXT{ "MUSIC - OFF" },
		RANKING_TEXT{ "SHOW RANKING" },
		CANCEL_TEXT{ "Back to Menu" },
		SCORE_TEXT{ "SCORE : " },
		TIME_TEXT{ "TIME : " },
		START_TEXT{ "PRESS ANY MOTION KEY TO START" },
		GAME_OVER_TEXT{ "GAME OVER" },
		NEW_RECORD_TEXT{"NEW RECORD!!!"},
		RECORDS_DISPLAY_TEXT{"SCORE      TIME          DATE"};
}

// Klasa inizjalizujaca i obslugujaca biblioteke graficzna SDL 2
export class Core {
protected:
	SDL_Window* Window;
	SDL_Surface* Screen_Surface;
	SDL_Surface* Game_Surfaces[SURFACES_TEXTURES_ENUM::TOTAL];
	Texture Game_Textures[SURFACES_TEXTURES_ENUM::TOTAL];
	SDL_Rect Game_Clips[CLIPS_ENUM::TOTAL];
	TTF_Font* TextFont;
	SDL_Renderer* Renderer;
	SDL_Event event;
	int Width, Height;
	bool initialisation();
	bool load_media();
	Core();
	~Core();
private:
	SDL_Texture* loadTexture(const std::string& path);
	void Load_IMG_Surface(SDL_Surface*& Buff_Surface, SDL_Surface*& Optimized_Surface, bool& success, SDL_Surface*& Class_Member_Surface);
	void Load_TTF(TTF_Font*& TextFont, bool& success, std::string& Text, const int& Index, const int& R, const int& G, const int& B);
	void load_Clips();
};

void Set_Clip(SDL_Rect& Clip, const int& x, const int& y, const int& w, const int& h);