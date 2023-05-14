import Core;

import <SDL.h>;
import <SDL_image.h>;
import <SDL_mixer.h>;
import <SDL_ttf.h>;
import <stdio.h>;
import <memory>;

import Texture;

void Set_Clip(SDL_Rect& Clip, const int& x, const int& y, const int& w, const int& h) {
	Clip.x = x;
	Clip.y = y;
	Clip.w = w;
	Clip.h = h;
}

Core::Core() {
	if (!initialisation()) {
		printf("\nError encountered during initialisation process.");
	}
	else {
		if (!load_media()) {
			printf("\nError occured during images loading.");
		}
		else {
			load_Clips();
			//TODO MUSIC INIT
		}
	}
}

Core::~Core() {
	SDL_DestroyRenderer(this->Renderer);
	this->Renderer = nullptr;
	//TODO texture destroyer
	SDL_FreeSurface(this->Screen_Surface);
	this->Screen_Surface = nullptr;
	SDL_DestroyWindow(this->Window);
	this->Window = nullptr;
	IMG_Quit();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}


bool Core::initialisation() {
	SDL_DisplayMode DM;
	SDL_GetDesktopDisplayMode(0, &DM);
	this->Width = DM.w;
	this->Height = DM.h;
	bool success = false;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		printf("\nError SDL could not be inistalised : ", SDL_GetError);
	}
	else {
		this->Window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->Width, this->Height, SDL_WINDOW_SHOWN);
		if (this->Window == nullptr) {
			printf("\nError - unable to create window : ", SDL_GetError);
		}
		else {
			SDL_SetWindowFullscreen(this->Window, SDL_WINDOW_FULLSCREEN_DESKTOP);
			this->Renderer = SDL_CreateRenderer(this->Window, -1, SDL_RENDERER_ACCELERATED);
			if (this->Renderer == nullptr) {
				printf("\nError - unable to create renderer : ", SDL_GetError);
			}
			else {
				SDL_SetRenderDrawColor(this->Renderer, 255, 255, 255, 255);

				int ImgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(ImgFlags) && ImgFlags)) {
					printf("\nError - unable to initalise SDL_IMAGE : ", IMG_GetError);
				}
				else if (TTF_Init() == -1) {
					printf("\nError - unable to initalise SDL_ttf : ", TTF_GetError);
				}
				else {
					this->Screen_Surface = SDL_GetWindowSurface(this->Window);
				}
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
					printf("\nError - unable to initalise SDL_mixer : ", Mix_GetError);
				}
				else {
					success = true;
				}
			}
		}
	}
	return success;
}

SDL_Texture* Core::loadTexture(const std::string& path)
{
	//The final texture
	SDL_Texture* newTexture = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(this->Renderer, loadedSurface);
		if (newTexture == nullptr)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

void Core::Load_IMG_Surface(SDL_Surface*& Buff_Surface, SDL_Surface*& Optimized_Surface, bool& success, SDL_Surface*& Class_Member_Surface) {
	if (Buff_Surface == nullptr) {
		printf("\nError - unable to load image : ", IMG_GetError);
	}
	else {
		Optimized_Surface = SDL_ConvertSurface(Buff_Surface, this->Screen_Surface->format, 0);
		if (Optimized_Surface == nullptr) {
			printf("\nError - unable to convert image : ", SDL_GetError);
		}
		else
		{
			Class_Member_Surface = Optimized_Surface;
			success = true;
		}
	}
}

void Core::Load_TTF(TTF_Font*& TextFont, bool& success, std::string& Text, const int& Index, const int& R, const int& G, const int& B) {
	if (TextFont == nullptr) {
		printf("\nError - unable to load TTF file : ", TTF_GetError);
		success = false;
	}
	else {
		SDL_Colour FontColour{ R, G, B };
		if (!this->Game_Textures[Index].Create_TTF(this->Renderer, TextFont, Text, FontColour)) {
			printf("\nError - unable to create TTF texture.");
			success = false;
		}
		else {
			success = true;
		}
	}
}

bool Core::load_media() {
	bool success = false;
	SDL_Surface* Buff_Surface = nullptr;
	SDL_Surface* Optimized_Surface = nullptr;

	for (int i = SURFACES_TEXTURES_ENUM::PLAY_1; i <= SURFACES_TEXTURES_ENUM::PLAY_30; ++i) {
		Buff_Surface = IMG_Load(PATHS::PLAY_PATH.at(i).c_str());
		Load_IMG_Surface(Buff_Surface, Optimized_Surface, success, this->Game_Surfaces[i]);
		this->Game_Textures[i].Create(Optimized_Surface, this->Renderer);
	}

	for (int i = SURFACES_TEXTURES_ENUM::OPTION_1; i <= SURFACES_TEXTURES_ENUM::OPTION_30; ++i) {
		Buff_Surface = IMG_Load(PATHS::OPTIONS_PATH.at(i - SURFACES_TEXTURES_ENUM::OPTION_1).c_str());
		Load_IMG_Surface(Buff_Surface, Optimized_Surface, success, this->Game_Surfaces[i]);
		this->Game_Textures[i].Create(Optimized_Surface, this->Renderer);
	}

	for (int i = SURFACES_TEXTURES_ENUM::QUIT_1; i <= SURFACES_TEXTURES_ENUM::QUIT_30; ++i) {
		Buff_Surface = IMG_Load(PATHS::QUIT_PATH.at(i - SURFACES_TEXTURES_ENUM::QUIT_1).c_str());
		Load_IMG_Surface(Buff_Surface, Optimized_Surface, success, this->Game_Surfaces[i]);
		this->Game_Textures[i].Create(Optimized_Surface, this->Renderer);
	}

	for (int i = SURFACES_TEXTURES_ENUM::COIN_1; i <= SURFACES_TEXTURES_ENUM::COIN_6; ++i) {
		Buff_Surface = IMG_Load(PATHS::COIN_PATH.at(i - SURFACES_TEXTURES_ENUM::COIN_1).c_str());
		Load_IMG_Surface(Buff_Surface, Optimized_Surface, success, this->Game_Surfaces[i]);
		this->Game_Textures[i].Create(Optimized_Surface, this->Renderer);
	}

	Buff_Surface = IMG_Load(PATHS::BACKGROUND_PATH.c_str());
	Load_IMG_Surface(Buff_Surface, Optimized_Surface, success, this->Game_Surfaces[SURFACES_TEXTURES_ENUM::BACKGROUND]);
	this->Game_Textures[SURFACES_TEXTURES_ENUM::BACKGROUND].Create(Optimized_Surface, this->Renderer);

	Buff_Surface = IMG_Load(PATHS::APPLE_PATH.c_str());
	Load_IMG_Surface(Buff_Surface, Optimized_Surface, success, this->Game_Surfaces[SURFACES_TEXTURES_ENUM::APPLE]);
	this->Game_Textures[SURFACES_TEXTURES_ENUM::APPLE].Create(Optimized_Surface, this->Renderer);

	Buff_Surface = IMG_Load(PATHS::SNAKE_PATH.c_str());
	Load_IMG_Surface(Buff_Surface, Optimized_Surface, success, this->Game_Surfaces[SURFACES_TEXTURES_ENUM::SNAKE]);
	this->Game_Textures[SURFACES_TEXTURES_ENUM::SNAKE].Create(Optimized_Surface, this->Renderer);

	Buff_Surface = IMG_Load(PATHS::OBSTACLE_PATH.c_str());
	Load_IMG_Surface(Buff_Surface, Optimized_Surface, success, this->Game_Surfaces[SURFACES_TEXTURES_ENUM::OBSTACLE]);
	this->Game_Textures[SURFACES_TEXTURES_ENUM::OBSTACLE].Create(Optimized_Surface, this->Renderer);

	this->TextFont = TTF_OpenFont(PATHS::FONT_PATH.c_str(), 100);
	Load_TTF(this->TextFont, success, TEXT_TTF::TITLE_TEXT, SURFACES_TEXTURES_ENUM::TITLE_TEXT_BLACK, 61, 61, 59);
	this->TextFont = TTF_OpenFont(PATHS::FONT_PATH.c_str(), 98);
	Load_TTF(this->TextFont, success, TEXT_TTF::TITLE_TEXT, SURFACES_TEXTURES_ENUM::TITLE_TEXT_WHITE, 224, 224, 224);
	this->TextFont = TTF_OpenFont(PATHS::FONT_PATH.c_str(), 50);
	Load_TTF(this->TextFont, success, TEXT_TTF::AUTHOR_TEXT, SURFACES_TEXTURES_ENUM::AUTHOR_TEXT_BLACK, 61, 61, 59);
	Load_TTF(this->TextFont, success, TEXT_TTF::AUTHOR_TEXT, SURFACES_TEXTURES_ENUM::AUTHOR_TEXT_WHITE, 224, 224, 224);
	this->TextFont = TTF_OpenFont(PATHS::FONT_PATH.c_str(), 48);
	Load_TTF(this->TextFont, success, TEXT_TTF::SOUND_ON_TEXT, SURFACES_TEXTURES_ENUM::SOUND_ON_TEXT_NOT_SEL, 224, 224, 224);
	Load_TTF(this->TextFont, success, TEXT_TTF::SOUND_ON_TEXT, SURFACES_TEXTURES_ENUM::SOUND_ON_TEXT_SEL, 239, 228, 179);
	this->TextFont = TTF_OpenFont(PATHS::FONT_PATH.c_str(), 50);
	Load_TTF(this->TextFont, success, TEXT_TTF::SOUND_ON_TEXT, SURFACES_TEXTURES_ENUM::SOUND_ON_TEXT_BLACK, 61, 61, 59);
	this->TextFont = TTF_OpenFont(PATHS::FONT_PATH.c_str(), 48);
	Load_TTF(this->TextFont, success, TEXT_TTF::SOUND_OFF_TEXT, SURFACES_TEXTURES_ENUM::SOUND_OFF_TEXT_NOT_SEL, 224, 224, 224);
	Load_TTF(this->TextFont, success, TEXT_TTF::SOUND_OFF_TEXT, SURFACES_TEXTURES_ENUM::SOUND_OFF_TEXT_SEL, 239, 228, 179);
	this->TextFont = TTF_OpenFont(PATHS::FONT_PATH.c_str(), 50);
	Load_TTF(this->TextFont, success, TEXT_TTF::SOUND_OFF_TEXT, SURFACES_TEXTURES_ENUM::SOUND_OFF_TEXT_BLACK, 61, 61, 59);
	this->TextFont = TTF_OpenFont(PATHS::FONT_PATH.c_str(), 48);
	Load_TTF(this->TextFont, success, TEXT_TTF::MUSIC_ON_TEXT, SURFACES_TEXTURES_ENUM::MUSIC_ON_TEXT_NOT_SEL, 224, 224, 224);
	Load_TTF(this->TextFont, success, TEXT_TTF::MUSIC_ON_TEXT, SURFACES_TEXTURES_ENUM::MUSIC_ON_TEXT_SEL, 239, 228, 179);
	this->TextFont = TTF_OpenFont(PATHS::FONT_PATH.c_str(), 50);
	Load_TTF(this->TextFont, success, TEXT_TTF::MUSIC_ON_TEXT, SURFACES_TEXTURES_ENUM::MUSIC_ON_TEXT_BLACK, 61, 61, 59);
	this->TextFont = TTF_OpenFont(PATHS::FONT_PATH.c_str(), 48);
	Load_TTF(this->TextFont, success, TEXT_TTF::MUSIC_OFF_TEXT, SURFACES_TEXTURES_ENUM::MUSIC_OFF_TEXT_NOT_SEL, 224, 224, 224);
	Load_TTF(this->TextFont, success, TEXT_TTF::MUSIC_OFF_TEXT, SURFACES_TEXTURES_ENUM::MUSIC_OFF_TEXT_SEL, 239, 228, 179);
	this->TextFont = TTF_OpenFont(PATHS::FONT_PATH.c_str(), 50);
	Load_TTF(this->TextFont, success, TEXT_TTF::MUSIC_OFF_TEXT, SURFACES_TEXTURES_ENUM::MUSIC_OFF_TEXT_BLACK, 61, 61, 59);
	this->TextFont = TTF_OpenFont(PATHS::FONT_PATH.c_str(), 48);
	Load_TTF(this->TextFont, success, TEXT_TTF::RANKING_TEXT, SURFACES_TEXTURES_ENUM::RANKING_TEXT_NOT_SEL, 224, 224, 224);
	Load_TTF(this->TextFont, success, TEXT_TTF::RANKING_TEXT, SURFACES_TEXTURES_ENUM::RANKING_TEXT_SEL, 239, 228, 179);
	this->TextFont = TTF_OpenFont(PATHS::FONT_PATH.c_str(), 50);
	Load_TTF(this->TextFont, success, TEXT_TTF::RANKING_TEXT, SURFACES_TEXTURES_ENUM::RANKING_TEXT_BLACK, 61, 61, 59);
	this->TextFont = TTF_OpenFont(PATHS::FONT_PATH.c_str(), 50);
	Load_TTF(this->TextFont, success, TEXT_TTF::CANCEL_TEXT, SURFACES_TEXTURES_ENUM::CANCEL_TEXT_NOT_SEL, 224, 224, 224);
	Load_TTF(this->TextFont, success, TEXT_TTF::CANCEL_TEXT, SURFACES_TEXTURES_ENUM::CANCEL_TEXT_SEL, 239, 228, 179);
	this->TextFont = TTF_OpenFont(PATHS::FONT_PATH.c_str(), 48);
	Load_TTF(this->TextFont, success, TEXT_TTF::CANCEL_TEXT, SURFACES_TEXTURES_ENUM::CANCEL_TEXT_BLACK, 61, 61, 59);
	this->TextFont = TTF_OpenFont(PATHS::FONT_PATH.c_str(), 50);
	Load_TTF(this->TextFont, success, TEXT_TTF::SCORE_TEXT, SURFACES_TEXTURES_ENUM::SCORE_TEXT_BLACK, 61, 61, 59);
	Load_TTF(this->TextFont, success, TEXT_TTF::SCORE_TEXT, SURFACES_TEXTURES_ENUM::SCORE_TEXT_WHITE, 224, 224, 224);
	Load_TTF(this->TextFont, success, TEXT_TTF::TIME_TEXT, SURFACES_TEXTURES_ENUM::TIME_TEXT_BLACK, 61, 61, 59);
	Load_TTF(this->TextFont, success, TEXT_TTF::TIME_TEXT, SURFACES_TEXTURES_ENUM::TIME_TEXT_WHITE, 224, 224, 224);
	Load_TTF(this->TextFont, success, TEXT_TTF::START_TEXT, SURFACES_TEXTURES_ENUM::START_TEXT_BLACK, 61, 61, 59);
	Load_TTF(this->TextFont, success, TEXT_TTF::START_TEXT, SURFACES_TEXTURES_ENUM::START_TEXT_WHITE, 224, 224, 224);
	this->TextFont = TTF_OpenFont(PATHS::FONT_PATH.c_str(), 100);
	Load_TTF(this->TextFont, success, TEXT_TTF::GAME_OVER_TEXT, SURFACES_TEXTURES_ENUM::GAME_OVER_TEXT_BLACK, 61, 61, 59);
	Load_TTF(this->TextFont, success, TEXT_TTF::GAME_OVER_TEXT, SURFACES_TEXTURES_ENUM::GAME_OVER_TEXT_WHITE, 224, 224, 224);
	this->TextFont = TTF_OpenFont(PATHS::FONT_PATH.c_str(), 50);
	SDL_FreeSurface(Buff_Surface);
	SDL_FreeSurface(Optimized_Surface);
	return success;
}

void Core::load_Clips() {
	Set_Clip(this->Game_Clips[CLIPS_ENUM::PLAY], 0, 0, 300, 80);
	Set_Clip(this->Game_Clips[CLIPS_ENUM::OPTION], 0, 0, 300, 80);
	Set_Clip(this->Game_Clips[CLIPS_ENUM::QUIT], 0, 0, 300, 80);

	Set_Clip(this->Game_Clips[CLIPS_ENUM::COIN_1], 0, 0, 32, 32);
	Set_Clip(this->Game_Clips[CLIPS_ENUM::COIN_2], 0, 0, 24, 32);
	Set_Clip(this->Game_Clips[CLIPS_ENUM::COIN_3], 0, 0, 16, 32);
	Set_Clip(this->Game_Clips[CLIPS_ENUM::COIN_4], 0, 0, 5, 32);
	Set_Clip(this->Game_Clips[CLIPS_ENUM::COIN_5], 0, 0, 16, 32);
	Set_Clip(this->Game_Clips[CLIPS_ENUM::COIN_6], 0, 0, 24, 32);

	Set_Clip(this->Game_Clips[CLIPS_ENUM::BACKGROUND], 0, 0, 1920, 1080);

	Set_Clip(this->Game_Clips[CLIPS_ENUM::APPLE], 0, 0, 64, 64);

	Set_Clip(this->Game_Clips[CLIPS_ENUM::SNAKE_TAIL_DOWN], 0, 0, 40, 40);
	Set_Clip(this->Game_Clips[CLIPS_ENUM::SNAKE_TAIL_RIGHT], 0, 41, 40, 39);
	Set_Clip(this->Game_Clips[CLIPS_ENUM::SNAKE_TAIL_LEFT], 40, 0, 40, 40);
	Set_Clip(this->Game_Clips[CLIPS_ENUM::SNAKE_TAIL_UP], 41, 40, 39, 40);
	Set_Clip(this->Game_Clips[CLIPS_ENUM::SNAKE_BODY_VER], 80, 0, 40, 40);
	Set_Clip(this->Game_Clips[CLIPS_ENUM::SNAKE_BODY_HOR], 80, 40, 40, 40);
	Set_Clip(this->Game_Clips[CLIPS_ENUM::SNAKE_HEAD_UP], 120, 0, 40, 40);
	Set_Clip(this->Game_Clips[CLIPS_ENUM::SNAKE_HEAD_DOWN], 121, 40, 39, 40);
	Set_Clip(this->Game_Clips[CLIPS_ENUM::SNAKE_HEAD_RIGHT], 160, 0, 40, 40);
	Set_Clip(this->Game_Clips[CLIPS_ENUM::SNAKE_HEAD_LEFT], 160, 41, 40, 39);
	Set_Clip(this->Game_Clips[CLIPS_ENUM::SNAKE_DN_RIGHT], 200, 1, 40, 40);
	Set_Clip(this->Game_Clips[CLIPS_ENUM::SNAKE_UP_RIGHT], 200, 40, 40, 40);
	Set_Clip(this->Game_Clips[CLIPS_ENUM::SNAKE_UP_LEFT], 241, 0, 39, 40);
	Set_Clip(this->Game_Clips[CLIPS_ENUM::SNAKE_DN_LEFT], 241, 41, 39, 39);

	Set_Clip(this->Game_Clips[CLIPS_ENUM::OBSTACLE], 0, 0, 32, 32);

	for (int i = CLIPS_ENUM::SOUND_BOX; i <= CLIPS_ENUM::RANKING_BOX; ++i) {
		Set_Clip(this->Game_Clips[i], 0, 0, 300, 80);
	}
	Set_Clip(this->Game_Clips[CLIPS_ENUM::RANKING_BOX], 0, 0, 350, 80);
}
