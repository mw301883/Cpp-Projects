import Sound;
import "SDL_Mixer.h";

bool Sound::isActive = true;

Sound::Sound() : Music(nullptr), Chunk(nullptr) {}

Sound::~Sound() {
	if (this->Music != nullptr) {
		Mix_FreeMusic(this->Music);
		this->Music = nullptr;
	}

	if (this->Chunk != nullptr) {
		this->Chunk = nullptr;
	}
}

void Sound::Play_Music() {
	if (this->Music != nullptr) {
		Mix_PlayMusic(this->Music, -1);
	}
}

void Sound::Stop_Music() {
	if (this->Music != nullptr) {
		Mix_HaltMusic();
	}
}

void Sound::Play_Chunk(bool infinite) {
	if (isActive && this->Chunk != nullptr && !infinite) {
		Mix_PlayChannel(-1, this->Chunk, 0);
	}
	else if (infinite) {
		Mix_PlayChannel(-1, this->Chunk, -1);
	}
}

void Sound::Turn_On() {
	isActive = true;
}

void Sound::Turn_Off() {
	isActive = false;
}

bool Sound::Load_Music(std::string& Path) {
	this->Music = Mix_LoadMUS(Path.c_str());
	if (this->Music == nullptr) {
		return false;
	}
	else {
		return true;
	}
}

bool Sound::Load_Chunk(std::string& Path) {
	this->Chunk = Mix_LoadWAV(Path.c_str());
	if (this->Chunk == nullptr) {
		return false;
	}
	else {
		return true;
	}
}