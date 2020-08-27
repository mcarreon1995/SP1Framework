#include "Guard.h"



Guard::Guard(char Direction) {
	char travelDirection = Direction;
}

Guard::~Guard() {

}

char Guard::getName() {
	return 'G';
}

void Guard::move(map &themap) {
	if (travelDirection == 'V') {
		if (pOrM == 'P') {
			if (themap.getMapVar(this->getposX() + 1, this->getposY()) == '#') {
				pOrM = 'M';
				this->setposX(this->getposX() - 1);
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
		else {
			if (themap.getMapVar(this->getposX() - 1, this->getposY()) == '#') {
				pOrM = 'P';
				this->setposX(this->getposX() + 1);
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


	}
	else {
		if (pOrM == 'P') {
			if (themap.getMapVar(this->getposX(), this->getposY() + 1) == '#') {
				pOrM = 'M';
				this->setposY(this->getposY() - 1);
			}
			else if (themap.getMapVar(this->getposX(), this->getposY() + 1) == (char)1) {
				//end game criteria
			}
			else if (themap.getMapVar(this->getposX(), this->getposY() + 1) == ' ') {
				this->setposY(this->getposY() + 1);
			}
			else {
				cout << "Bugged!!" << endl;
			}
		}
		else {
			if (themap.getMapVar(this->getposX(), this->getposY() - 1) == '#') {
				pOrM = 'P';
				this->setposY(this->getposY() + 1);
			}
			else if (themap.getMapVar(this->getposX(), this->getposY() - 1) == (char)1) {
				//end game criteria
			}
			else if (themap.getMapVar(this->getposX(), this->getposY() - 1) == ' ') {
				this->setposY(this->getposY() - 1);
			}
			else {
				cout << "Bugged!!" << endl;
			}
		}
	}

}