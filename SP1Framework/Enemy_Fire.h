#pragma once
#include "Entity.h"
class Enemy_Fire:public Entity
{
private:
	static char upOrDown;
	int fireTrailX, fireTrailY, oldX, oldY;
public:
	Enemy_Fire();
	~Enemy_Fire();
	char getName();
	void move(map&);
};

