#pragma once

class Player {
	char *name;
	int score;
public:
	void setName(char *name);
	char *getName();
	void setScore(int score);
	int getScore();
};