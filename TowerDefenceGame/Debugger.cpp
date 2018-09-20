
#include "Debugger.h"

#include <vector>
#include <string>
#include <sstream>

void Debugger::addText(const std::string &text) {
	m_texts.push_back(text + '\n');
}

void Debugger::show(const int showflag) {
#ifdef _DEBUG
	if (showflag == Debugger::ShowFlagOutput) {
		std::stringstream ss;
		for (auto i = m_texts.begin(); i != m_texts.end(); ++i) {
			_RPT0(_CRT_WARN, (*i));
		}
}
#endif // _DEBUG

	if (showflag == Debugger::ShowFlagText) {

	}
}

void Debugger::print(const std::string &text) {
#ifdef _DEBUG
	std::stringstream ss;
	ss << text + '\n';
	_RPT0(_CRT_WARN, ss.str().c_str());
#endif // _DEBUG
}
