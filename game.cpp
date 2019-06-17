#include <iostream>
#include "game.h"
#include "candy.h"

using namespace std;

Game::Game() {
	bestScore = 0;
	score = 0;
	combo = 0;
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
	while( checkPop() ) {
		combo++;
	}
	drawMap();
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
					candy->drawCandy();
					cout << " ";
				}
			}
		}
		cout << endl << endl;
	}
}

bool Game::checkPop() {
	int pop = 0;

	// ■■■ 검사
	int x, y;
	for(y=0; y<mapSize; y++) {
		for(x=0; x<mapSize - 2; x++) {
			Candy *c1, *c2, *c3;
			int t1, t2, t3;

			c1 = map[x][y];
			c2 = map[x][y];
			c3 = map[x][y];

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
	int x, y;
}

void Game::addScore(int score) {
	score = score + score * (combo / 2);

	this->score += score;
	if(this->score >= bestScore) {
		bestScore = this->score;
	}
}