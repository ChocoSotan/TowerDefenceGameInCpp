#pragma once
#include<vector>
#include"Button.h"
//#include<vector>
class ToggleButton {
public:
	~ToggleButton() {}
	ToggleButton() {

	}
	void update();
	void addButton(Button*);
	void addButton(std::vector<Button*>);
	void channelClear();
	int getChannel() { return Channel; }
private:
	std::vector<Button*> button;
	int Channel=-1;
};