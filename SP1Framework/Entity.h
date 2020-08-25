#pragma once
#include <iostream>
#include "Position.h"
#include "map.h"

using namespace std;

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
	virtual char getName() = 0;
	virtual void move(map&);
	virtual void move(char);

};



