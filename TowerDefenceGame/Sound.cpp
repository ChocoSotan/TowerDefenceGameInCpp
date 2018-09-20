#include "Sound.h"

#include "DxLib.h"

#include <string>

bool Sound::play(const std::string &filename) const {
	try {
		sounds.at(filename);
	} catch (const std::out_of_range &e) {
		OutputDebugString(e.what());
		return false;
	}
	PlaySoundMem(sounds.at(filename), DX_PLAYTYPE_BACK);
	return true;
}

bool Sound::pool(const std::string &filename) {
	if (sounds.find(filename) != sounds.end())return false;

	int handle = LoadSoundMem(filename.c_str());
	//int handle = LoadSoundMem("sound/BasicTurret.wav");
	if (handle == -1)return false;

	this->sounds.insert(std::make_pair(filename, handle));
	return true;
}
