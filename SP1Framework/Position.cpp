#include "Position.h"

Position::Position()
{
	x = -1;
	y = -1;
}

Position::~Position()
{

}

void Position::setXpos(int Xpos)
{
	x = Xpos;
}

int Position::getXpos()
{
	return x;
}

void Position::setYpos(int Ypos)
{
	y = Ypos;
}

int Position::getYpos()
{
	return y;
}