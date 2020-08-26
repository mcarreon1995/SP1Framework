#include "Guard.h"

char Guard::pOrM = 'P';
Guard::Guard(char input) {
	char Direction = input;
}

Guard::~Guard() {

}

char Guard::getName() {
	return 'G';
}

void Guard::move(map &themap) {
	if (Direction == V) {
		if (pOrM == 'P') {
			oldX = this->getposX();
			oldY = this->getposY();
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
		else {
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
		themap.updateMap(this->getposX(), this->getposY(), this->getName());
		themap.updateMap(oldX, oldY, ' ');
	}
	else {
		if (pOrM == 'P') {
			oldX = this->getposX();
			oldY = this->getposY();
			if (themap.getMapVar(this->getposX() , this->getposY()+1) == '#') {
				pOrM = 'M';
				this->setposX(this->getposY() - 1);
			}
			else if (themap.getMapVar(this->getposX(), this->getposY()+1) == 'P') {
				//end game criteria
			}
			else if (themap.getMapVar(this->getposX(), this->getposY()+1) == ' ') {
				this->setposX(this->getposY() + 1);
			}
			else {
				cout << "Bugged!!" << endl;
			}
		}
		else {
			if (themap.getMapVar(this->getposX(), this->getposY()-1) == '#') {
				pOrM = 'P';
				this->setposX(this->getposY() + 1);
			}
			else if (themap.getMapVar(this->getposX(), this->getposY()-1) == 'P') {
				//end game criteria
			}
			else if (themap.getMapVar(this->getposX(), this->getposY()-1) == ' ') {
				this->setposX(this->getposY() - 1);
			}
			else {
				cout << "Bugged!!" << endl;
			}
		}
		themap.updateMap(this->getposX(), this->getposY(), this->getName());
		themap.updateMap(oldX, oldY, ' ');
	}
}