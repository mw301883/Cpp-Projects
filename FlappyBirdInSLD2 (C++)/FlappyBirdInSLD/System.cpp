#include "System.h"
#include <iostream>

void Set_Clip(SDL_Rect& Clip, const int& x, const int& y, const int& w, const int& h) {
	Clip.x = x;
	Clip.y = y;
	Clip.w = w;
	Clip.h = h;
}

System::System() : Window(nullptr), Renderer(nullptr), TextFont(nullptr), Width(360), Height(640) {
	this->Surfaces[Screen_SURFACE] = nullptr;
	this->Surfaces[Background_SURFACE] = nullptr;
	this->Surfaces[Menu_SURFACE] = nullptr;
	this->Surfaces[Bird_SURFACE] = nullptr;
	this->Surfaces[Pipe_SURFACE] = nullptr;

	Set_Clip(this->Texture_Clips[CLIP_BACKGROUND_DAY], 0, 0, 360, 640);
	Set_Clip(this->Texture_Clips[CLIP_BACKGROUND_NIGHT], 360, 0, 360, 640);

	Set_Clip(this->Texture_Clips[CLIP_MENU_START_DARK], 0, 0, 200, 66);
	Set_Clip(this->Texture_Clips[CLIP_MENU_OPTIONS_DARK], 0, 65, 200, 66);
	Set_Clip(this->Texture_Clips[CLIP_MENU_QUIT_DARK], 0, 130, 200, 66);
	Set_Clip(this->Texture_Clips[CLIP_MENU_START_LIGHT], 200, 0, 200, 66);
	Set_Clip(this->Texture_Clips[CLIP_MENU_OPTIONS_LIGHT], 200, 65, 200, 66);
	Set_Clip(this->Texture_Clips[CLIP_MENU_QUIT_LIGHT], 200, 130, 200, 66);

	Set_Clip(this->Texture_Clips[CLIP_BIRD_MOVE_UP], 0, 0, 100, 89);
	Set_Clip(this->Texture_Clips[CLIP_BIRD_MOVE_DOWN], 100, 0, 100, 89);
	Set_Clip(this->Texture_Clips[CLIP_BIRD_DEAD_UP], 200, 0, 100, 89);
	Set_Clip(this->Texture_Clips[CLIP_BIRD_DEAD_DOWN], 300, 0, 100, 89);

	Set_Clip(this->Texture_Clips[CLIP_PIPE_DOWN_HIGH], 0, 0, 110, 640);
	Set_Clip(this->Texture_Clips[CLIP_PIPE_DOWN_MEDIUM], 115, 0, 110, 640);
	Set_Clip(this->Texture_Clips[CLIP_PIPE_DOWN_LOW], 240, 0, 110, 640);
	Set_Clip(this->Texture_Clips[CLIP_PIPE_UP_HIGH], 365, 0, 110, 640);
	Set_Clip(this->Texture_Clips[CLIP_PIPE_UP_MEDIUM], 500, 0, 110, 640);
	Set_Clip(this->Texture_Clips[CLIP_PIPE_UP_LOW], 630, 0, 110, 640);
	Set_Clip(this->Texture_Clips[CLIP_PIPE_GAP_LOW], 770, 0, 110, 640);
	Set_Clip(this->Texture_Clips[CLIP_PIPE_GAP_HIGH], 915, 0, 110, 640);

	this->Text[Title_TEXT] = "Flappy Bird";
	this->Text[Background_TEXT] = "Background type : ";
	this->Text[Day_TEXT] = "Day";
	this->Text[Night_TEXT] = "Night";
	this->Text[Sound_TEXT] = "Sound : ";
	this->Text[Selector_Right_TEXT] = ">";
	this->Text[Selector_Left_TEXT] = "<";
	this->Text[On_TEXT] = "ON";
	this->Text[Off_TEXT] = "OFF";
	this->Text[Score_TEXT] = "SCORE: ";
	this->Text[Score_Num_TEXT] = "0";
	this->Text[Author_TEXT] = "Author : Michal Wieczorek";
	this->Text[Instruction_One_TEXT] = "Press SPACE";
	this->Text[Instruction_Two_TEXT] = "to begin and Fly!";
}

System::~System() {

	SDL_FreeSurface(this->Surfaces[Screen_SURFACE]);
	this->Surfaces[Screen_SURFACE] = nullptr;
	SDL_FreeSurface(this->Surfaces[Background_SURFACE]);
	this->Surfaces[Background_SURFACE] = nullptr;
	SDL_FreeSurface(this->Surfaces[Menu_SURFACE]);
	this->Surfaces[Menu_SURFACE] = nullptr;
	SDL_FreeSurface(this->Surfaces[Bird_SURFACE]);
	this->Surfaces[Bird_SURFACE] = nullptr;
	SDL_FreeSurface(this->Surfaces[Pipe_SURFACE]);
	this->Surfaces[Pipe_SURFACE] = nullptr;
	TTF_CloseFont(this->TextFont);
	this->TextFont = nullptr;
	SDL_DestroyRenderer(this->Renderer);
	this->Renderer = nullptr;
	SDL_DestroyWindow(this->Window);
	this->Window = nullptr;

	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

//Game Loop (core of the application)
void System::Play() {
	//Game Objects
	SDL_Event Game_Event;
	Selector Selector_Background_Left, Selector_Background_Right, Selector_Sound_Left, Selector_Sound_Right;
	Sound Background_Sound, Bird_Sound, Hit_Sound;

	Menu Game_Menu(this->Texture_Clips);
	Background Game_Background(this->Texture_Clips);
	Bird Game_Bird(this->Texture_Clips);
	Pipe Game_Pipes[PIPE_TOTAL];
	Game_Pipe_Init(this->Texture_Clips, Game_Pipes);

	std::string Background_Path{ "FlappyBirdGraphics/Background_Bind.png" }, Menu_Path{ "FlappyBirdGraphics/Game_Menu.png" },
		Bird_Path{ "FlappyBirdGraphics/Bird_Frames_smaller.png" }, Pipe_Path{ "FlappyBirdGraphics/Pipes_Frames.png" }, 
		TTF_Path{ "FlappyBirdTTF/Zippy.ttf" }, Background_Sound_Path{ "FlappyBirdSounds/choco birds run (online-audio-converter.com).wav" },
		Bird_Sound_Path{ "FlappyBirdSounds/GUI Sound Effects_071.wav" }, Hit_Sound_Path{ "FlappyBirdSounds/Girl_Scream (online-audio-converter.com).wav" };

	bool Program_Quit = false, CurrentPipe = true, Background_Move = true, loadedScore = true, isQuit = false, EndGame = false, PlayStartSound = true, Sound_Semaphore = true, Game_Start = false;

	int ScrolingXPos = 360, Pipe_Index = 0, Score = 0, Game_Delay = 50000;;
	
	//Setting selector objects used in OPTIONS page
	Selector_Background_Left.Set_Selector(100, 150, 30, 30);
	Selector_Background_Right.Set_Selector(250, 150, 30, 30);
	Selector_Sound_Left.Set_Selector(100, 250, 30, 30);
	Selector_Sound_Right.Set_Selector(250, 250, 30, 30);
	
	//Game Loop
	if (!Initialisation()) {
		std::cout << "\nError encountered during initialisation process.";
	}
	else {
		if (!Load_Media(Background_Path, Menu_Path, Bird_Path, Pipe_Path, TTF_Path, this->TextFont)) {
			std::cout << "\nError during images loading.";
		}
		else {
			this->TextFont = TTF_OpenFont(TTF_Path.c_str(), 50);
			//Loading Game Sounds
			Background_Sound.Load_Music(Background_Sound_Path);
			Bird_Sound.Load_Chunk(Bird_Sound_Path);
			Hit_Sound.Load_Chunk(Hit_Sound_Path);

			Background_Sound.Play_Music();

			while (!Program_Quit) {
				//Loop which checks User action when the application is running
				while (SDL_PollEvent(&Game_Event)) {
					if (Game_Event.type == SDL_QUIT) {
						Program_Quit = true;
					}
					if (Game_Menu.GetStart()) {
						//Checking User actions during GamePlay
						if (Game_Start) {
							Game_Bird.CheckEvent(&Game_Event);
							Game_Menu.CheckEventsQuit(&Game_Event);
						}
						else {
							Game_Begin_Communicate(&Game_Event, Game_Start);
						}
					}
					else if (Game_Menu.GetOptions()) {
						//Checking User actions on OPTIONS page
						Selector_Background_Left.Action(&Game_Event);
						Selector_Background_Right.Action(&Game_Event);
						Selector_Sound_Left.Action(&Game_Event);
						Selector_Sound_Right.Action(&Game_Event);
						Game_Menu.CheckEventsQuit(&Game_Event);
					}
					else {
						//Checking User actions on the main menu page
						Game_Menu.CheckEvents(&Game_Event);
					}
				}
				//Setting game objects position during GamePlay
				if (Game_Menu.GetStart() && Game_Start) {
					Game_Bird.Move(this->Height);
					Game_Pipes[Pipe_Index].Move(this->Width, CurrentPipe);
				}
				
				SDL_SetRenderDrawColor(this->Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(this->Renderer);
				//Actions during GamePlay
				if (Game_Menu.GetStart()) {
					if (Game_Start) {
						if (PlayStartSound) {
							Bird_Sound.Play_Chunk();
							PlayStartSound = false;
						}

						//Reset all game objects settings
						if (Game_Bird.is_End(EndGame) || EndGame) {
							if (isQuit) {
								for (int x = 0; x < PIPE_TOTAL; ++x) {
									Game_Pipes[x].ResetPipe();
									Game_Pipes[x].Set_Const_Counter(10);
								}
								Background_Move = true;
								Game_Delay = 50000;
								Score = 0;
								this->Text[Score_Num_TEXT] = Score;
								isQuit = false;
								EndGame = false;
								PlayStartSound = true;
								Game_Start = false;
								Game_Bird.Reset_Bird();
								Game_Menu.Reset_Start();
								Game_Menu.Reset_Quit();
							}
							//Render the final Score of the User when the game is over
							else {
								Game_Background.Render_Scrolling(this->Textures[Background_TEXTURE], Renderer, ScrolingXPos);
								this->Textures[Score_Fond_TEXTURE].Render(80, 200, this->Renderer);
								this->Textures[Score_Num_Fond_TEXTURE].Render(200, 200, this->Renderer);
								Game_Menu.RenderQuit(this->Textures[Menu_TEXTURE], this->Renderer);
								QuitAction(isQuit, Game_Menu);
							}
						}
						else {

							//Change Speed of Game after every 10000 frames
							if (Game_Delay == 40000 || Game_Delay == 30000 || Game_Delay == 20000 || Game_Delay == 10000 || Game_Delay == 0) {
								for (int x = 0; x < PIPE_TOTAL; ++x) {
									Game_Pipes[x].Set_Const_Counter(Game_Speed_Controller(Game_Delay));
								}
							}
							--Game_Delay;
							//Choosing random Pipe object
							if (CurrentPipe) {
								Pipe_Index = Random_Index();
							}
							//Controlling Background behaviour
							if (Background_Move) {
								Game_Background.Render_Scrolling(this->Textures[Background_TEXTURE], this->Renderer, ScrolingXPos);
							}
							else {
								Game_Background.Render_Static(this->Textures[Background_TEXTURE], this->Renderer);
							}
							//Checking Collisions fo game objects
							if (!CurrentPipe) {
								Game_Pipes[Pipe_Index].Render(this->Textures[Pipe_TEXTURE], this->Renderer);
								if (Game_Bird.Collision_Detection(Game_Pipes[Pipe_Index].GetX(), Game_Pipes[Pipe_Index].Get_ColliderHight_Up(), Game_Pipes[Pipe_Index].Get_ColliderHight_Down(), Game_Pipes[Pipe_Index].Get_is_Double_Collision_Area())) {
									Hit_Sound.Play_Chunk();
									Background_Move = false;
								}
							}
							Game_Bird.Render(this->Textures[Bird_TEXTURE], Renderer);

							Score += 1;
							this->Text[Score_Num_TEXT] = std::to_string(Score / 5);
							Load_TTF(this->TextFont, loadedScore, this->Text[Score_Num_TEXT], Score_Num_Fond_TEXTURE);
							if (!loadedScore) {
								Game_Menu.Reset_Start();
							}
							//Rendering actual Score Points
							this->Textures[Score_Fond_TEXTURE].Render(100, 30, this->Renderer);
							this->Textures[Score_Num_Fond_TEXTURE].Render(220, 30, this->Renderer);
						}
					}
					else {
						//Rendering Game Instruction display in the beggining of every GamePlay
						Game_Background.Render_Scrolling(this->Textures[Background_TEXTURE], this->Renderer, ScrolingXPos);
						this->Textures[Instruction_One_Fond_TEXTURE].Render(75, 200, this->Renderer);
						this->Textures[Instruction_Two_Fond_TEXTURE].Render(60, 250, this->Renderer);
					}
				}
				//Actions on the OPTIONS page
				else if (Game_Menu.GetOptions()) {
					Game_Background.Render_Static(this->Textures[Background_TEXTURE], this->Renderer);
					//Rendering textures
					this->Textures[Background_Fond_TEXTURE].Render(50, 100, this->Renderer);
					this->Textures[Selector_Left_Fond_TEXTURE].Render(100, 150, this->Renderer);
					this->Textures[Selector_Right_Fond_TEXTURE].Render(250, 150, this->Renderer);

					//Checking User's changes in Game Settings

					if (Selector_Background_Left.GetisClicked() || Selector_Background_Right.GetisClicked()) {
						this->Textures[Night_Fond_TEXTURE].Render(150, 150, this->Renderer);
						Game_Background.SetNight();
					}
					else if (Selector_Background_Left.GetisClicked() || !Selector_Background_Right.GetisClicked()) {
						this->Textures[Day_Fond_TEXTURE].Render(150, 150, this->Renderer);
						Game_Background.SetDay();
					}

					this->Textures[Sound_Fond_TEXTURE].Render(50, 200, this->Renderer);
					this->Textures[Selector_Left_Fond_TEXTURE].Render(100, 250, this->Renderer);
					this->Textures[Selector_Right_Fond_TEXTURE].Render(250, 250, this->Renderer);

					if (Selector_Sound_Left.GetisClicked() || Selector_Sound_Right.GetisClicked()) {
						this->Textures[Off_Fond_TEXTURE].Render(150, 250, this->Renderer);
						if (Sound_Semaphore) {
							Background_Sound.Stop_Music();
							Bird_Sound.Turn_Off();
							Hit_Sound.Turn_Off();
							Sound_Semaphore = false;
						}
					}
					else {
						this->Textures[On_Fond_TEXTURE].Render(150, 250, this->Renderer);
						if (!Sound_Semaphore) {
							Background_Sound.Play_Music();
							Bird_Sound.Turn_On();
							Hit_Sound.Turn_On();
							Sound_Semaphore = true;
						}
					}

					Game_Menu.RenderQuit(this->Textures[Menu_TEXTURE], this->Renderer);
					QuitAction(isQuit, Game_Menu);
				}
				//Closing Program
				else if (Game_Menu.GetQuit()) {
					Program_Quit = true;
				}
				else {
					//Rendering main menu
					Game_Background.Render_Scrolling(this->Textures[Background_TEXTURE], this->Renderer, ScrolingXPos);
					Game_Menu.Render(this->Textures[Menu_TEXTURE], this->Renderer);
					this->Textures[Title_Fond_TEXTURE].Render(50, 35, this->Renderer);
					this->Textures[Author_Fond_TEXTURE].Render(150, 600, this->Renderer);
				}

				SDL_RenderPresent(this->Renderer);
			}
		}
	}
}

bool System::Initialisation() {
	bool success = false;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		std::cout << "\nError SDL could not be inistalised : " << SDL_GetError;
	}
	else {
		this->Window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->Width, this->Height, SDL_WINDOW_SHOWN);
		if (this->Window == nullptr) {
			std::cout << "\nError - unable to create window : " << SDL_GetError;
		}
		else {
			this->Renderer = SDL_CreateRenderer(this->Window, -1, SDL_RENDERER_ACCELERATED);
			if (this->Renderer == nullptr) {
				std::cout << "\nError - unable to create renderer : " << SDL_GetError;
			}
			else {
				SDL_SetRenderDrawColor(this->Renderer, 255, 255, 255, 255);

				int ImgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(ImgFlags) && ImgFlags)) {
					std::cout << "\nError - unable to initalise SDL_IMAGE : " << IMG_GetError;
				}
				else if (TTF_Init() == -1) {
					std::cout << "\nError - unable to initalise SDL_ttf : " << TTF_GetError;
				}
				else {
					this->Surfaces[Screen_SURFACE] = SDL_GetWindowSurface(this->Window);
				}
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
					std::cout << "\nError - unable to initalise SDL_mixer : " << Mix_GetError;
				}
				else {
					success = true;
				}
			}
		}
	}
	return success;
}

void System::Load_IMG_Surface(SDL_Surface*& Buff_Surface, SDL_Surface*& Optimized_Surface, bool& success, SDL_Surface*& Class_Member_Surface) {
	if (Buff_Surface == nullptr) {
		std::cout << "\nError - unable to load image : " << IMG_GetError;
	}
	else {
		Optimized_Surface = SDL_ConvertSurface(Buff_Surface, this->Surfaces[Screen_SURFACE]->format, 0);
		if (Optimized_Surface == nullptr) {
			std::cout << "\nError - unable to convert image : " << SDL_GetError;
		}
		else
		{
			Class_Member_Surface = Optimized_Surface;
			success = true;
		}
	}
}

void System::Load_TTF(TTF_Font*& TextFont, bool& success, std::string& Text, TEXTURE_ENUM Index) {
	if (TextFont == nullptr) {
		std::cout << "\nError - unable to load TTF file : " << TTF_GetError;
		success = false;
	}
	else {
		SDL_Colour FontColour{ 0, 0, 0 };
		if (!this->Textures[Index].Create_TTF(this->Renderer, TextFont, Text, FontColour)) {
			std::cout << "\nError - unable to create TTF texture.";
			success = false;
		}
		else {
			success = true;
		}
	}
}

bool System::Load_Media(std::string& Background_Path, std::string& Menu_Path, std::string& Bird_Path, std::string& Pipe_Path, std::string& TTF_Path, TTF_Font*& TextFont) {
	bool success = false;
	SDL_Surface* Buff_Surface = IMG_Load(Background_Path.c_str());
	SDL_Surface* Optimized_Surface = nullptr;
	Load_IMG_Surface(Buff_Surface, Optimized_Surface, success, this->Surfaces[Background_SURFACE]);
	this->Textures[Background_TEXTURE].Create(this->Surfaces[Background_SURFACE], this->Renderer);

	Buff_Surface = IMG_Load(Menu_Path.c_str());
	Load_IMG_Surface(Buff_Surface, Optimized_Surface, success, this->Surfaces[Menu_SURFACE]);
	this->Textures[Menu_TEXTURE].Create(Optimized_Surface, this->Renderer);

	Buff_Surface = IMG_Load(Bird_Path.c_str());
	Load_IMG_Surface(Buff_Surface, Optimized_Surface, success, this->Surfaces[Bird_SURFACE]);
	this->Textures[Bird_TEXTURE].Create(Optimized_Surface, this->Renderer);

	Buff_Surface = IMG_Load(Pipe_Path.c_str());
	Load_IMG_Surface(Buff_Surface, Optimized_Surface, success, this->Surfaces[Pipe_SURFACE]);
	this->Textures[Pipe_TEXTURE].Create(Optimized_Surface, this->Renderer);


	TextFont = TTF_OpenFont(TTF_Path.c_str(), 75);
	Load_TTF(this->TextFont, success, this->Text[Title_TEXT], Title_Fond_TEXTURE);

	TextFont = TTF_OpenFont(TTF_Path.c_str(), 50);
	Load_TTF(this->TextFont, success, this->Text[Background_TEXT], Background_Fond_TEXTURE);

	TextFont = TTF_OpenFont(TTF_Path.c_str(), 50);
	Load_TTF(this->TextFont, success, this->Text[Day_TEXT], Day_Fond_TEXTURE);

	TextFont = TTF_OpenFont(TTF_Path.c_str(), 50);
	Load_TTF(this->TextFont, success, this->Text[Night_TEXT], Night_Fond_TEXTURE);

	TextFont = TTF_OpenFont(TTF_Path.c_str(), 50);
	Load_TTF(this->TextFont, success, this->Text[Selector_Right_TEXT], Selector_Right_Fond_TEXTURE);

	TextFont = TTF_OpenFont(TTF_Path.c_str(), 50);
	Load_TTF(this->TextFont, success, this->Text[Selector_Left_TEXT], Selector_Left_Fond_TEXTURE);

	TextFont = TTF_OpenFont(TTF_Path.c_str(), 50);
	Load_TTF(this->TextFont, success, this->Text[Sound_TEXT], Sound_Fond_TEXTURE);

	TextFont = TTF_OpenFont(TTF_Path.c_str(), 50);
	Load_TTF(this->TextFont, success, this->Text[On_TEXT], On_Fond_TEXTURE);

	TextFont = TTF_OpenFont(TTF_Path.c_str(), 50);
	Load_TTF(this->TextFont, success, this->Text[Off_TEXT], Off_Fond_TEXTURE);

	TextFont = TTF_OpenFont(TTF_Path.c_str(), 50);
	Load_TTF(this->TextFont, success, this->Text[Score_TEXT], Score_Fond_TEXTURE);

	TextFont = TTF_OpenFont(TTF_Path.c_str(), 50);
	Load_TTF(this->TextFont, success, this->Text[Score_Num_TEXT], Score_Num_Fond_TEXTURE);

	TextFont = TTF_OpenFont(TTF_Path.c_str(), 25);
	Load_TTF(this->TextFont, success, this->Text[Author_TEXT], Author_Fond_TEXTURE);

	TextFont = TTF_OpenFont(TTF_Path.c_str(), 50);
	Load_TTF(this->TextFont, success, this->Text[Instruction_One_TEXT], Instruction_One_Fond_TEXTURE);

	TextFont = TTF_OpenFont(TTF_Path.c_str(), 50);
	Load_TTF(this->TextFont, success, this->Text[Instruction_Two_TEXT], Instruction_Two_Fond_TEXTURE);

	SDL_FreeSurface(Buff_Surface);
	return success;
}

SDL_Window* System::GetWindow() {
	return this->Window;
}

SDL_Renderer* System::GetRenderer() {
	return this->Renderer;
}

SDL_Surface* System::GetScreenSurface() {
	return this->Surfaces[Screen_SURFACE];
}

SDL_Surface* System::GetBackgroundSurface() {
	return this->Surfaces[Background_SURFACE];
}

SDL_Surface* System::GetMenuSurface() {
	return this->Surfaces[Menu_SURFACE];
}

SDL_Surface* System::GetBirdSurface() {
	return this->Surfaces[Bird_SURFACE];
}

SDL_Surface* System::GetPipeSurface() {
	return this->Surfaces[Pipe_SURFACE];
}

Texture System::GetBackgroundTexture() {
	return this->Textures[Background_TEXTURE];
}

Texture System::GetMenuTexture() {
	return this->Textures[Menu_TEXTURE];
}

Texture System::GetBirdTexture() {
	return this->Textures[Bird_TEXTURE];
}

Texture System::GetPipeTexture() {
	return this->Textures[Pipe_TEXTURE];
}



void System::Game_Begin_Communicate(SDL_Event* Game_Event, bool& Game_Start) {
	if (Game_Event->key.keysym.sym == SDLK_SPACE) {
		Game_Start = true;
	}
}



int Game_Speed_Controller(int& Game_Delay) {
	if (Game_Delay == 40000) {
		return 6;
	}
	else if (Game_Delay == 30000) {
		return 5;
	}
	else if (Game_Delay == 20000) {
		return 4;
	}
	else if (Game_Delay == 10000) {
		return 3;
	}
	else if (Game_Delay == 0) {
		return 2;
	}
}