#include "Enemy_Fire.h"

char Enemy_Fire::pOrM = 'P';

Enemy_Fire::Enemy_Fire(char Direction) {
	char travelDirection = Direction;
}

Enemy_Fire::~Enemy_Fire() {

}

char Enemy_Fire::getName() {
	return 'F';
}

void Enemy_Fire::move(map &themap) {
	oldX = fireTrail3X;
	oldY = fireTrail3Y;
	fireTrail3X = fireTrail2X;
	fireTrail3Y = fireTrail2Y;
	fireTrail2X = fireTrail1X;
	fireTrail2Y = fireTrail1Y;
	fireTrail1X = this->getposX();
	fireTrail1Y = this->getposY();
	if (travelDirection == 'V') {
		if (pOrM == 'P') {
			if (themap.getMapVar(this->getposX() + 1, this->getposY()) == '#') {
				pOrM = 'M';
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
		else  {
			if (themap.getMapVar(this->getposX() - 1, this->getposY()) == '#') {
				pOrM = 'P';
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

		
	}
	else {
		if (pOrM == 'P') {
			if (themap.getMapVar(this->getposX(), this->getposY()+1) == '#') {
				pOrM = 'M';
				this->setposY(this->getposY() - 1);
			}
			else if (themap.getMapVar(this->getposX() , this->getposY()+1) == 'P') {
				//end game criteria
			}
			else if (themap.getMapVar(this->getposX(), this->getposY()+1) == ' ') {
				this->setposY(this->getposY() + 1);
			}
			else {
				cout << "Bugged!!" << endl;
			}
		}
		else {
			if (themap.getMapVar(this->getposX(), this->getposY()-1) == '#') {
				pOrM = 'P';
				this->setposY(this->getposY()+1);
			}
			else if (themap.getMapVar(this->getposX(), this->getposY()-1) == 'P') {
				//end game criteria
			}
			else if (themap.getMapVar(this->getposX(), this->getposY()-1) == ' ') {
				this->setposY(this->getposY() - 1);
			}
			else {
				cout << "Bugged!!" << endl;
			}
		}
	}
	themap.updateMap(oldX, oldY, ' ');
	themap.updateMap(fireTrail3X, fireTrail3Y, 'f');
	themap.updateMap(fireTrail2X, fireTrail2Y, 'f');
	themap.updateMap(fireTrail1X, fireTrail1Y, 'f');
	themap.updateMap(this->getposX(), this->getposY(), this->getName());
}