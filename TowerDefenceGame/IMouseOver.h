#pragma once

#include "Mouse.h"
#include "Vector2D.h"

class IMouseOver {
public:
	IMouseOver() {}
	virtual ~IMouseOver() {}

protected:
	inline virtual void update(const Mouse &mouse, const Vector2D &pos, const int size_x,  const int size_y);
	bool isMouseOver() const { return this->mouseover; }

protected:
	bool mouseover;
};

inline void IMouseOver::update(const Mouse &mouse, const Vector2D &pos, const int size_x, const int size_y) {
	Vector2D nowpos = mouse.getPosition();

	if (nowpos.getX() < pos.getX() || nowpos.getX() > pos.getX() + size_x || nowpos.getY() < pos.getY() || nowpos.getY() > pos.getY() + size_y) {
		this->mouseover = false;
	}
	else {
		this->mouseover = true;
	}
}