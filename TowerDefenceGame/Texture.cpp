#include "Texture.h"

#include <map>
#include <vector>
#include <string>

bool Texture::pool(const std::string &filename) {
	// if pair has been added dictionary
	if (dictionary.find(filename) != dictionary.end())return false;

	int handle = LoadGraph(filename.c_str());
	if (handle == -1)return false;

	dictionary.insert(std::make_pair(filename, handle));
	return true;
}

bool Texture::pool(const std::vector<std::string> &vfilename) {
	for (auto i = vfilename.begin(); i != vfilename.end(); i++) {
		// if pair has been added dictionary
		if (dictionary.find(*i) != dictionary.end())continue;

		int handle = LoadGraph((*i).c_str());
		if (handle == -1)return false;

		dictionary.insert(std::make_pair(*i, handle));
	}
	return true;
}

bool Texture::deleteHandle(const std::string &filename) {
	if (DeleteGraph(dictionary[filename]) == -1)return false;
	return true;
}

bool Texture::deleteHandle(const std::vector<std::string> &vfilename) {
	for (int i = 0; (signed)vfilename.size(); i++) {
		if (DeleteGraph(dictionary[vfilename[i]]) == -1)return false;
	}
	return true;
}

int Texture::getHandle(const std::string &filename) const {
	try {
		dictionary.at(filename);
	} catch (std::out_of_range &oor) {
		OutputDebugString(oor.what());
		return -1;
	}
	return dictionary.at(filename);
}

std::vector<int> Texture::getHandle(const std::vector<std::string> &vfilename) const {
	try {
		for (auto i = vfilename.begin(); i != vfilename.end(); i++) {
			dictionary.at(*i);
		}
	} catch (std::out_of_range &oor) {
		OutputDebugString(oor.what());
		return std::vector<int>();
	}

	std::vector<int> ret;
	for (auto i = vfilename.begin(); i != vfilename.end(); i++) {
		ret.push_back(dictionary.at(*i));
	}

	return ret;
}

bool Texture::deleteHandleAll() {
	for (auto i = dictionary.begin(); i != dictionary.end(); i++) {
		if(DeleteGraph(i->second) == -1)return false;
	}
	return true;
}






