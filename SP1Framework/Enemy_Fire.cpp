#include "Enemy_Fire.h"

char Enemy_Fire::upOrDown = 'U';

Enemy_Fire::Enemy_Fire() {

}

Enemy_Fire::~Enemy_Fire() {

}

char Enemy_Fire::getName() {
	return 'F';
}



void Enemy_Fire::move(map &themap) {
	if (upOrDown == 'U') {
		oldX = fireTrailX;
		oldY = fireTrailY;
		fireTrailX = this->getposX();
		fireTrailY = this->getposY();
		if (themap.getMapVar(this->getposX() + 1, this->getposY()) == '#') {
			upOrDown = 'D';
			this->setposX(this->getposX() - 1);
		}
		else if (themap.getMapVar(this->getposX() + 1, this->getposY()) == 'P') {
			//end game criteria
		}
		else if (themap.getMapVar(this->getposX() + 1, this->getposY()) == ' ') {
			this->setposX(this->getposX() + 1);
		}
		else {
			cout << "Bugged!!" << endl;
		}
	}
	else {
		if (themap.getMapVar(this->getposX() - 1, this->getposY()) == '#') {
			upOrDown = 'U';
			this->setposX(this->getposX() + 1);
		}
		else if (themap.getMapVar(this->getposX() - 1, this->getposY()) == 'P') {
			//end game criteria
		}
		else if (themap.getMapVar(this->getposX() - 1, this->getposY()) == ' ') {
			this->setposX(this->getposX() - 1);
		}
		else {
			cout << "Bugged!!" << endl;
		}
	}
	themap.updateMap(this->getposX(), this->getposY(), this->getName());
	themap.updateMap(fireTrailX, fireTrailY, 'f');
	themap.updateMap(oldX, oldY, ' ');
}