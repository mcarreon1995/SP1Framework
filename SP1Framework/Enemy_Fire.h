#pragma once
#include "Entity.h"
class Enemy_Fire:public Entity
{
private:
	char fireMovement;
public:
	Enemy_Fire();
	~Enemy_Fire();
	char getName();
	void move();
};

