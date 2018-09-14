#include "InformationWindow.h"

#include "DxLib.h"
#include "Vector2D.h"
#include "Mouse.h"

#include <vector>
#include <string>
#include <sstream>

void InformationWindow::update(const std::string &text) {
	this->text = text;
}

void InformationWindow::draw(const Vector2D &pos, int textcolor, int framecolor, int backcolor, eTextAlignment alignment) const {
	int width = getStringWidth(text);
	int height = getStringHeight(text);
	int padding = 8;

	// frame & back
	if (framecolor != INFOTYPE_NONEBORDER) {
		DrawBox((int)pos.getX() - padding, (int)pos.getY() - padding, (int)pos.getX() + width + (padding * 2), (int)pos.getY() + height + (padding * 2), framecolor, FALSE);
	}
	if(backcolor != INFOTYPE_CLEARBACK){
		DrawBox((int)pos.getX() - padding + 1, (int)pos.getY() - padding + 1, (int)pos.getX() + width + (padding * 2) - 1, (int)pos.getY() + height + (padding * 2) - 1, backcolor, TRUE);
	}
		
		// text
	switch (alignment) {
	case eTextAlignmentCenter:
		
		break;
	case eTextAlignmentLeft:
		DrawString((int)pos.getX() + padding, (int)pos.getY() + padding, this->text.c_str(), textcolor);
		break;
	}
}

int InformationWindow::getStringWidth(const std::string &text) const {
	using namespace std;
	
	int ret = 0;
	vector<string> lines;

	splitString(text, &lines, '\n');
	for (int i = 0; i < lines.size(); i++) {
		int width = 0;
		width = GetDrawStringWidth(lines[i].c_str(), lines[i].length());
		width > ret ? ret = width : ret = ret;
	}

	return ret;
}

int InformationWindow::getStringHeight(const std::string &text) const {
	using namespace std;

	int ret = 0;
	int fontsize = 20;
	vector<string> lines;

	splitString(text, &lines, '\n');
	
	ret = lines.size() * fontsize;

	return ret;
}

void InformationWindow::splitString(const std::string &text, std::vector<std::string> *container, const char delim) const {
	using namespace std;
	istringstream iss(text);
	string str;

	while (getline(iss, str, delim)) {
		container->push_back(str);
	}
}




