export module Game_Object;

import Texture;
import Core;
import "SDL.h";
import Snake;
import <random>;

export class Game_Object {
public:
	virtual void Render(SDL_Renderer* Renderer, const int& x = 0, const int& y = 0) = 0;
	virtual void Interaction(Snake& Snake_Obj) = 0;
	int Get_Random_Integer(const int& rbegin, const int& rend) {
		std::random_device rd;
		std::default_random_engine eng(rd());
		std::uniform_int_distribution<int> uniform_dist(rbegin, rend);
		return uniform_dist(eng);
	}
	virtual ~Game_Object() {}
};