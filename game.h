#pragma once

#include "candy.h"

class Game {
	int status;
	int mapSize;
	Candy *map[10][10];
	int bestScore;
	int score;
public:
	Game();
	void start();
	void makeMap();
	void drawMap();
	void drawCandy(Candy);
};
