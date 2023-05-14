import Menu;
import Core;

Menu::Menu() : Play_Bool(false), Option_Bool(false), Quit_Bool(false), Sound_Bool(false), Music_Bool(false), Ranking_Bool(false) {}

Menu::Menu(Texture Game_Textures[SURFACES_TEXTURES_ENUM::TOTAL], SDL_Rect Game_Clips[CLIPS_ENUM::TOTAL], Texture& Title_TEXT_BLACK, Texture& Title_TEXT_WHITE, Texture& Author_TEXT_BLACK, Texture& Author_TEXT_WHITE) : Play_Bool(false), Option_Bool(false), Quit_Bool(false), Sound_Bool(false), Music_Bool(false), Ranking_Bool(false) {
	this->Title_TEXT_BLACK = &Title_TEXT_BLACK;
	this->Title_TEXT_WHITE = &Title_TEXT_WHITE;
	this->Author_TEXT_BLACK = &Author_TEXT_BLACK;
	this->Author_TEXT_WHITE = &Author_TEXT_WHITE;

	Button Buff_Play{ Game_Textures, Game_Clips[CLIPS_ENUM::PLAY], SURFACES_TEXTURES_ENUM::PLAY_1, SURFACES_TEXTURES_ENUM::PLAY_30};
	Game_buttons[BUTTON_ENUM::PLAY] = Buff_Play;
	Button Buff_Option{ Game_Textures, Game_Clips[CLIPS_ENUM::OPTION], SURFACES_TEXTURES_ENUM::OPTION_1, SURFACES_TEXTURES_ENUM::OPTION_30 };
	Game_buttons[BUTTON_ENUM::OPTION] = Buff_Option;
	Button Buff_Quit{ Game_Textures, Game_Clips[CLIPS_ENUM::QUIT], SURFACES_TEXTURES_ENUM::QUIT_1, SURFACES_TEXTURES_ENUM::QUIT_30 };
	Game_buttons[BUTTON_ENUM::QUIT] = Buff_Quit;
	Button Buff_Sound_ON{ Game_Textures[SURFACES_TEXTURES_ENUM::SOUND_ON_TEXT_NOT_SEL], Game_Textures[SURFACES_TEXTURES_ENUM::SOUND_ON_TEXT_SEL], Game_Textures[SURFACES_TEXTURES_ENUM::SOUND_ON_TEXT_BLACK], Game_Clips[CLIPS_ENUM::SOUND_BOX] };
	Game_buttons[BUTTON_ENUM::SOUND_ON] = Buff_Sound_ON;
	Button Buff_Sound_OFF{ Game_Textures[SURFACES_TEXTURES_ENUM::SOUND_OFF_TEXT_NOT_SEL], Game_Textures[SURFACES_TEXTURES_ENUM::SOUND_OFF_TEXT_SEL], Game_Textures[SURFACES_TEXTURES_ENUM::SOUND_OFF_TEXT_BLACK], Game_Clips[CLIPS_ENUM::SOUND_BOX] };
	Game_buttons[BUTTON_ENUM::SOUND_OFF] = Buff_Sound_OFF;
	Button Buff_Music_ON{ Game_Textures[SURFACES_TEXTURES_ENUM::MUSIC_ON_TEXT_NOT_SEL], Game_Textures[SURFACES_TEXTURES_ENUM::MUSIC_ON_TEXT_SEL], Game_Textures[SURFACES_TEXTURES_ENUM::MUSIC_ON_TEXT_BLACK], Game_Clips[CLIPS_ENUM::MUSIC_BOX] };
	Game_buttons[BUTTON_ENUM::MUSIC_ON] = Buff_Music_ON;
	Button Buff_Music_OFF{ Game_Textures[SURFACES_TEXTURES_ENUM::MUSIC_OFF_TEXT_NOT_SEL], Game_Textures[SURFACES_TEXTURES_ENUM::MUSIC_OFF_TEXT_SEL], Game_Textures[SURFACES_TEXTURES_ENUM::MUSIC_OFF_TEXT_BLACK], Game_Clips[CLIPS_ENUM::MUSIC_BOX] };
	Game_buttons[BUTTON_ENUM::MUSIC_OFF] = Buff_Music_OFF;
	Button Buff_Ranking{ Game_Textures[SURFACES_TEXTURES_ENUM::RANKING_TEXT_NOT_SEL], Game_Textures[SURFACES_TEXTURES_ENUM::RANKING_TEXT_SEL], Game_Textures[SURFACES_TEXTURES_ENUM::RANKING_TEXT_BLACK], Game_Clips[CLIPS_ENUM::RANKING_BOX] };
	Game_buttons[BUTTON_ENUM::RANKING] = Buff_Ranking;
	Button Buff_Cancel{ Game_Textures[SURFACES_TEXTURES_ENUM::CANCEL_TEXT_NOT_SEL], Game_Textures[SURFACES_TEXTURES_ENUM::CANCEL_TEXT_SEL], Game_Textures[SURFACES_TEXTURES_ENUM::CANCEL_TEXT_BLACK], Game_Clips[CLIPS_ENUM::RANKING_BOX] };
	Game_buttons[BUTTON_ENUM::CANCEL] = Buff_Cancel;
} 

Menu::~Menu() {
	this->Title_TEXT_BLACK = nullptr;
	this->Title_TEXT_WHITE = nullptr;
	this->Author_TEXT_BLACK = nullptr;
	this->Author_TEXT_WHITE = nullptr;
};

void Menu::Check_Events(SDL_Event Event) {
	if (!this->Option_Bool) {
		for (int i = 0; i < BUTTON_ENUM::SOUND_ON; ++i) {
			this->Game_buttons[i].Check_Event(&Event);
		}
		Menu_Actions();
	}
	else {
		for (int i = BUTTON_ENUM::SOUND_ON; i < BUTTON_ENUM::TOTAL; ++i) {
			this->Game_buttons[i].Check_Event(&Event);
		}
		SubMenu_Actions();
	};
	Reset_Buttons();
}
void Menu::Render_Menu(SDL_Renderer* Renderer) {
	Render_Title_Author(Renderer);
	this->Game_buttons[BUTTON_ENUM::PLAY].Render(1325, 350, Renderer);
	this->Game_buttons[BUTTON_ENUM::OPTION].Render(1325, 450, Renderer);
	this->Game_buttons[BUTTON_ENUM::QUIT].Render(1325, 550, Renderer);
}
bool Menu::Get_Play_Bool() {
	return this->Play_Bool;
}
bool Menu::Get_Options_Bool() {
	return this->Option_Bool;
}
bool Menu::Get_Quit_Bool() {
	return this->Quit_Bool;
}

void Menu::Menu_Actions() {
	if (this->Game_buttons[BUTTON_ENUM::PLAY].Get_is_Clicked() == true) {
		this->Play_Bool = true;
	}
	else if (this->Game_buttons[BUTTON_ENUM::OPTION].Get_is_Clicked() == true) {
		this->Option_Bool = true;
	}
	else if (this->Game_buttons[BUTTON_ENUM::QUIT].Get_is_Clicked() == true) {
		this->Quit_Bool = true;
	}
}

void Menu::Reset_Buttons() {
	for (int i = BUTTON_ENUM::PLAY; i < BUTTON_ENUM::TOTAL; ++i) {
		this->Game_buttons[i].Reset_is_Clicked();
	}
}

void Menu::Render_SubMenu(SDL_Renderer* Renderer) {
	Render_Title_Author(Renderer);
	if (this->Sound_Bool) {
		this->Game_buttons[BUTTON_ENUM::SOUND_OFF].Render(1325, 350, Renderer);
	}
	else {
		this->Game_buttons[BUTTON_ENUM::SOUND_ON].Render(1325, 350, Renderer);
	}
	if (this->Music_Bool) {
		this->Game_buttons[BUTTON_ENUM::MUSIC_OFF].Render(1325, 450, Renderer);
	}
	else {
		this->Game_buttons[BUTTON_ENUM::MUSIC_ON].Render(1325, 450, Renderer);
	}
	this->Game_buttons[BUTTON_ENUM::RANKING].Render(1325, 550, Renderer);
	this->Game_buttons[BUTTON_ENUM::CANCEL].Render(1325, 650, Renderer);
}

void Menu::Render_Title_Author(SDL_Renderer* Renderer) {
	this->Title_TEXT_BLACK->Render(1200, 200, Renderer, nullptr, 0);
	this->Title_TEXT_WHITE->Render(1200, 210, Renderer, nullptr, 0);
	this->Author_TEXT_BLACK->Render(1200, 900, Renderer, nullptr, 0);
	this->Author_TEXT_WHITE->Render(1200, 910, Renderer, nullptr, 0);
}

void Menu::Reset_Play_Bool() {
	this->Play_Bool = false;
}

void Menu::Reset_Option_Bool() {
	this->Option_Bool = false;
}

void Menu::SubMenu_Actions() {
	Button_ON_OFF(BUTTON_ENUM::SOUND_ON, this->Sound_Bool);
	Button_ON_OFF(BUTTON_ENUM::MUSIC_ON, this->Music_Bool);
	if (this->Game_buttons[BUTTON_ENUM::RANKING].Get_is_Clicked() == true) {

	}
	else {

	}
	if (this->Game_buttons[BUTTON_ENUM::CANCEL].Get_is_Clicked() == true) {
		Reset_Option_Bool();
	}
}

void Menu::Button_ON_OFF(const int& Button_Index, bool& Button_Bool) {
	if (!Button_Bool) {
		if (this->Game_buttons[Button_Index].Get_is_Clicked() == true) {
			Button_Bool = true;
		}
	}
	else {
		if (this->Game_buttons[Button_Index].Get_is_Clicked() == true) {
			Button_Bool = false;
		}
	}
}

void Menu::Button_GmOv_Menu() {
	if (this->Game_buttons[BUTTON_ENUM::CANCEL].Get_is_Clicked() == true) {
		Reset_Option_Bool();
	}
}

Button& Menu::Return_Cancel_Button() {
	return this->Game_buttons[BUTTON_ENUM::CANCEL];
}

void Menu::Check_Events_Return_Cancel_Button(SDL_Event Event) {
	this->Game_buttons[BUTTON_ENUM::CANCEL].Check_Event(&Event);
}