#pragma once

#include "Vector2D.h"

#include <vector>
#include <string>

#define INFOTYPE_CLEARBACK (-1)
#define INFOTYPE_NONEBORDER (-2)

typedef enum {
	eTextAlignmentCenter,
	eTextAlignmentLeft,
}eTextAlignment;

class InformationWindow final {
public:
	InformationWindow() {}
	~InformationWindow() {}
	
	void update(const std::string &text);
	void draw(const Vector2D &pos, int textcolor, int framecolor, int backcolor, eTextAlignment alignment = eTextAlignmentLeft) const;

private:
	int getStringWidth(const std::string &text) const;
	int getStringHeight(const std::string &text) const;
	void splitString(const std::string &text, std::vector<std::string> *container, const char delim = ',')const;
	

private:
	std::string text;
};