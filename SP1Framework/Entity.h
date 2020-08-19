#pragma once
#include <iostream>
#include "Position.h"

class Entity
{
protected:
	Position myPos;
public:
	int getposX();
	int getposY();
	void setposX(int X);
	void setposY(int X);
	Entity();
	~Entity();
	virtual char getIcon() = 0;
	virtual void move();
	virtual void move(char);

};



