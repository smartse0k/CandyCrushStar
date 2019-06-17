#pragma once

#include "candy.h"

class Game {
	int status;
	int mapSize;
	Candy *map[10][10];
	int bestScore;
	int score;
	int combo;
	int cursorX;
	int cursorY;
	int selectX;
	int selectY;
public:
	Game();
	void start();
	void makeMap();
	void drawMap();
	void drawCandy(Candy);
	bool checkPop();
	void feedCandy();
	void addScore(int);
	void processCandyCrush();
	void delay(int);
	void input();
};
