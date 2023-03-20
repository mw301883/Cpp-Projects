#pragma once
#include "System.h"

enum PIPE_ENUM {
	PIPE_UP_HIGH,
	PIPE_UP_MEDIUM,
	PIPE_UP_LOW,
	PIPE_DOWN_HIGH,
	PIPE_DOWN_MEDIUM,
	PIPE_DOWN_LOW,
	PIPE_GAP_LOW,
	PIPE_GAP_HIGH,
	PIPE_TOTAL
};

class Pipe {
public:
	Pipe();
	~Pipe();
	void Render(Texture& Pipe_Texture, SDL_Renderer* &Renderer);
	//Change X position
	void Move(int& Window_W, bool& CurrentPipe);
	//Set the Double Collision area when one Pipe Object render Two pipes (Up and Down)
	void Set_is_Double_Collision_area(bool is_Double_Collision_Area);
	void SetCollision();
	void ResetPipe();
	void Set_Clip(SDL_Rect Clip);
	//Change Collider position (upper Pipe)
	void Set_ColliderHight_Up(int ColliderHight);
	//Change Collider position (lower Pipe)
	void Set_ColliderHight_Down(int ColliderHight);
	int GetX();
	int GetY();
	int Get_ColliderHight_Up();
	int Get_ColliderHight_Down();
	bool Get_is_Double_Collision_Area();
	//Setting the speed of Pipes objects motions
	void Set_Const_Counter(const int& New_Counter);
private:
	SDL_Rect Pipe_Current;
	bool Double_Collision_Area, isCollision;
	int X, Y, Distance_Out_Screen, Counter, Const_Counter, ColliderHight_Up, ColliderHight_Down; /*measured like ColliderHight_Up*/
};

//Initialisation of Game Pipe objects
void Game_Pipe_Init(SDL_Rect Clips[20], Pipe Pipe_Unset[PIPE_TOTAL]);

//Choosing Random Pipe Object to render
int Random_Index();