#pragma once
#include "Entity.h"
class BatBullet :
    public Entity
{
private:
	int oldX, oldY;
	int origin_x, origin_y;
public:
	BatBullet(char direction, int x, int y);
	~BatBullet();
	char getName();
	void move(map&);
};

