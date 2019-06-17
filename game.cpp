#include <iostream>
#include "game.h"
#include "candy.h"

using namespace std;

Game::Game() {
	bestScore = 0;
	score = 0;
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

	cout << "C a n d y - C r u s h ★ S t a r" << endl << endl;

	int x, y;
	cout << " ";
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
					cout << (y + 1) << " ";
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