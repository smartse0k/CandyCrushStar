#include <iostream>
#include <ctime>
#include <conio.h>
#include "game.h"
#include "candy.h"

using namespace std;

Game::Game() {
	bestScore = 0;
	score = 0;
	combo = 0;
	cursorX = 0;
	cursorY = 0;
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
		cout << "�� ũ�⸦ �Է��غ����� (5 ~ 10): ";
		cin >> mapSize;

		if(mapSize >= 5 && mapSize <= 10) {
			break;
		}
	}

	makeMap();
	while(true) {
		processCandyCrush();
		input();
	}
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
	cout << "  C a n d y - C r u s h �� S t a r" << endl;
	cout << endl;
	cout << "  �ְ����� => " << bestScore << endl;
	cout << "  �������� => " << score << endl;
	cout << "  �÷��̾� => " << "�׽�Ʈ" << endl;
	cout << "      �޺� => " << combo << endl;
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

					if(x == cursorX && y == cursorY) {
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

void Game::input() {
	cursorX = 0;
	cursorY = 0;
	selectX = -1;
	selectY = -1;

	while(true) {
		drawMap();
		
		if(selectX == -1 && selectY == -1) {
			cout << "  [ĵ�� ���� ���] ����Ű: Ŀ�� �̵� / �����̽���: ĵ�� ����";
		} else {
			cout << "  [ĵ�� �̵� ���] ����Ű: ���õ� ĵ�� �̵� / �����̽���: ĵ�� ���� ����";
		}

		int key = getch();
		switch(key) {
		case 72: // ��
		case 119: // w
			if(selectX == -1 && selectY == -1) {
				if(cursorY > 0) {
					cursorY--;
				}
			} else {

			}
			break;
		case 80: // ��
		case 115: // s
			if(selectX == -1 && selectY == -1) {
				if(cursorY < mapSize - 1) {
					cursorY++;
				}
			} else {

			}
			break;
		case 75: // ��
		case 97: // a
			if(selectX == -1 && selectY == -1) {
				if(cursorX > 0) {
					cursorX--;
				}
			} else {

			}
			break;
		case 77: // ��
		case 100: // d
			if(selectX == -1 && selectY == -1) {
				if(cursorX < mapSize - 1) {
					cursorX++;
				}
			} else {

			}
			break;
		case 32: // �����̽�
		case 13: // ����
		case 10:
			if(selectX == -1 && selectY == -1) {
				selectX = cursorX;
				selectY = cursorY;
			} else {
				selectX = -1;
				selectY = -1;
			}
			break;
		}
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

	// ���� �˻�
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

	// ���� ���� �˻�
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

				x--; // �ٽ� �˻縦 ����
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