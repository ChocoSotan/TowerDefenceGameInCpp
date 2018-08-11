#pragma once

#include "DxLib.h"
#include "Texture.h"
#include "Mouse.h"

#include <string>

class Button {
public:
	Button(int x, int y) {
		this->x = x;
		this->y = y;
		wasclicked = false;
		isclicked = false;
		count = 0;
	}
	virtual ~Button() {}

	void draw() const;
	virtual void update(const Mouse &mouse);
	bool isClicked() const;
	bool init(Texture *texture, std::vector<std::string> vfilename);

protected:
	

	int x, y;
	int sx, sy;
	bool isclicked;
	bool wasclicked;
	Texture *texture;
	std::vector<std::string> vfilename;
	int count;
};

void Button::draw() const {
	DrawGraph(x, y, texture->getHandle(vfilename[count]), TRUE);
}

bool Button::isClicked() const {
	return isclicked;
}

void Button::update(const Mouse &mouse) {
	this->isclicked = false;

	if (!mouse.isChangedState())return;

	if (mouse.getLog() == MOUSE_INPUT_LOG_DOWN && (mouse.getBind() & MOUSE_INPUT_LEFT) != 0) {
		if (mouse.getPosition().getX() < this->x || this->x + this->sx < mouse.getPosition().getX() || mouse.getPosition().getY() < this->y || this->y + this->sy < mouse.getPosition().getY()) {
			wasclicked = false;
		}
		else {
			wasclicked = true;
		}
		return;
	}
	if (mouse.getLog() == MOUSE_INPUT_LOG_UP && (mouse.getBind() & MOUSE_INPUT_LEFT) != 0) {
		if (mouse.getPosition().getX() < this->x || this->x + this->sx < mouse.getPosition().getX() || mouse.getPosition().getY() < this->y || this->y + this->sy < mouse.getPosition().getY()) {
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

bool Button::init(Texture *texture, std::vector<std::string> vfilename) {
	for (auto i = vfilename.begin(); i != vfilename.end(); i++) {
		if (texture->getHandle(*i) == -1)return false;
	}
	this->texture = texture;
	this->vfilename = vfilename;
	if(GetGraphSize(texture->getHandle(vfilename[0]), &sx, &sy) == -1)return false;
	return true;
}