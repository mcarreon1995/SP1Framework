#pragma once
#include <iostream>
#include "Position.h"
#include "map.h"

using namespace std;

class Entity
{
private:
	char travelDirection;
	int moveSpeed;
protected: 
	Position myPos;
public:
	int getposX();
	int getposY();
	char getDirection();
	void setposX(int X);
	void setposY(int X);
	void setDirection(char t);
	void changeSpeed(int s);
	Entity();
	~Entity();
	virtual char getName() = 0;
	virtual void move(map&);
	virtual void move(char);
	int getSpeed();

};



