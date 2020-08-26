#pragma once
#include "Entity.h"
class Guard :public Entity
{
private:
	static char pOrM;
	int oldX, oldY;
	char Direction;
public:
	Guard(char);//H for horrizontal movement, V for vertical movement
	~Guard();
	char getName();
	void move(map&);
};

