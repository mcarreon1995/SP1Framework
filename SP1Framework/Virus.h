#pragma once
#include "Entity.h"
class Virus :
    public Entity
{
public:
	Virus();
	~Virus();
	char getName();
	void move();
};

