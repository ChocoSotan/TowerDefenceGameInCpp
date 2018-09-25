#include "Button.h"

#include <vector>
#include <string>

void Button::draw(const Texture &texture) const {
	DrawGraph(x, y, texture.getHandle(vfilename[count]), TRUE);
}

bool Button::isClicked() const {
	return isclicked;
}

void Button::update(const Mouse &mouse) {
	this->isclicked = false;

	if (!mouse.isChangedState())return;

	if (mouse.getLog() == MOUSE_INPUT_LOG_DOWN && (mouse.getBind() & MOUSE_INPUT_LEFT) != 0) {
		if (mouse.getPosition().getX() < this->x || this->x + this->sx - 1 < mouse.getPosition().getX() || mouse.getPosition().getY() < this->y || this->y + this->sy - 1 < mouse.getPosition().getY()) {
			wasclicked = false;
		}
		else {
			wasclicked = true;
		}
		return;
	}
	if (mouse.getLog() == MOUSE_INPUT_LOG_UP && (mouse.getBind() & MOUSE_INPUT_LEFT) != 0) {
		if (mouse.getPosition().getX() < this->x || this->x + this->sx - 1 < mouse.getPosition().getX() || mouse.getPosition().getY() < this->y || this->y + this->sy - 1 < mouse.getPosition().getY()) {
			isclicked = false;
			return;
		}
		else {
			if (!wasclicked)return;
			isclicked = true;
			count = (count + 1) % (int)vfilename.size();
		}
	}
}

bool Button::init(const Texture &texture, const std::vector<std::string> &vfilename) {
	for (auto i = vfilename.begin(); i != vfilename.end(); i++) {
		if (texture.getHandle(*i) == -1)return false;
	}
	this->vfilename = vfilename;
	if (GetGraphSize(texture.getHandle(vfilename[0]), &sx, &sy) == -1)return false;
	return true;
}

bool Button::init(const Texture &texture, const std::string &filename) {
	if (texture.getHandle(filename) == -1)return false;
	this->vfilename.push_back(filename);
	if (GetGraphSize(texture.getHandle(vfilename[0]), &sx, &sy) == -1)return false;
	return true;
}
void MouseOverButton::update(const Mouse &mouse) {
	mouseover.update(mouse,Vector2D(this->x,this->y),this->sx,this->sy);
}