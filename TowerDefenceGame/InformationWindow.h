#pragma once

#include "Vector2D.h"

#include <vector>
#include <string>

typedef enum {
	eTextAlignmentCenter,
	eTextAlignmentLeft,
}eTextAlignment;

class InformationWindow final {
public:
	InformationWindow() {}
	~InformationWindow() {}
	
	void update(const std::string &text);
	void draw(const Vector2D &pos, int textcolor, int framecolor, int backcolor, eTextAlignment alignment) const;

private:
	int getStringWidth(const std::string &text) const;
	int getStringHeight(const std::string &text) const;
	void splitString(const std::string &text, std::vector<std::string> &container, const char delim = ',')const;
	

private:
	std::string text;
};