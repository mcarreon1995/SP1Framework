#pragma once
#include "Entity.h"
class Enemy_Fire:public Entity
{
private:
	char pOrM = 'P';
	char travelDirection = 'V';
	int fireTrail1X, fireTrail1Y, fireTrail2X, fireTrail2Y, fireTrail3X, fireTrail3Y, oldX, oldY = { 0 };
public:
	Enemy_Fire(char);
	~Enemy_Fire();
	char getName();
	void move(map&);
};

