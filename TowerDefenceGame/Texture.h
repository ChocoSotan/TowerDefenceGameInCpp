#pragma once

#include <map>
#include <string>
#include <vector>

#include "DxLib.h"

class Texture final {
public:
	Texture() {}
	~Texture() {}

	bool pool(const std::string filename) {
		// if pair has been added dictionary
		if (dictionary.find(filename) != dictionary.end())return false;

		int handle = LoadGraph(filename.c_str());
		if (handle == -1)return false;
		
		dictionary.insert(std::make_pair(filename, handle));
		return true;
	}
	bool pool(std::vector<std::string> vfilename) {
		for (auto i = vfilename.begin(); i != vfilename.end(); i++) {
			// if pair has been added dictionary
			if (dictionary.find(*i) != dictionary.end())continue;

			int handle = LoadGraph((*i).c_str());
			if (handle == -1)return false;

			dictionary.insert(std::make_pair(*i, handle));
		}
		return true;
	}


	bool deleteHandle(const std::string filename) {
		if (DeleteGraph(dictionary[filename]) == -1)return false;
		return true;
	}
	bool deleteHandle(const std::vector<std::string> vfilename) {
		for (int i = 0; (signed)vfilename.size(); i++) {
			if (DeleteGraph(dictionary[vfilename[i]]) == -1)return false;
		}
		return true;
	}

	int getHandle(const std::string filename) {
		try {
			dictionary.at(filename);
		} catch (std::out_of_range &oor) {
			OutputDebugString(oor.what());
			return -1;
		} 
		return dictionary[filename];
	}
	
private:
	std::map<std::string,int> dictionary;
};