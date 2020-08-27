#include "Virus.h"
Virus::Virus(char Direction) {
	char travelDirection = Direction;
}

Virus::~Virus() {

}

char Virus::getName() {
	return 'V';
}

void Virus::move(map& themap) {
	if (travelDirection == 'V') {
		if (pOrM == 'P') {
			if (themap.getMapVar(this->getposX() + 1, this->getposY()) == '#') {
				pOrM = 'M';
				this->setposX(this->getposX() - 2);
			}
			else if (themap.getMapVar(this->getposX() + 2, this->getposY()) == '#') {
				pOrM = 'M';
				this->setposX(this->getposX());
			}
			else if (((themap.getMapVar(this->getposX() + 1 , this->getposY())) == 'P') || ((themap.getMapVar(this->getposX() + 2, this->getposY())) == 'P')) {
				//end game criteria
			}
			else if (themap.getMapVar(this->getposX() + 2, this->getposY()) == ' ') {
				this->setposX(this->getposX() + 2);
			}
			else {
				cout << "Bugged!!" << endl;
			}
		}
		else {
			if (themap.getMapVar(this->getposX() - 1, this->getposY()) == '#') {
				pOrM = 'P';
				this->setposX(this->getposX() + 2);
			}
			else if (themap.getMapVar(this->getposX() - 2, this->getposY()) == '#') {
				pOrM = 'P';
				this->setposX(this->getposX());
			}
			else if (((themap.getMapVar(this->getposX() - 1, this->getposY())) == 'P') || ((themap.getMapVar(this->getposX() - 2, this->getposY())) == 'P')) {
				//end game criteria
			}
			else if (themap.getMapVar(this->getposX() - 2, this->getposY()) == ' ') {
				this->setposX(this->getposX() - 2);
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
				this->setposY(this->getposY() - 2);
			}
			else if (themap.getMapVar(this->getposX(), this->getposY()+2) == '#') {
				pOrM = 'M';
				this->setposX(this->getposX());
			}
			else if (((themap.getMapVar(this->getposX(), this->getposY()+1)) == 'P') || ((themap.getMapVar(this->getposX(), this->getposY()+2)) == 'P')) {
				//end game criteria
			}
			else if (themap.getMapVar(this->getposX(), this->getposY() + 2) == ' ') {
				this->setposY(this->getposY() + 2);
			}
			else {
				cout << "Bugged!!" << endl;
			}
		}
		else {
			if (themap.getMapVar(this->getposX(), this->getposY() - 1) == '#') {
				pOrM = 'P';
				this->setposY(this->getposY() + 2);
			}
			else if (themap.getMapVar(this->getposX(), this->getposY() - 2) == '#') {
				pOrM = 'P';
				this->setposX(this->getposX());
			}
			else if (((themap.getMapVar(this->getposX(), this->getposY() - 1)) == 'P') || ((themap.getMapVar(this->getposX(), this->getposY() - 2)) == 'P')) {
				//end game criteria
			}
			else if (themap.getMapVar(this->getposX(), this->getposY() - 2) == ' ') {
				this->setposY(this->getposY() - 2);
			}
			else {
				cout << "Bugged!!" << endl;
			}

		}
	}

}
