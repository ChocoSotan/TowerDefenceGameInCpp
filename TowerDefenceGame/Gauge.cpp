#include"Gauge.h"

void HPGauge::drawFloatingGauge(Vector2D enemyposition,double currentnumber)const {
	int percentage = (int)(currentnumber / maxnumber*100);
	DrawBox(enemyposition.getX()-32, enemyposition.getY()-32, enemyposition.getX() + 32, enemyposition.getY() -30,GetColor(255,0,0),TRUE);
	DrawBox(enemyposition.getX()-32, enemyposition.getY()-32, enemyposition.getX() - 32+(64*percentage)/100, enemyposition.getY() -30, GetColor(0, 255, 0), TRUE);
}
void TimeGauge::drawImmovableGauge(double currentnumber)const {
	int percentage = (int) (currentnumber / maxnumber * 100);
	DrawBox(0, 20, 500, 20, GetColor(255, 0, 0), TRUE);
	DrawBox(0, 20, 500*percentage/100, 20, GetColor(0, 255, 0), TRUE);
}
void MoneyGauge::drawImmovableGauge(double currentnumber)const {
	int percentage = (int)(currentnumber / maxnumber * 100);
	DrawBox(25, 45, 500, 45, GetColor(255, 0, 0), TRUE);
	DrawBox(25, 45, 500 * percentage / 100, 45, GetColor(0, 255, 0), TRUE);
}