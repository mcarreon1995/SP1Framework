#include "maze_03.h"

maze_03::maze_03() {
	setTotalCollectibles(14);
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 50; j++) {
			updateMap(j, i, mazeArray[i][j]);
		}
	}
	randomCollectibles();
}

maze_03::~maze_03() {

}
