#include "Food.h"
#include "Snake.h"
#include "Logger.hh"

using namespace Logger;

Food::Food(LevelData &lvldata, int foodNumber) {
	f_leveldata = lvldata;
	value = foodNumber*100;

	f_position.x = rand() % ((f_leveldata.rows - 1) - 1 + 1) + 1;
	f_position.y = rand() % ((f_leveldata.columns - 1) - 1 + 1) + 1;
	while (f_position.x == 5 && f_position.x == 5) {
		f_position.x = rand() % ((f_leveldata.rows - 1) - 1 + 1) + 1;
		f_position.y = rand() % ((f_leveldata.columns - 1) - 1 + 1) + 1;
	}
}

Food::~Food() {
}

void Food::Spawn(Snake &snake, int foodnumber) {
	f_position.x = rand() % ((f_leveldata.rows - 2) - 1 + 1) + 1;
	f_position.y = rand() % ((f_leveldata.columns - 2) - 1 + 1) + 1;
	while(f_position.x == snake.GetPosition().x && f_position.x == snake.GetPosition().y){
		f_position.x = rand() % ((f_leveldata.rows - 2) - 1 + 1) + 1;
		f_position.y = rand() % ((f_leveldata.columns - 2) - 1 + 1) + 1;
	}
	value = foodnumber * 100;
	Println("---EAT FOOD!---\n");
}


Position Food::GetPosition() {
	return f_position;
}

int Food::GetValue() {
	return value;
}