export module Interface;

import Core;
import Button;
import Menu;
import Snake;
import Game_Object;
import Apple;
import Coin;
import Obstacle;
import <vector>;
import <memory>;
import Sound;
import <filesystem>;
import <iomanip>;
import <fstream>;
import <time.h>;
import External_Functions;

export class Interface : protected Core {
public:
	Interface();
	~Interface();
	void Main_Loop();
private:
	bool Quit;
	Menu Game_Menu;
	Snake Game_Snake;
	std::vector<std::unique_ptr<Game_Object>> Game_Objects;
	Sound Menu_Theme;
private:
	void Menu_Operations();
	void Check_Events();
	void Render();
	void Save_Records(const int& New_Score, const std::string& New_Time);
	void Play();
};