import Interface;
import "SDL.h";
import <iostream>;
import Apple;
import Coin;
import Obstacle;
import Sound;
import <filesystem>;
import <fstream>;
import <time.h>;
import <iomanip>;
import External_Functions;

Interface::Interface() : Quit(false), Game_Menu(this->Game_Textures, this->Game_Clips, this->Game_Textures[SURFACES_TEXTURES_ENUM::TITLE_TEXT_BLACK], 
	this->Game_Textures[SURFACES_TEXTURES_ENUM::TITLE_TEXT_WHITE], this->Game_Textures[SURFACES_TEXTURES_ENUM::AUTHOR_TEXT_BLACK], this->Game_Textures[SURFACES_TEXTURES_ENUM::AUTHOR_TEXT_WHITE]), 
	Game_Snake(this->Window, this->Game_Textures, this->Game_Clips) {
	this->Menu_Theme.Load_Music(PATHS::MENU_THEME_PATH);
	this->Game_Objects.push_back(std::make_unique<Apple>(this->Game_Textures, this->Game_Clips));
	this->Game_Objects.push_back(std::make_unique<Coin>(this->Game_Textures, this->Game_Clips));
	for (int i = 0; i < 5; ++i) {
		this->Game_Objects.push_back(std::make_unique<Obstacle>(this->Game_Textures, this->Game_Clips));
	}
}

Interface::~Interface() {}

void Interface::Main_Loop() {
	this->Menu_Theme.Play_Music();
	while (!Quit)
	{
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
		Play();
	}
	else if(Game_Menu.Get_Options_Bool()) {
		this->Game_Menu.Render_SubMenu(this->Renderer, this->TextFont);
	}
	else if (Game_Menu.Get_Quit_Bool()) {
		this->Quit = true;
	}
	else {
		Game_Menu.Render_Menu(this->Renderer);
	}
}

void Interface::Check_Events() {
	if (!this->Game_Menu.Get_Play_Bool()) {
		this->Game_Menu.Check_Events(this->event, &this->Menu_Theme);
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

void Interface::Save_Records(const int& New_Score, const std::string& New_Time) {
	std::string folderName = "Records";
	std::filesystem::path folderPath(folderName);

	if (!std::filesystem::exists(folderPath)) {
		std::filesystem::create_directory(folderPath);
	}
	std::string PathRecords{ folderName + "/Records.txt" };
	std::ifstream file_i(PathRecords);
	std::string line{}, Record{};
	int Record_Score{};
	if (file_i.is_open()) {
		while (getline(file_i, line)) {
			Record = line;
		}
		if(Record.length() > 3)
			Record_Score = Check_Record_Score(Record[0], Record[1], Record[2]);
		file_i.close();
	}
	std::ofstream file_o(PathRecords, std::ofstream::app);
	if (file_o.is_open()) {
		if (Record_Score < New_Score) {
			char tmpbuf_time[128], tmpbuf_date[128];
			_tzset();
			_strtime_s(tmpbuf_time, 128);
			_strdate_s(tmpbuf_date, 128);
			int Space_Num = 25;
			if (New_Score > 9) {
				Space_Num = 24;
			}
			else if (New_Score > 99) {
				Space_Num = 23;
			}
			file_o << std::to_string(New_Score) << std::setw(Space_Num) << New_Time << "     " << tmpbuf_date << "-" << tmpbuf_time << "\n";
		}
		file_o.close();
	}
}

void Interface::Play() {
	this->Game_Snake.Start_Timer(SDL_GetTicks64());
	for (auto& Obj : this->Game_Objects) {
		Obj->Interaction(this->Game_Snake);
	}
	if (this->Game_Snake.Render(this->Renderer)) {
		if (this->Game_Snake.Display_GmOv_Statis(this->Renderer, this->TextFont, &this->Game_Textures[SURFACES_TEXTURES_ENUM::SCORE_TEXT_WHITE], &this->Game_Textures[SURFACES_TEXTURES_ENUM::SCORE_TEXT_BLACK],
			&this->Game_Textures[SURFACES_TEXTURES_ENUM::TIME_TEXT_WHITE], &this->Game_Textures[SURFACES_TEXTURES_ENUM::TIME_TEXT_BLACK], &this->Game_Textures[SURFACES_TEXTURES_ENUM::GAME_OVER_TEXT_WHITE], &this->Game_Textures[SURFACES_TEXTURES_ENUM::GAME_OVER_TEXT_BLACK], this->Game_Menu.Return_Cancel_Button())) {
			Save_Records(this->Game_Snake.Get_Score(), this->Game_Snake.Get_Time());
			this->Game_Snake.Reset();
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