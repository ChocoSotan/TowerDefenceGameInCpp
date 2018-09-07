#include "Enemy.h"

#include "Vector2D.h"
#include "Texture.h"
#include "DxLib.h"

#include <math.h>
#include <sstream>
#include <iomanip>



void NormalEnemy::update(const std::vector<Vector2D> &vpath) {
	Vector2D nextpos;
	double nextangle;

	/* move */
	// taken knockback
	while (this->knockback > EPSILON) {
		nextangle = this->getPosition().getAngleTo(vpath[currentpoint]);
		nextpos.setX(nextpos.getX() + this->knockback * cos(nextangle));
		nextpos.setY(nextpos.getY() + this->knockback * sin(nextangle));
		nextangle = nextpos.getAngleTo(vpath[currentpoint]);

		// if the position will behind start position
		if (currentpoint == 0 && fabs((this->position.getAngleTo(vpath[currentpoint]) - nextangle)) > EPSILON) {
			this->position = vpath[0];
			knockback = 0;
		}

		// if the angle to the target is different before and after the movement 
		if (fabs((this->position.getAngleTo(vpath[currentpoint]) - nextangle)) > EPSILON) {
			this->position = vpath[currentpoint];
			this->knockback -= this->position.getAbsTo(vpath[currentpoint]);
			currentpoint--;
		}
		else {
			this->position.setX(this->position.getX() + this->knockback * cos(nextangle));
			this->position.setY(this->position.getY() + this->knockback * sin(nextangle));
			this->knockback = 0;
			break;
		}
	}

	double movecount = this->movespeed;

	// move forward
	while (movecount > EPSILON) {
		if (currentpoint != vpath.size()-1) {
			this->setAngle(this->getPosition().getAngleTo(vpath[currentpoint + 1]));
		}
		// if the position will over the base
		else {
			// take damage for base
			
			// reset position to start
			this->position = vpath[0];
			currentpoint = 0;

			break;
		}

		nextpos.setX(this->position.getX() + movecount * cos(this->angle));
		nextpos.setY(this->position.getY() + movecount * sin(this->angle));
		nextangle = nextpos.getAngleTo(vpath[currentpoint + 1]);

		// if the angle to the target is different before and after the movement 
		if (fabs(this->angle - nextangle) > EPSILON && this->position != vpath[0]) {
			movecount -= this->position.getAbsTo(vpath[currentpoint + 1]);
			this->position = vpath[currentpoint + 1];
			currentpoint++;
		}
		else {
			this->position.setX(this->position.getX() + movecount * cos(nextangle));
			this->position.setY(this->position.getY() + movecount * sin(nextangle));
			movecount = 0;
			break;
		}
	}
}

double EnemyBase::getDistanceToBase(const std::vector<Vector2D> &vpath) const {
	double ret = 0;
	for (int i = vpath.size() - 1; i > this->currentpoint; i--) {
		ret += vpath[i].getAbsTo(vpath[i - 1]);
	}
	ret -= this->position.getAbsTo(vpath[currentpoint]);
	
	return ret;
}

std::string NormalEnemy::getStatusText() const {
	std::stringstream ss;
	ss << "Type : Normal\n"
		<< "HitPoint : " << std::setprecision(1) << this->hitpoint << "\n"
		<< "Speed : " << std::setprecision(2) << this->movespeed << "\n"
		<< "Damage : " << this->attackpower << "\n"
		<< "Reward : " << this->resourcereward << "\n";
	
	return ss.str();
}

void NormalEnemy::draw(const Texture &texture) {
	DrawRotaGraph(this->position.getX(), this->getPosition().getY(), 1.0, this->angle, texture.getHandle("texture/Game/Enemy/Normal.png"), TRUE);
}