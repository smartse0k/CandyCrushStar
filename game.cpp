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
	cout << "  C a n d y - C r u s h �� S t a r" << endl;
	cout << endl;

	while(true) {
		cout << "  �� ũ�⸦ �Է��غ����� (5 ~ 10): ";
		cin >> mapSize;

		if(mapSize >= 5 && mapSize <= 10) {
			break;
		}
	}

	cout << endl;
	
	while(true) {
		cout << "  ĵ�� �̵��� ������ �Է��غ����� (5 ~ 99): ";
		cin >> amountMove;

		if(amountMove >= 5 || amountMove <= 99) {
			break;
		}
	}

	cout << endl;

	while(true) {
		cout << "  ������ �ο� ���� �Է��غ����� (1 ~ 10): ";
		cin >> playernum;

		if(playernum >= 1 || playernum <= 10) {
			break;
		}
	}

	cout << endl;

	players = new Player[playernum];
	for(int i=0; i<playernum; i++) {
		char name[100];
		cout << "     " << (i + 1) << "��° �÷��̾��� �̸��� �Է��غ�����: ";
		cin >> name;
		//cout << "�Էµ�: " << name << endl;
		players[i].setName(name);
	}

	/*
	for(int i=0; i<playernum; i++) {
		cout << "�÷��̾�" << (i+1) << ": " << players[i].getName() << endl;
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
		cout << "  �÷��̾� '" << players[i].getName() << "'�� ���ʰ� �������" << endl;
		while(true) {
			cout << "    ��� �Ϸ��� 1�� �Է��ϼ���: ";
			int i;
			cin >> i;
			if(i == 1) {
				break;
			}
		}
	}

	system("cls");
	cout << endl;
	cout << "  C a n d y - C r u s h �� S t a r" << endl;
	cout << endl;
	cout << "  ����ǥ" << endl;
	for(int i=0; i<playernum; i++) {
		cout << "    " << players[i].getName() << " => " << players[i].getScore() << "��" << endl;
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
	cout << "  C a n d y - C r u s h �� S t a r" << endl;
	cout << endl;
	cout << "  �ְ����� => " << bestScore << endl;
	cout << "  �������� => " << score << endl;
	cout << "  �÷��̾� => " << players[currentPlayer].getName() << endl;
	cout << "  ����ȸ�� => " << leftAmountMove << endl;
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
			cout << "  [ĵ�� ���� ���] ����Ű: Ŀ�� �̵� / �����̽���: ĵ�� ����";
		} else {
			cout << "  [ĵ�� �̵� ���] ����Ű: ���õ� ĵ�� �̵� / �����̽���: ĵ�� ���� ����";
		}

		int key = _getch();
		switch(key) {
		case 72: // ��
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
		case 80: // �Ʒ�
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
		case 75: // ����
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
		case 77: // ������
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

void Game::pop(Candy *candy, int x, int y) {
	int candyAttribute = candy->getCandyAttribute();

	switch(candyAttribute) {
	case CANDY_DEFAULT:
		// x
		break;
	case CANDY_BOMB:
		int testX = 0, testY = 0;
		if(x > 0) { // ��
			map[x - 1][y]->setPop();
			testX++;
		}
		if(y > 0) { // ��
			map[x][y - 1]->setPop();
			testY++;
		}
		if(x < mapSize - 1) { // ��
			map[x + 1][y]->setPop();
			testX++;
		}
		if(y < mapSize - 1) { // ��
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
	

	// ���
	// ��� �˻�
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

	// ����� �˻�
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

	// ����� ���� �˻�
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
				this->pop(c1, x, y);
				this->pop(c2, x + 1, y);
				this->pop(c3, x + 2, y);
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