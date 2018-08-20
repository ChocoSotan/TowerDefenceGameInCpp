#pragma once
#include "Vector2D.h"


class Mouse final {
public:
	Mouse();
	~Mouse();

	void update();
	Vector2D getPosition() const;
	int getBind() const;
	int getLog() const;
	bool isChangedState()const;

private:
	int bind;
	Vector2D position;
	int log;
	bool ischanged;
};

