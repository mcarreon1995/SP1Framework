#pragma once
#include "Entity.h"
class Bat :
    public Entity
{
public:
	Bat();
	~Bat();
	char getName();
	void move();
};

