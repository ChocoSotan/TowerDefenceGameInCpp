#pragma once

#include "DxLib.h"
#include "Texture.h"
#include "Mouse.h"
#include "IMouseOver.h"

#include <string>
#include <vector>

class Button {
public:
	Button(int x, int y) {
		this->x = x;
		this->y = y;
		wasclicked = false;
		isclicked = false;
		count = 0;
	}
	Button(const Vector2D &pos) {
		this->x = pos.getX();
		this->y = pos.getY();
		wasclicked = false;
		isclicked = false;
		count = 0;
	}
	virtual ~Button() {}

	void draw(const Texture &texture) const;
	virtual void update(const Mouse &mouse);
	bool isClicked() const;
	bool init(const Texture &texture, const std::vector<std::string> &vfilename);
	bool init(const Texture &texture, const std::string &filename);

	void proceedCount() { count = (count + 1) % (int)vfilename.size(); }
	void setCount(int count) { this->count = count; }

	Vector2D getPosition() const { return Vector2D(x, y); }

protected:
	int x, y;
	int sx, sy;
	bool isclicked;
	bool wasclicked;
	std::vector<std::string> vfilename;
	int count;
};

class MouseOverButton :public Button {
public:
	MouseOverButton(int x,int y):Button(x,y) {

	}
	MouseOverButton(const Vector2D &pos) :Button(pos) {

	}
	void update(const Mouse &mouse)override;
	bool isMouseOver() { return mouseover.isMouseOver(); }

private:
	MouseOver mouseover;
};