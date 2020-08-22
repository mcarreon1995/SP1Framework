#pragma once
#include "Entity.h"
class Guard :public Entity
{
public:
	Guard();
	~Guard();
	char getName();
	void move();
};

