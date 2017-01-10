#pragma once
#include "Snake.h"

class Food {
public:
	Food(LevelData &lvldata, int foodNumber, Snake *snake);
	~Food();
	void Spawn(int foodnumber);
//	void Spawn(Snake &snake, int foodnumber, Cell &cellData);

	//setters & getters
	Position GetPosition(void);
	int GetValue(void);

	void SetPosition(Position pos);

private:
	Snake *f_snake;
	LevelData f_leveldata;
	Position f_position;
	int value;
};