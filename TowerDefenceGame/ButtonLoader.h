#pragma once

#include "Loader.h"

class Button;
class ToggleButton;
class Texture;

#include <string>
#include <vector>

class ButtonLoader : public Loader {
public:
	ButtonLoader() {}
	~ButtonLoader() {}

	bool load(std::string filename, std::vector<Button*> &vbutton, std::vector<ToggleButton*> &vtbutton, Texture *texture);
};
