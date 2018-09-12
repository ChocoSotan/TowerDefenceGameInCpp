#include "Loader.h"

#include "Terrain.h"
#include "Turret.h"
#include "TurretFactory.h"
#include "WaveSystem.h"
#include "TargetPriority.h"
#include "Button.h"
#include "ToggleButton.h"

#include <string>
#include <vector>
#include <fstream>


// split string by delimiter and store to container
void Loader::splitString(const std::string &line, std::vector<std::string> &container, const char delim) {
	std::istringstream iss(line);
	std::string str;

	while (std::getline(iss, str, delim)) {
		container.push_back(str);
	}
}

bool FieldLoader::load(std::string filename, std::vector<std::vector<TerrainBase*>> &vec, const Vector2D &pos, const int size) {
	using namespace std;
	ifstream ifs(filename);
	string line;
	vector<string> buffer;
	int column = 0;
	int row = 0;
	vector<TerrainBase*> tmp;

	if (ifs.fail())return false;

	// can place turret
	while (getline(ifs, line)) {
		if (line[0] == '#')continue;
		splitString(line, buffer);

		for (column = 0; column < (signed)buffer.size(); column++) {
			if (stoi(buffer[column]) == 0) {
				tmp.push_back(new BasicTerrain(false, Vector2D(pos.getX() + row * size,pos.getY() + column * size)));
			}
			else {
				tmp.push_back(new BasicTerrain(true, Vector2D(pos.getX() + row * size, pos.getY() + column * size)));
			}
		}

		vec.push_back(tmp);
		tmp.clear();
		row++;
		buffer.clear();
	}
	ifs.clear();
	

	return true;
}

bool FieldLoader::initField(std::string filename_texture, std::string filename_id, std::vector<std::vector<TerrainBase*>> &vec, Texture *texture) {
	using namespace std;
	ifstream ifs(filename_id);
	string line;
	vector<string> buffer;
	map<int, string> dictionary;
	int row = 0;

	while (getline(ifs, line)) {
		if (line[0] == '#')continue;
		splitString(line, buffer);
		
		dictionary.insert(std::make_pair(stoi(buffer[0]), buffer[1]));

		row++;
		buffer.clear();
	}

	ifs.close();
	ifs.open(filename_texture);
	if (ifs.fail())return false;
	row = 0;

	while (getline(ifs, line)) {
		if (line[0] == '#')continue;
		splitString(line, buffer);

		for (int i = 0; i < buffer.size(); i++) {
			if (dictionary.find(stoi(buffer[i])) != dictionary.end()) {
				vec[i][row]->init(texture, dictionary[stoi(buffer[i])]);
			}
			else return false;
		}

		row++;
		buffer.clear();
	}


	return true;
}



bool WaveLoader::load(std::string filename, std::vector<Wave*> &vec, Vector2D &pos) {
	using namespace std;

	ifstream ifs(filename);
	string line;
	vector<string> buffer;
	vector<EnemyBase*> venemy;

	const vector<string> EnemyType{
		"Normal",
		"Fast",
		"Armored",
	};

	if (ifs.fail())return false;

	while (getline(ifs, line)) {
		if (line[0] == '#')continue;
		splitString(line, buffer);

		for (int i = 0; i < (signed)EnemyType.size(); i++) {
			if (EnemyType[i].compare(buffer[0]) != 0)continue;
			switch (i) {
			case 0:
				for (int j = 0; j < stoi(buffer[1]); j++) {
					venemy.push_back(new NormalEnemy(stoi(buffer[2]), stod(buffer[3]), stol(buffer[4]), stoll(buffer[5]),pos));
				}
				break;

			case 1:
				// Fast(experimental)
				for (int j = 0; j < stoi(buffer[1]); j++) {
					venemy.push_back(new NormalEnemy(stoi(buffer[2]), stod(buffer[3]), stol(buffer[4]), stoll(buffer[5]),pos));
				}
				break;
			case 2:
				// Armored
				for (int j = 0; j < stoi(buffer[1]); j++) {
					venemy.push_back(new NormalEnemy(stoi(buffer[2]), stod(buffer[3]), stol(buffer[4]), stoll(buffer[5]),pos));
				}
				break;
			}
			vec.push_back(new Wave(venemy));
			break;
		}
		venemy.clear();
		buffer.clear();
	}
	return true;
}

bool PathLoader::load(std::string filename, std::vector<Vector2D> &vpath) {
	using namespace std;
	ifstream ifs(filename);
	string line;
	vector<string> buffer;

	if (ifs.fail())return false;

	while (getline(ifs, line)) {
		if (line[0] == '#')continue;
		splitString(line, buffer);

		vpath.push_back(Vector2D(stoi(buffer[0]),stoi(buffer[1])));

		buffer.clear();
	}



	return true;
}

bool TextureLoader::load(std::string filename, Texture *texture) {
	using namespace std;

	ifstream ifs(filename);
	string line;
	vector<string> buffer;
	vector<string> vfilename;

	if (ifs.fail())return false;

	while (getline(ifs, line)) {
		if (line[0] == '#')continue;
		//splitString(line, buffer);

		if(!texture->pool(line))return false;

		buffer.clear();
	}



	return true;
}

bool ButtonLoader::load(std::string filename, std::vector<Button*> &vbutton, std::vector<ToggleButton*> &vtbutton,Texture *texture) {
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
		for (int i = 3; i < (unsigned)buffer.size(); i++) {
			buttonfilename.push_back(buffer[i]);
		}

		// if the button has toggle group id
		if (buffer[0].compare("-") != 0) {
			int id = stoi(buffer[0]);
			togglegroup.push_back(id);
			if(vtbutton.size() <= id)vtbutton.push_back(new ToggleButton());
			vtbutton[id]->addButton(button);
		}
		

		button->init(texture, buttonfilename);
		vbutton.push_back(button);

		buttonfilename.clear();
		buffer.clear();
	}

	return true;
}
