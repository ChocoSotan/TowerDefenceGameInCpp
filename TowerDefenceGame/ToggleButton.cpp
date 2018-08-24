#include"ToggleButton.h"
void ToggleButton::update() {
	for (int i = 0; i < button.size(); i++) {
		if (!button[i]->isClicked())continue;
		if (i == Channel) {
			button[i]->setCount(0);
			Channel = -1;
		}
		if (Channel != -1) {
			button[Channel]->setCount(0);
		}
		Channel = i;
		return;
	}
}

void ToggleButton::addButton(Button* button) {
	this->button.push_back(button);
}
void ToggleButton::addButton(std::vector<Button*>button) {
	this->button.clear();
	for (auto i = 0; i < button.size(); i++) {
		this->button.push_back(button[i]);
	}
}
void ToggleButton::channelClear() {
	for (auto i = 0; i < button.size(); i++) {
		button[i]->setCount(0);
	}
	Channel = -1;
}