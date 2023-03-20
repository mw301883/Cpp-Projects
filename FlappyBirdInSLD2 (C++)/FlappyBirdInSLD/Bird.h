#pragma once

#include "System.h"

class Bird {
public:
	Bird(SDL_Rect Clips[20]);
	~Bird();
	void Render(Texture& Bird_Texture, SDL_Renderer*& Renderer);
	//Changing Y position in Game
	void Move(int& Window_H);
	//Checking User's movements
	void CheckEvent(SDL_Event* Mouse_Event);
	//Check collisions with Pipes objects
	bool Collision_Detection(int PipeX, int PipeUpHeight, int PipeDownHeight, bool isDoublePipe);
	bool is_End(bool& EndGame);
	void Reset_Bird();
private:
	bool isDead;
	SDL_Rect Alive_Up, Alive_Down, Dead_Up, Dead_Down;
	bool Motion, Collision;
	int X, Y, VelY, Height, Counter;
};