#include "BatBullet.h"
char travelDirection;
BatBullet::BatBullet(char direction, int x, int y) {
	setDirection(direction);
	origin_x = x;
	origin_y = y;
}

BatBullet::~BatBullet() {

}

char BatBullet::getName() {
	return '*';
}

void BatBullet::move(map& themap) {
	bool skip = 0;
	oldX = this->getposX();
	oldY = this->getposY();
	if (getDirection() == 'A') {
		if (themap.getMapVar(this->getposX() - 1, this->getposY()) == '#') {
			this->setposX(origin_x);
			skip = 1;
		}
		else if (themap.getMapVar(this->getposX() - 1, this->getposY()) == (char)1) {
			//end game criteria
		}
		else if (themap.getMapVar(this->getposX() - 1, this->getposY()) == ' ') {
			this->setposX(this->getposX() - 1);
		}
		else {
			cout << "Bugged!!" << endl;
		}
	}
	else if (getDirection() == 'D') {
		if (themap.getMapVar(this->getposX() + 1, this->getposY()) == '#') {
			this->setposX(origin_x);
			skip = 1;
		}
		else if (themap.getMapVar(this->getposX() + 1, this->getposY()) == (char)1) {
			//end game criteria
		}
		else if (themap.getMapVar(this->getposX() + 1, this->getposY()) == ' ') {
			this->setposX(this->getposX() + 1);
		}
		else {
			cout << "Bugged!!" << endl;
		}
	}
	else if (getDirection() == 'W') {
		if (themap.getMapVar(this->getposX(), this->getposY()-1) == '#') {
			this->setposY(origin_y);
			skip = 1;
		}
		else if (themap.getMapVar(this->getposX(), this->getposY()-1) == (char)1) {
			//end game criteria
		}
		else if (themap.getMapVar(this->getposX(), this->getposY()-1) == ' ') {
			this->setposX(this->getposY() - 1);
		}
		else {
			cout << "Bugged!!" << endl;
		}
	}
	else if (getDirection() == 'S') {
		if (themap.getMapVar(this->getposX(), this->getposY() + 1) == '#') {
			this->setposY(origin_y);
			skip = 1;
		}
		else if (themap.getMapVar(this->getposX(), this->getposY() + 1) == (char)1) {
			//end game criteria
		}
		else if (themap.getMapVar(this->getposX(), this->getposY() + 1) == ' ') {
			this->setposX(this->getposY() + 1);
		}
		else {
			cout << "Bugged!!" << endl;
		}
	}
	if(skip == 0)
		themap.updateMap(this->getposX(), this->getposY(), this->getName());
	themap.updateMap(oldX, oldY, ' ');
}