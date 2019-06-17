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
		cout << "£ª";
		return;
	}

	switch(type) {
	case CANDY_RECT:
		if(select == NOT_SELECTED && !selected) cout << "¡à";
		else cout << "¡á";
		break;
	case CANDY_CIRCLE:
		if(select == NOT_SELECTED && !selected) cout << "¡Û";
		else cout << "¡Ü";
		break;
	case CANDY_STAR:
		if(select == NOT_SELECTED && !selected) cout << "¡Ù";
		else cout << "¡Ú";
		break;
	case CANDY_DIAMOND:
		if(select == NOT_SELECTED && !selected) cout << "¡Þ";
		else cout << "¡ß";
		break;
	case CANDY_HEART:
		if(select == NOT_SELECTED && !selected) cout << "¢½";
		else cout << "¢¾";
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