#include <iostream>
#include <ctime>
#include "game.h"
#include "candy.h"

using namespace std;

Game::Game() {
	bestScore = 0;
	score = 0;
	combo = 0;
	selectX = 0;
	selectY = 0;
}

void Game::delay(int ms) {
	clock_t delay = ms;
	clock_t start = clock();
	while (clock() - start < delay);
}

void Game::start() {
	while(true) {
		cout << "맵 크기를 입력해보세요 (5 ~ 10): ";
		cin >> mapSize;

		if(mapSize >= 5 && mapSize <= 10) {
			break;
		}
	}

	makeMap();
	processCandyCrush();
}

void Game::makeMap() {
	int x, y;
	for(x=0; x<mapSize; x++) {
		for(y=0; y<mapSize; y++) {
			Candy *candy = new Candy();
			map[x][y] = candy;
		}
		cout << endl;
	}
}

void Game::drawMap() {
	system("cls");

	cout << endl;
	cout << "  C a n d y - C r u s h ★ S t a r" << endl;
	cout << endl;
	cout << "  최고점수 => " << bestScore << endl;
	cout << "  현재점수 => " << score << endl;
	cout << "  플레이어 => " << "테스트" << endl;
	cout << "      콤보 => " << combo << endl;
	cout << endl;

	int x, y;
	cout << "  ";
	for(y=-1; y<mapSize; y++) {
		for(x=-1; x<mapSize; x++) {
			if(y == -1) {
				if(x == -1) {
					continue;
				} else {
					cout << "  " << (x + 1);
				}
			} else {
				if(x == -1) {
					cout << "  " << (y + 1) << " ";
				} else {
					Candy *candy = map[x][y];

					if(x == selectX && y == selectY) {
						candy->drawCandy(true);
					} else {
						candy->drawCandy(false);
					}
					cout << " ";
				}
			}
		}
		cout << endl << endl;
	}
}

void Game::processCandyCrush() {
	combo = 0;
	
	while( checkPop() ) {
		drawMap();
		delay(500);

		combo++;
		feedCandy();

		drawMap();
		delay(500);
	}
}

bool Game::checkPop() {
	int pop = 0;

	int x, y;

	// ■■■ 검사
	for(y=0; y<mapSize; y++) {
		for(x=0; x<mapSize - 2; x++) {
			Candy *c1, *c2, *c3;
			int t1, t2, t3;

			c1 = map[x][y];
			c2 = map[x + 1][y];
			c3 = map[x + 2][y];

			t1 = c1->getType();
			t2 = c2->getType();
			t3 = c3->getType();
			
			if(t1 == t2 && t2 == t3) {
				c1->setPop();
				c2->setPop();
				c3->setPop();
				addScore(10 * 3);
				return true;
			}
		}
	}

	// 세로 ■■■ 검사
	for(y=0; y<mapSize - 2; y++) {
		for(x=0; x<mapSize; x++) {
			Candy *c1, *c2, *c3;
			int t1, t2, t3;

			c1 = map[x][y];
			c2 = map[x][y + 1];
			c3 = map[x][y + 2];

			t1 = c1->getType();
			t2 = c2->getType();
			t3 = c3->getType();
			
			if(t1 == t2 && t2 == t3) {
				c1->setPop();
				c2->setPop();
				c3->setPop();
				addScore(10 * 3);
				return true;
			}
		}
	}

	return false;
}

void Game::feedCandy() {
	int x, y, yy;

	for(y=mapSize - 1; y>=0; y--) {
		for(x=0; x<mapSize; x++) {
			Candy *c = map[x][y];

			if(c->getPop()) {
				delete c;

				if(y > 0) {
					for(yy=y; yy>=0; yy--) {
						map[x][yy] = map[x][yy - 1];
					}
				}

				map[x][0] = new Candy();

				x--; // 다시 검사를 위함
			}
		}
	}
}

void Game::addScore(int score) {
	score = score + score * (combo / 2);

	this->score += score;
	if(this->score >= bestScore) {
		bestScore = this->score;
	}
}