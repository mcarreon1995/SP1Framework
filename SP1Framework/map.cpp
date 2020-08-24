#include "map.h"
#include <ctime>
#include <stdlib.h>

map::map() {

}

map::~map() {

}

void map::updateMap(int x, int y, char e) {
	mapArray[y][x] = e;
}

char map::getMapVar(int x, int y) {
	return mapArray[y][x];
}

void map::randomCollectibles() {
	srand(time(NULL));
	while (currentCollectibles < totalCollectibles) {
		for (int i = 0; i < 25; i++) {
			for (int j = 0; j < 50; j++) {
				if (getMapVar(j, i) == 'P') {
					if (rand() % 2 == 1) {
						updateMap(j, i, 'C');
						addCurrentCollectibles();
					}
				}
			}
		}
	}
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 50; j++) {
			if (getMapVar(j, i) == 'P') {
				if (rand() % 2 == 1) {
					updateMap(j, i, ' ');
				}
			}
		}
	}
}

void map::setTotalCollectibles(int t) {
	totalCollectibles = t;
}

void map::addCurrentCollectibles() {
	currentCollectibles += 1;
}