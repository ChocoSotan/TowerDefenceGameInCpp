#include "Mouse.h"

#include "Vector2D.h"
#include "DxLib.h"


Mouse::Mouse() {
	bind = -1;
	position.setX(0), position.setY(0);
	log = -1;
	ischanged = false;
}


Mouse::~Mouse() {
}




void Mouse::update() {
	int x, y;
	GetMouseInputLog2(&this->bind, &x, &y, &this->log) == -1 ? ischanged = false : ischanged = true;
	this->position.setX(x), this->position.setY(y);
}

Vector2D Mouse::getPosition() const {
	return this->position;
}


int Mouse::getBind() const {
	return this->bind;
}


int Mouse::getLog() const {
	return this->log;
}

bool Mouse::isChangedState() const {
	return this->ischanged;
}