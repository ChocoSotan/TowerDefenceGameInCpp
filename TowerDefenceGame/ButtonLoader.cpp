#include "ButtonLoader.h"

#include "Button.h"
#include "ToggleButton.h"
#include "Texture.h"

#include <string>
#include <vector>
#include <fstream>

#ifdef _DEBUG
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG



bool ButtonLoader::load(const std::string &filename, std::vector<Button*> *vbutton, std::vector<ToggleButton*> &vtbutton, const Texture &texture) const {
	using namespace std;

	ifstream ifs(filename);
	string line;
	vector<string> buffer;
	Button *button;
	vector<string> buttonfilename;
	vector<int> togglegroup;

	if (ifs.fail())return false;

	while (getline(ifs, line)) {
		if (line[0] == '#')continue;
		splitString(line, buffer);

		button = new Button(stoi(buffer[1]), stoi(buffer[2]));
		for (int i = 3; i < (signed)buffer.size(); i++) {
			buttonfilename.push_back(buffer[i]);
		}

		// if the button has toggle group id
		if (buffer[0].compare("-") != 0) {
			int id = stoi(buffer[0]);
			togglegroup.push_back(id);
			if ((int)vtbutton.size() <= id)vtbutton.push_back(new ToggleButton());
			vtbutton[id]->addButton(button);
		}


		button->init(texture, buttonfilename);
		vbutton->push_back(button);

		buttonfilename.clear();
		buffer.clear();
	}

	return true;
}
