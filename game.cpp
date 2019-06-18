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
	cout << endl;
	cout << "  C a n d y - C r u s h ★ S t a r" << endl;
	cout << endl;

	while(true) {
		cout << "  맵 크기를 입력해보세요 (5 ~ 10): ";
		cin >> mapSize;

		if(mapSize >= 5 && mapSize <= 10) {
			break;
		}
	}

	cout << endl;
	
	while(true) {
		cout << "  캔디 이동수 제한을 입력해보세요 (5 ~ 99): ";
		cin >> amountMove;

		if(amountMove >= 5 || amountMove <= 99) {
			break;
		}
	}

	cout << endl;

	while(true) {
		cout << "  참여할 인원 수를 입력해보세요 (1 ~ 10): ";
		cin >> playernum;

		if(playernum >= 1 || playernum <= 10) {
			break;
		}
	}

	cout << endl;

	players = new Player[playernum];
	for(int i=0; i<playernum; i++) {
		char name[100];
		cout << "     " << (i + 1) << "번째 플레이어의 이름을 입력해보세요: ";
		cin >> name;
		//cout << "입력됨: " << name << endl;
		players[i].setName(name);
	}

	/*
	for(int i=0; i<playernum; i++) {
		cout << "플레이어" << (i+1) << ": " << players[i].getName() << endl;
	}
	*/

	for(int i=0; i<playernum; i++) {
		currentPlayer = i;
		score = 0;
		leftAmountMove = amountMove;

		makeMap();
		processCandyCrush();
		while(leftAmountMove > 0) {
			input();
			processCandyCrush();
		}
		deleteMap();

		players[i].setScore(score);

		cout << endl << endl;
		cout << "  플레이어 '" << players[i].getName() << "'의 차례가 끝났어요" << endl;
		while(true) {
			cout << "    계속 하려면 1을 입력하세요: ";
			int i;
			cin >> i;
			if(i == 1) {
				break;
			}
		}
	}

	system("cls");
	cout << endl;
	cout << "  C a n d y - C r u s h ★ S t a r" << endl;
	cout << endl;
	cout << "  성적표" << endl;
	for(int i=0; i<playernum; i++) {
		cout << "    " << players[i].getName() << " => " << players[i].getScore() << "점" << endl;
	}
	cout << endl;
	cout << " THE END." << endl;

	int a;
	cin >> a;
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

void Game::deleteMap() {
	int x, y;
	for(x=0; x<mapSize; x++) {
		for(y=0; y<mapSize; y++) {
			delete map[x][y];
		}
	}
}

void Game::drawMap() {
	system("cls");

	cout << endl;
	cout << "  C a n d y - C r u s h ★ S t a r" << endl;
	cout << endl;
	cout << "  최고점수 => " << bestScore << endl;
	cout << "  현재점수 => " << score << endl;
	cout << "  플레이어 => " << players[currentPlayer].getName() << endl;
	cout << "  남은회수 => " << leftAmountMove << endl;
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

void Game::moveCandy(int x, int y, int dir) {
	switch(dir) {
	case 'w':
		if(selectY > 0) {
			Candy *thisCandy, *targetCandy;
			thisCandy = map[x][y];
			targetCandy = map[x][y - 1];
			map[x][y] = targetCandy;
			map[x][y - 1] = thisCandy;
		}
		break;
	case 's':
		if(selectY < mapSize - 1) {
			Candy *thisCandy, *targetCandy;
			thisCandy = map[x][y];
			targetCandy = map[x][y + 1];
			map[x][y] = targetCandy;
			map[x][y + 1] = thisCandy;
		}
		break;
	case 'a':
		if(selectX > 0) {
			Candy *thisCandy, *targetCandy;
			thisCandy = map[x][y];
			targetCandy = map[x - 1][y];
			map[x][y] = targetCandy;
			map[x - 1][y] = thisCandy;
		}
		break;
	case 'd':
		if(selectX < mapSize - 1) {
			Candy *thisCandy, *targetCandy;
			thisCandy = map[x][y];
			targetCandy = map[x + 1][y];
			map[x][y] = targetCandy;
			map[x + 1][y] = thisCandy;
		}
		break;
	}

	leftAmountMove--;
}

void Game::input() {
	cursorX = 0;
	cursorY = 0;
	selectX = -1;
	selectY = -1;

	while(true) {
		drawMap();
		
		if(selectX == -1 && selectY == -1) {
			cout << "  [캔디 선택 모드] 방향키: 커서 이동 / 스페이스바: 캔디 선택";
		} else {
			cout << "  [캔디 이동 모드] 방향키: 선택된 캔디 이동 / 스페이스바: 캔디 선택 해제";
		}

		int key = _getch();
		switch(key) {
		case 72: // 위
		case 119: // w
			if(selectX == -1 && selectY == -1) {
				if(cursorY > 0) {
					cursorY--;
				}
			} else {
				moveCandy(selectX, selectY, 'w');
				selectX = -1;
				selectY = -1;
				return;
			}
			break;
		case 80: // 아래
		case 115: // s
			if(selectX == -1 && selectY == -1) {
				if(cursorY < mapSize - 1) {
					cursorY++;
				}
			} else {
				moveCandy(selectX, selectY, 's');
				selectX = -1;
				selectY = -1;
				return;
			}
			break;
		case 75: // 왼쪽
		case 97: // a
			if(selectX == -1 && selectY == -1) {
				if(cursorX > 0) {
					cursorX--;
				}
			} else {
				moveCandy(selectX, selectY, 'a');
				selectX = -1;
				selectY = -1;
				return;
			}
			break;
		case 77: // 오른쪽
		case 100: // d
			if(selectX == -1 && selectY == -1) {
				if(cursorX < mapSize - 1) {
					cursorX++;
				}
			} else {
				moveCandy(selectX, selectY, 'd');
				selectX = -1;
				selectY = -1;
				return;
			}
			break;
		case 32: // 스페이스
		case 13: // 엔터
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

void Game::pop(Candy *candy, int x, int y) {
	int candyAttribute = candy->getCandyAttribute();

	switch(candyAttribute) {
	case CANDY_DEFAULT:
		// x
		break;
	case CANDY_BOMB:
		int testX = 0, testY = 0;
		if(x > 0) { // 왼
			map[x - 1][y]->setPop();
			testX++;
		}
		if(y > 0) { // 위
			map[x][y - 1]->setPop();
			testY++;
		}
		if(x < mapSize - 1) { // 아
			map[x + 1][y]->setPop();
			testX++;
		}
		if(y < mapSize - 1) { // 오
			map[x][y + 1]->setPop();
			testY++;
		}
		break;
	}

	candy->setPop();
}

void Game::replaceToBombCandy(int x, int y) {
	Candy *candy = map[x][y];
	Candy *bombcandy = new BombCandy(candy);
	delete candy;
	map[x][y] = bombcandy;
}

bool Game::checkPop() {
	int pop = 0;

	int x, y;
	

	// ■■
	// ■■ 검사
	for(y=0; y<mapSize - 1; y++) {
		for(x=0; x<mapSize - 1; x++) {
			Candy *c1, *c2, *c3, *c4;
			int t1, t2, t3, t4;

			c1 = map[x][y];
			c2 = map[x + 1][y];
			c3 = map[x][y + 1];
			c4 = map[x + 1][y + 1];

			t1 = c1->getType();
			t2 = c2->getType();
			t3 = c3->getType();
			t4 = c4->getType();
			
			if(t1 == t2 && t2 == t3 && t3 == t4) {
				this->pop(c1, x, y);
				this->pop(c2, x + 1, y);
				this->pop(c3, x + 2, y);
				this->pop(c4, x + 3, y);
				replaceToBombCandy(x, y);
				addScore(15 * 4);
				return true;
			}
		}
	}

	// ■■■■ 검사
	for(y=0; y<mapSize; y++) {
		for(x=0; x<mapSize - 3; x++) {
			Candy *c1, *c2, *c3, *c4;
			int t1, t2, t3, t4;

			c1 = map[x][y];
			c2 = map[x + 1][y];
			c3 = map[x + 2][y];
			c4 = map[x + 3][y];

			t1 = c1->getType();
			t2 = c2->getType();
			t3 = c3->getType();
			t4 = c4->getType();
			
			if(t1 == t2 && t2 == t3 && t3 == t4) {
				this->pop(c1, x, y);
				this->pop(c2, x + 1, y);
				this->pop(c3, x + 2, y);
				this->pop(c4, x + 3, y);
				replaceToBombCandy(x, y);
				addScore(15 * 4);
				return true;
			}
		}
	}

	// ■■■■ 세로 검사
	for(y=0; y<mapSize - 3; y++) {
		for(x=0; x<mapSize; x++) {
			Candy *c1, *c2, *c3, *c4;
			int t1, t2, t3, t4;

			c1 = map[x][y];
			c2 = map[x][y + 1];
			c3 = map[x][y + 2];
			c4 = map[x][y + 3];

			t1 = c1->getType();
			t2 = c2->getType();
			t3 = c3->getType();
			t4 = c4->getType();
			
			if(t1 == t2 && t2 == t3 && t3 == t4) {
				this->pop(c1, x, y);
				this->pop(c2, x, y + 1);
				this->pop(c3, x, y + 2);
				this->pop(c4, x, y + 3);
				replaceToBombCandy(x, y);
				addScore(15 * 4);
				return true;
			}
		}
	}

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
				this->pop(c1, x, y);
				this->pop(c2, x + 1, y);
				this->pop(c3, x + 2, y);
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
				this->pop(c1, x, y);
				this->pop(c2, x, y + 1);
				this->pop(c3, x, y + 2);
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