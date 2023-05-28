export module Sound;

import Core;
import "SDL_Mixer.h";
import <string>;

export class Sound {
private:
	static bool isActive;
	Mix_Music* Music;
	Mix_Chunk* Chunk;
public:
	Sound();
	~Sound();
	void Play_Music();
	void Stop_Music();
	void Play_Chunk(bool infinite = false);
	static void Turn_On();
	static void Turn_Off();
	bool Load_Music(std::string& Path);
	bool Load_Chunk(std::string& Path);
};