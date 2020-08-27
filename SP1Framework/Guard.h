#pragma once
#include "Entity.h"
class Guard :public Entity
{
private:
	char pOrM = 'P';
	char travelDirection;
	int oldX, oldY;
public:
	Guard(char);
	~Guard();
	char getName();
	void move(map&);
};

