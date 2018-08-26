#include "Loader.h"

#include "Terrain.h"
#include "Turret.h"
#include "TurretFactory.h"
#include "WaveSystem.h"
#include "TargetPriority.h"
#include "Button.h"

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

bool FieldLoader::load(std::string filename, std::vector<std::vector<TerrainBase*>> &vec, Vector2D &pos, int size) {
	using namespace std;
	ifstream ifs(filename);
	string line;
	vector<string> buffer;
	int column = 0;
	int row = 0;

	if (ifs.fail())return false;

	// can place turret
	while (getline(ifs, line)) {
		if (line[0] == '#')continue;
		splitString(line, buffer);

		for (column = 0; column < (signed)buffer.size(); column++) {
			vec[column][row] = stoi(buffer[row]) == 0 ?
				new BasicTerrain(false, Vector2D(pos.getX() + column * size, pos.getY() + row * size))
				: new BasicTerrain(true, Vector2D(pos.getX() + column * size, pos.getY() + row * size));
		}
		row++;
		buffer.clear();
	}
	ifs.clear();
	

	return true;
}

bool FieldLoader::initField(std::string filename, std::vector<std::vector<TerrainBase*>> &vec, Texture *texture) {
	using namespace std;
	ifstream ifs(filename);
	string line;
	vector<string> buffer;
	int row = 0;

	while (getline(ifs, line)) {
		if (line[0] == '#')continue;
		splitString(line, buffer);

		for (int i = 0; i < buffer.size(); i++) {
			if (!texture->pool(buffer[i]))return false;
			vec[i][row]->init(texture, buffer[i]);
		}
		
		row++;
		buffer.clear();
	}


	return true;
}

bool TurretLoader::load(std::string filename, std::vector<TurretBase*> &vec) {
	using namespace std;
	ifstream ifs(filename);
	string line;
	vector<string> buffer;
	TurretBase *turret;

	const vector<string> TurretType {
		"Basic",
		"Splash",
		"AoE",
	};

	if (ifs.fail())return false;

	while (getline(ifs, line)) {
		if (line[0] == '#')continue;
		splitString(line, buffer);
		
		for (int i = 0; i < (signed)TurretType.size(); i++) {
			if (TurretType[i].compare(buffer[0]) != 0)continue;
			switch (i) {
			case 0:
				turret = new BasicTurret(buffer[1],stod(buffer[2]),stod(buffer[3]),stod(buffer[4]),stoi(buffer[5]),stoi(buffer[6]),Vector2D(0,0));
				break;
			case 1:
				turret = new MortarTurret(buffer[1], stod(buffer[2]), stod(buffer[3]), stod(buffer[4]), stoi(buffer[5]), stoi(buffer[6]), Vector2D(0, 0), stod(buffer[7]), stod(buffer[8]), stod(buffer[9]));
				break;
			case 2:
				turret = new BlastTurret(buffer[1], stod(buffer[2]), stod(buffer[3]), stod(buffer[4]), stoi(buffer[5]), stoi(buffer[6]), Vector2D(0, 0));
				break;
			}
			vec.push_back(turret);
		}
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

		texture->pool(line);

		buffer.clear();
	}



	return true;
}

bool ButtonLoader::load(std::string filename, std::vector<Button*> &vbutton, Texture *texture) {
	using namespace std;

	ifstream ifs(filename);
	string line;
	vector<string> buffer;
	Button *button;


	if (ifs.fail())return false;

	while (getline(ifs, line)) {
		if (line[0] == '#')continue;
		splitString(line, buffer);

		button = new Button(stoi(buffer[0]), stoi(buffer[1]));
		button->init(texture, buffer[2]);
		vbutton.push_back(button);

		buffer.clear();
	}



	return true;
}
