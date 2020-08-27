#pragma once
#include "Entity.h"
class Hacker :
    public Entity
{
private:
	static char pOrM;
	char travelDirection;
	int oldX, oldY;
public:
	Hacker(char);
	~Hacker();
	char getName();
	void move(map&);
};
