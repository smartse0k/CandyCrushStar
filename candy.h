#pragma once

class Candy {
	int type;
	int select;
	int pop;
public:
	Candy();
	Candy(int);
	int getType();
	void setType(int);
	int getSelect();
	void setSelect(int);
	virtual void drawCandy(bool);
	int getPop();
	virtual void setPop();
	void changeCandyAttribute(int);
	virtual int getCandyAttribute();
};

class BombCandy : public Candy {
public:
	BombCandy(Candy *);
	virtual void drawCandy(bool);
	virtual int getCandyAttribute();
}

enum CANDYTYPE {
	CANDY_RECT = 0,
	CANDY_CIRCLE,
	CANDY_STAR,
	CANDY_DIAMOND,
	CANDY_HEART,
	CANDY_NUM,
};

enum SELECTTYPE {
	NOT_SELECTED = 0,
	SELECTED,
};

enum CANDYATTR {
	CANDY_DEFAULT = 0,
	CANDY_BOMB,
};