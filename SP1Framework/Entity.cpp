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
	myPos.setXpos(X);
}
void Entity::setposY(int Y) {
	myPos.setYpos(Y);
}
