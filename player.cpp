#include <string.h>
#include "player.h"

void Player::setName(char *name) {
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

char *Player::getName() {
	return name;
}

void Player::setScore(int score) {
	this->score = score;
}

int Player::getScore() {
	return score;
}