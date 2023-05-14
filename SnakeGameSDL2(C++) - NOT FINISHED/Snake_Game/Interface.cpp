import Interface;
import "SDL.h";
import <iostream>;
import Apple;
import Coin;
import Obstacle;

Interface::Interface() : Quit(false), Game_Menu(this->Game_Textures, this->Game_Clips, this->Game_Textures[SURFACES_TEXTURES_ENUM::TITLE_TEXT_BLACK], 
	this->Game_Textures[SURFACES_TEXTURES_ENUM::TITLE_TEXT_WHITE], this->Game_Textures[SURFACES_TEXTURES_ENUM::AUTHOR_TEXT_BLACK], this->Game_Textures[SURFACES_TEXTURES_ENUM::AUTHOR_TEXT_WHITE]), 
	Game_Snake(this->Window, this->Game_Textures, this->Game_Clips) {
	this->Game_Objects.push_back(std::make_unique<Apple>(this->Game_Textures, this->Game_Clips));
	this->Game_Objects.push_back(std::make_unique<Coin>(this->Game_Textures, this->Game_Clips));
	for (int i = 0; i < 5; ++i) {
		this->Game_Objects.push_back(std::make_unique<Obstacle>(this->Game_Textures, this->Game_Clips));
	}
}

Interface::~Interface() {}

void Interface::Main_Loop() {
	//While application is running
	while (!Quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&this->event) != 0)
		{
			Check_Events();
		}
		this->Game_Snake.Move();
		Render();
		SDL_Delay(75);
	}
}

void Interface::Menu_Operations() {
	if (Game_Menu.Get_Play_Bool()) {
		this->Game_Snake.Start_Timer(SDL_GetTicks64());
		for (auto& Obj : this->Game_Objects) {
			Obj->Interaction(this->Game_Snake);
		}
		if (this->Game_Snake.Render(this->Renderer)) {
			if (this->Game_Snake.Display_GmOv_Statis(this->Renderer, this->TextFont, &this->Game_Textures[SURFACES_TEXTURES_ENUM::SCORE_TEXT_WHITE], &this->Game_Textures[SURFACES_TEXTURES_ENUM::SCORE_TEXT_BLACK],
				&this->Game_Textures[SURFACES_TEXTURES_ENUM::TIME_TEXT_WHITE], &this->Game_Textures[SURFACES_TEXTURES_ENUM::TIME_TEXT_BLACK], &this->Game_Textures[SURFACES_TEXTURES_ENUM::GAME_OVER_TEXT_WHITE], &this->Game_Textures[SURFACES_TEXTURES_ENUM::GAME_OVER_TEXT_BLACK], this->Game_Menu.Return_Cancel_Button())) {
				this->Game_Menu.Reset_Play_Bool();
			}
		}
		else {
			this->Game_Snake.Begining_Text(this->Renderer, &this->Game_Textures[SURFACES_TEXTURES_ENUM::START_TEXT_WHITE],
				&this->Game_Textures[SURFACES_TEXTURES_ENUM::START_TEXT_BLACK]);
			this->Game_Snake.Display_Statis(this->Renderer, this->TextFont, &this->Game_Textures[SURFACES_TEXTURES_ENUM::SCORE_TEXT_WHITE], &this->Game_Textures[SURFACES_TEXTURES_ENUM::SCORE_TEXT_BLACK],
				&this->Game_Textures[SURFACES_TEXTURES_ENUM::TIME_TEXT_WHITE], &this->Game_Textures[SURFACES_TEXTURES_ENUM::TIME_TEXT_BLACK]);
			this->Game_Objects.at(0)->Render(this->Renderer, 400, 200);
			this->Game_Objects.at(1)->Render(this->Renderer, 700, 400);
			this->Game_Objects.at(2)->Render(this->Renderer, 800, 400);
			this->Game_Objects.at(3)->Render(this->Renderer, 200, 400);
			this->Game_Objects.at(4)->Render(this->Renderer, 1700, 500);
			this->Game_Objects.at(5)->Render(this->Renderer, 750, 900);
			this->Game_Objects.at(6)->Render(this->Renderer, 450, 900);
		}
	}
	else if(Game_Menu.Get_Options_Bool()) {
		this->Game_Menu.Render_SubMenu(this->Renderer);
	}
	else if (Game_Menu.Get_Quit_Bool()) {
		this->Quit = true;
	}
	else {
		//this->Game_Snake.Menu_Animation(this->Renderer);
		Game_Menu.Render_Menu(this->Renderer);
	}
}

void Interface::Check_Events() {
	if (!this->Game_Menu.Get_Play_Bool()) {
		this->Game_Menu.Check_Events(this->event);
	}
	else {
		this->Game_Snake.Check_Events(this->event);
		this->Game_Menu.Check_Events_Return_Cancel_Button(this->event);
	}
}

void Interface::Render() {
	SDL_RenderClear(this->Renderer);
	this->Game_Textures[SURFACES_TEXTURES_ENUM::BACKGROUND].Render(0, 0, this->Renderer, &this->Game_Clips[CLIPS_ENUM::BACKGROUND], 1);
	Menu_Operations();
	SDL_RenderPresent(this->Renderer);
}