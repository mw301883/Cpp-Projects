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

export class Interface : protected Core {
private:
	bool Quit;
	Menu Game_Menu;
	Snake Game_Snake;
	void Menu_Operations();
	void Check_Events();
	void Render();
	std::vector<std::unique_ptr<Game_Object>> Game_Objects;
public:
	Interface();
	~Interface();
	void Main_Loop();
};