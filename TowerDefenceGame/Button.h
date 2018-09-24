#pragma once

#include "DxLib.h"
#include "Texture.h"
#include "Mouse.h"

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

