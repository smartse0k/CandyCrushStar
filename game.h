#pragma once

#include "candy.h"
#include "player.h"

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
	int amountMove;
	int leftAmountMove;
	Player *players;
	int playernum;
	int currentPlayer;
public:
	Game();
	void start();
	void makeMap();
	void drawMap();
	void drawCandy(Candy);
	bool checkPop();
	void pop(Candy *, int, int);
	void feedCandy();
	void addScore(int);
	void processCandyCrush();
	void delay(int);
	void input();
	void moveCandy(int, int, int);
	void replaceToBombCandy(int, int);
	void deleteMap();
};
