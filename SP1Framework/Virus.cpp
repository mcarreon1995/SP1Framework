#include "Virus.h"

Virus::Virus(char Direction) {
	setDirection(Direction);
}

Virus::~Virus() {

}

char Virus::getName() {
	return '*';
}

void Virus::move(map& themap) {
	int oldX, oldY;
	oldX = this->getposX();
	oldY = this->getposY();
	if (getDirection() == 'A' || getDirection() == 'D') {
		if (pOrM == 'P') {
			if (themap.getMapVar(this->getposX() + 1, this->getposY()) == '#') {
				pOrM = 'M';
				this->setposX(this->getposX() - 1);
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
	/*switch (this->getDirection()) {
	case 'A':
		if (themap.getMapVar(this->getposX() - 1, this->getposY()) == '#') {
			this->setposX(this->getposX() + 1);
			this->setDirection('D');
		}
		else if (themap.getMapVar(this->getposX() + 1, this->getposY()) == ' ') {
			this->setposX(this->getposX() + 1);
		}
		break;
	case 'D':
		if (themap.getMapVar(this->getposX() + 1, this->getposY()) == '#') {
			this->setposX(this->getposX() - 1);
			this->setDirection('A');
		}
		else if (themap.getMapVar(this->getposX() + 1, this->getposY()) == ' ') {
			this->setposX(this->getposX() + 1);
		}
		break;
	case 'W':
		if (themap.getMapVar(this->getposX(), this->getposY() - 1) == '#') {
			this->setposX(this->getposY() + 1);
			this->setDirection('S');
		}
		else if (themap.getMapVar(this->getposX() + 1, this->getposY()) == ' ') {
			this->setposX(this->getposX() + 1);
		}
		break;
	case 'S':
		if (themap.getMapVar(this->getposX(), this->getposY() + 1) == '#') {
			this->setposX(this->getposY() - 1);
			this->setDirection('W');
		}
		else if (themap.getMapVar(this->getposX(), this->getposY() + 1) == ' ') {
			this->setposX(this->getposY() + 1);
		}
		break;
	}*/
	themap.updateMap(this->getposX(), this->getposY(), this->getName());
	themap.updateMap(oldX, oldY, ' ');
}
