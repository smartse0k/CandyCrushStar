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
	void drawCandy();
	virtual void setPop();
};

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
