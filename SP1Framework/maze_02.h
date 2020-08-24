#pragma once
#include "map.h"
class maze_02 : public map
{
private:
	char mazeArray[25][50] = {
	{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', },
	{ '#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#', },
	{ '#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#', },
	{ '#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#', },
	{ '#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#', },
	{ '#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#', },
	{ '#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#', },
	{ '#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#', },
	{ '#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#', },
	{ '#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#', },
	{ '#',' ','#','#','#','#',' ','#','#','#',' ',' ',' ','#','#','#',' ','#','#','#','#',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#', },
	{ '#',' ','#','#','#','#',' ','#','#','#',' ','S',' ','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#', },
	{ '#',' ','#','#','#','#',' ','#','#','#',' ',' ',' ','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#', },
	{ '#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#', },
	{ '#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#', },
	{ '#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#', },
	{ '#',' ','#','#','#','#',' ','#','#','#',' ','#',' ','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#', },
	{ '#',' ','#','#','#','#',' ','#','#','#',' ','#',' ','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#', },
	{ '#',' ','#','#','#','#',' ','#','#','#',' ','#',' ','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#', },
	{ '#',' ','#','#','#','#',' ','#','#','#',' ','#',' ','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#', },
	{ '#','E','#','#','#','#',' ','#','#','#',' ','#',' ','#','#','#',' ','#','#','#','#',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#', },
	{ '#','#','#','#','#','#',' ','#','#','#',' ','#',' ','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#', },
	{ '#','#','#','#','#','#',' ','#','#','#',' ','#',' ','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#', },
	{ '#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#', },
	{ '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#', }
	};
public:
	maze_02();
	~maze_02();
};
