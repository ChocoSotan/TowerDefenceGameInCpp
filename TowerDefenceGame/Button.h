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

