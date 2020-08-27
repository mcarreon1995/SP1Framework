#pragma once
#include "Entity.h"
class Virus :
    public Entity
{
private:
    char pOrM;
	char travelDirection;
	int oldX, oldY;
public:
	Virus(char);
	~Virus();
	char getName();
	void move(map&);
};

