#include "maze_02.h"


maze_02::maze_02() {
	setTotalCollectibles(8);
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 50; j++) {
			updateMap(j, i, mazeArray[i][j]);
		}
	}
	randomCollectibles();
}

maze_02::~maze_02() {

}
