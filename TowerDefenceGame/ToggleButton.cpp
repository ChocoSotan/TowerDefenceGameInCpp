#include"ToggleButton.h"
void ToggleButton::update(const Mouse &mouse) {
	for (int i = 0; i < button.size(); i++) {
		if (button[i]->isClicked()) {
			Channel = i;
			break;
		}
	}
}
void ToggleButton::addButton(int x, int y, Texture* texture, std::vector<std::string> vfilename) {
	button.push_back(new Button(x, y));
	button[button.size()]->init(texture, vfilename);
}
void ToggleButton::addButton(std::vector<Button*>button) {
	this->button.clear();
	for (auto i = 0; i < button.size(); i++) {
		this->button.push_back(button[i]);
	}
}