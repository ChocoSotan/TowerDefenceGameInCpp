#pragma once

#include <string>
#include <vector>

class Debugger final {
public:
	void print(const std::string &text);
	void addText(const std::string &text);

	void show(const int showflag);

	const static int ShowFlagOutput = 0x0000;
	const static int ShowFlagText = 0x0001;

private:
	std::vector<std::string> m_texts;
};