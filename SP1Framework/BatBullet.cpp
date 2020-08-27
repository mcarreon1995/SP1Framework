#include "BatBullet.h"
char travelDirection;
BatBullet::BatBullet(char direction) {
	char travelDirection = direction;
}

BatBullet::~BatBullet() {

}

char BatBullet::getName() {
	return '* ';
}

void BatBullet::move(map& themap) {
	bool skip = 0;
	oldX = this->getposX();
	oldY = this->getposY();
	if (travelDirection == 'W') {
		if (themap.getMapVar(this->getposX() - 1, this->getposY()) == '#') {
			delete this;
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
	else if (travelDirection == 'S') {
		if (themap.getMapVar(this->getposX() + 1, this->getposY()) == '#') {
			delete this;
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
	else if (travelDirection == 'A') {
		if (themap.getMapVar(this->getposX(), this->getposY()-1) == '#') {
			delete this;
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
	else if (travelDirection == 'D') {
		if (themap.getMapVar(this->getposX(), this->getposY() + 1) == '#') {
			delete this;
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