#pragma once
#include "Entity.h"
class BatBullet :
    public Entity
{
private:
	char travelDirection;
	int oldX, oldY;
public:
	BatBullet(char);
	~BatBullet();
	char getName();
	void move(map&);
};

