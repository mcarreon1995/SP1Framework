#pragma once
#include "map.h"

class maze_03 : public map
{
private:
	char mazeArray[25][50] = {
	{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',},
	{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',},
	{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#','#','#',' ',' ',' ','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#',},
	{'#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#','#','#',' ',' ',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#',' ','#',},
	{'#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#','#','#',' ',' ',' ','#','#','#','#','#',' ',' ',' ',' ','#','#',' ','#',' ','#',},
	{'#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ',' ',' ','#','#','#','#','#',' ','#','#',' ','#','#',' ','#',' ','#',},
	{'#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#',' ','#','#',' ','#',' ','#',},
	{'#',' ','#','#','#','#',' ',' ',' ',' ',' ','#','#','#','#',' ','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#',' ','#','#',' ','#',' ','#',},
	{'#',' ','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ','#',' ','#',},
	{'#',' ','#','#','#','#',' ',' ','S',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ','#',' ','#',},
	{'#',' ','#','#','#','#',' ',' ',' ',' ',' ','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ','#','#','#',' ',' ',' ',' ','#','#',' ','#',' ','#',},
	{'#',' ','#','#','#','#',' ',' ',' ',' ',' ','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ','#','#','#',' ',' ',' ',' ','#','#',' ','#',' ','#',},
	{'#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#',' ',' ',' ','#','#','#','#','#',' ','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ','#','#','#','#','#',' ',' ','#','#',' ','#',' ','#',},
	{'#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#',' ','#','#','#','#','#',' ','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ','#','#','#','#','#',' ',' ','#','#',' ','#',' ','#',},
	{'#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#',' ',' ',' ','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#',' ',' ','#','#',' ','#','E','#',},
	{'#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#',' ','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#',' ',' ','#','#',' ','#','#','#',},
	{'#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#',' ','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',},
	{'#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#',' ','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#',' ',' ',' ','#','#','#','#','#',' ','#',},
	{'#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#',' ',' ',' ','#','#','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#',' ','#',},
	{'#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#',' ','#',},
	{'#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#',' ',' ',' ','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',},
	{'#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#',},
	{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',},
	{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',},
	{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',}
	};
public:
	maze_03();
	~maze_03();
};

