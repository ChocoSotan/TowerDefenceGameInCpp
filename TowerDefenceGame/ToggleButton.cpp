#include"ToggleButton.h"
void ToggleButton::update() {
	for (int i = 0; i < button.size(); i++) {
		if (button[i]->isClicked()) {
			if (Channel != -1) {
				button[Channel]->setCount(0);
			}
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