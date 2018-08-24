#pragma once
#include"Button.h"
#include<vector>
//#include<vector>
class ToggleButton {
public:
	~ToggleButton() {}
	ToggleButton() {

	}
	void update();
	void addButton(int x, int y);
private:
	std::vector<Button*> button;
};