#include <iostream>
#include "candy.h"

using namespace std;

Candy::Candy() {
	setType(rand() % CANDY_NUM);
	setSelect(NOT_SELECTED);
	pop = 0;
}

Candy::Candy(int type) {
	setType(type);
	setSelect(NOT_SELECTED);
	pop = 0;
}

void Candy::drawCandy(bool selected) {
	if(pop == 1) {
		cout << "��";
		return;
	}

	switch(type) {
	case CANDY_RECT:
		if(select == NOT_SELECTED && !selected) cout << "��";
		else cout << "��";
		break;
	case CANDY_CIRCLE:
		if(select == NOT_SELECTED && !selected) cout << "��";
		else cout << "��";
		break;
	case CANDY_STAR:
		if(select == NOT_SELECTED && !selected) cout << "��";
		else cout << "��";
		break;
	case CANDY_DIAMOND:
		if(select == NOT_SELECTED && !selected) cout << "��";
		else cout << "��";
		break;
	case CANDY_HEART:
		if(select == NOT_SELECTED && !selected) cout << "��";
		else cout << "��";
		break;
	default:
		cout << "?";
		break;
	}
}

void BombCandy::drawCandy(bool selected) {
	if(getPop() == 1) {
		cout << "��";
		return;
	}

	switch(getType()) {
	case CANDY_RECT:
		if(getSelect() == NOT_SELECTED && !selected) cout << "��";
		else cout << "��";
		break;
	case CANDY_CIRCLE:
		if(getSelect() == NOT_SELECTED && !selected) cout << "��";
		else cout << "��";
		break;
	case CANDY_STAR:
		if(getSelect() == NOT_SELECTED && !selected) cout << "��";
		else cout << "��";
		break;
	case CANDY_DIAMOND:
		if(getSelect() == NOT_SELECTED && !selected) cout << "��";
		else cout << "��";
		break;
	case CANDY_HEART:
		if(getSelect() == NOT_SELECTED && !selected) cout << "��";
		else cout << "��";
		break;
	default:
		cout << "?";
		break;
	}
}

int Candy::getType() {
	return type;
}

void Candy::setType(int type) {
	this->type = type;
}

int Candy::getSelect() {
	return select;
}

void Candy::setSelect(int select) {
	this->select = select;
}

void Candy::setPop() {
	this->pop = 1;
}

int Candy::getPop() {
	return pop;
}

int Candy::getCandyAttribute() {
	return CANDY_DEFAULT;
}

int BombCandy::getCandyAttribute() {
	return CANDY_BOMB;
}

BombCandy::BombCandy(Candy *candy) {
	this->setSelect(candy->getSelect());
	this->setType(candy->getType());
}