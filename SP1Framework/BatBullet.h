#pragma once
#include "Entity.h"
class BatBullet :
    public Entity
{
private:
	int oldX, oldY;
	char travelDirection;
public:
	BatBullet(char);
	~BatBullet();
	char getName();
	void move(map&);
};

