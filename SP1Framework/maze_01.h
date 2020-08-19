#pragma once
#include "map.h"

class maze_01 : public map
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
	maze_01();
	~maze_01();
};

