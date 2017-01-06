#pragma once
#include "Snake.h"

class Food {
public:
	Food(LevelData &lvldata, int foodNumber);
	~Food();
	void Spawn(Snake &snake, int foodnumber);

	//setters & getters
	Position GetPosition(void);
	int GetValue(void);

private:
	LevelData f_leveldata;
	Position f_position;
	int value;
};