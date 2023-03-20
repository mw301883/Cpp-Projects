#pragma once

#include "System.h"
#include "SDL_mixer.h"

class Sound {
public:
	Sound();
	~Sound();
	void Play_Music();
	void Stop_Music();
	void Play_Chunk(bool infinite = false);
	void Turn_On();
	void Turn_Off();
	bool Load_Music(std::string& Path);
	bool Load_Chunk(std::string& Path);
private:
	bool isActive;
	Mix_Music* Music;
	Mix_Chunk* Chunk;
};
