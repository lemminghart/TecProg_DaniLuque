#include "Food.h"
#include "Snake.h"
#include "Logger.hh"
#include "Scene_Playing.h"
#include <random>

using namespace Logger;

Food::Food(LevelData &lvldata, int foodNumber, Snake *snake) {
	f_snake = snake;
	
	f_leveldata = lvldata;
	value = foodNumber*100;

	f_position.x = rand() % ((f_leveldata.rows - 2) - 0) + 1;
	f_position.y = rand() % ((f_leveldata.columns - 2) - 0) + 1;
	for (int i = 0; i < f_snake->_serpiente.size(); i++) {
		if (f_position.x == f_snake->_serpiente[i].x && f_position.y == f_snake->_serpiente[i].y) {
			f_position.x = rand() % ((f_leveldata.rows - 2) - 0) + 1;
			f_position.y = rand() % ((f_leveldata.columns - 2) - 0) + 1;
			i = 0;
		}
	}

}

Food::~Food() {
}

void Food::Spawn(int foodnumber) {
	//Random between 2 variables:
	//int randNum = rand()%(max-min + 1) + min; (min & max included)
	//do rand
	f_position.x = rand() % ((f_leveldata.rows - 2) - 0) + 1;
	f_position.y = rand() % ((f_leveldata.columns - 2) - 0) + 1;
	for (int i = 0; i < f_snake->_serpiente.size(); i++) {
		if (f_position.x == f_snake->_serpiente[i].x && f_position.y== f_snake->_serpiente[i].y) {
			f_position.x = rand() % ((f_leveldata.rows - 2) - 0) + 1;
			f_position.y = rand() % ((f_leveldata.columns - 2) - 0) + 1;
			i = 0;
		}
	}
	

	value = foodnumber * 100;
}

//void Food::Spawn(LevelData m_leveldata, int foodnumber, Cell &cellData) {
//	//Random between 2 variables:
//	//int randNum = rand()%(max-min + 1) + min; (min & max included)
//	
//	for (int i = 0; i < m_leveldata.rows; ++i) {
//		for (int j = 0; j < m_leveldata.columns; ++j) {
//			if(cellData[i][j].objectID == 
//		}
//	}
//	value = foodnumber * 100;
//}

void Food::SetPosition(Position pos) {
	f_position = pos;
}

Position Food::GetPosition() {
	return f_position;
}

int Food::GetValue() {
	return value;
}