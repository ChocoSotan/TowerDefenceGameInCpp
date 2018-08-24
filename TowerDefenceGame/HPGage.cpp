#include"HPGage.h"
#include"DxLib.h"

void HPGage::draw(Vector2D enemyposition,double maxhitpoint,double hitpoint)const {
	int percentage = (int)hitpoint / maxhitpoint*100;
	DrawBox(enemyposition.getX()-32, enemyposition.getY()-32, enemyposition.getX() + 32, enemyposition.getY() -30,GetColor(255,0,0),TRUE);
	DrawBox(enemyposition.getX()-32, enemyposition.getY()-32, enemyposition.getX() - 32+(64*percentage)/100, enemyposition.getY() -30, GetColor(0, 255, 0), TRUE);
}