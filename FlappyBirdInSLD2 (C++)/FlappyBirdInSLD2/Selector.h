#pragma once

#include "System.h"

class Selector {
public:
	Selector();
	~Selector();
	void Set_Selector(int x, int y, int w, int h);
	//Checking if the User clicked the selector in OPTION page
	void Action(SDL_Event* MouseEvent);
	bool GetisClicked();
private:
	SDL_Rect Position;
	bool isClicked;
};