#include "BatBullet.h"
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
		switch (themap.getMapVar(this->getposX(), this->getposY() - 1)) {
		case '#':
			this->setposY(origin_y);
		case ' ':
			this->setposY(this->getposY() - 1);
		}
	}
	else if (getDirection() == 'S') {
		switch (themap.getMapVar(this->getposX(), this->getposY() + 1)) {
		case '#':
			this->setposY(origin_y);
		case ' ':
			this->setposY(this->getposY() + 1);
		}
	}
	themap.updateMap(this->getposX(), this->getposY(), this->getName());
	themap.updateMap(oldX, oldY, ' ');
}