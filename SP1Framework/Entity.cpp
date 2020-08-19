#include "Entity.h"

Entity::Entity() {

};

Entity::~Entity() {

};

void Entity::move() {

};
void Entity::move(char) {

}

int Entity::getposX() {
	return myPos.getXpos();
}
int Entity::getposY() {
	return myPos.getYpos();
}
void Entity::setposX(int X) {
	if (X > 19)
		X = 19;
	else if (X < 0)
		X = 0;
	myPos.setXpos(X);
}
void Entity::setposY(int Y) {
	if (Y > 19)
		Y = 19;
	else if (Y < 0)
		Y = 0;
	myPos.setYpos(Y);
}
