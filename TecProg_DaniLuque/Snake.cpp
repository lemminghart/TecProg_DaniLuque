#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "GameMenu.hh"
#include "Snake.h"
#include "Scene_Playing.h"
#pragma region TODO



using namespace Logger;

#define CELL_WIDTH 80
#define CELL_HEIGHT 80

Snake::Snake() {

}

Snake::Snake(LevelData &lvldata) {
	s_leveldata = lvldata;
	lives = 3;
	bodySize = 0;

	s_direction = RIGHT;
	position = { 5,5 };
	
}

Snake::~Snake(void) {
}


void Snake::Update(void) {
	//static MouseCoords mouseCoords(0, 0);

	if (IM.IsKeyHold<'l'>()) Println("SNAKE VIVE!");

	if (IM.IsKeyUp<KEY_BUTTON_DOWN>()) {
		s_direction = DOWN;
		Println("SNAKE DOWN");
		Go();
	}
	if (IM.IsKeyUp<KEY_BUTTON_UP>()) {
		s_direction = UP;
		Println("SNAKE UP");
		Go();
	}
	if (IM.IsKeyUp<KEY_BUTTON_LEFT>()){
		s_direction = LEFT;
		Println("SNAKE LEFT");
		Go();
	}
	if (IM.IsKeyUp<KEY_BUTTON_RIGHT>()){
		s_direction = RIGHT;
		Println("SNAKE RIGHT");
		Go();
	}

	

}

void Snake::Draw(void) {

	

}

void Snake::Go(void) {
	switch (s_direction) {
	case DOWN:
		if (CheckNeighbours()) {
			position.x += 1;
		}
		else {
			Println("ALGO NO VA BIEN");
		}
		break;
	case UP:
		if (CheckNeighbours()) {
			position.x -= 1;
		}
		else {
			Println("ALGO NO VA BIEN");
		}
		break;
	case LEFT:
		if (CheckNeighbours()) {
			position.y -= 1;
		}
		else {
			Println("ALGO NO VA BIEN");
		}
		break;
	case RIGHT:
		if (CheckNeighbours()) {
			position.y += 1;
		}
		else {
			Println("ALGO NO VA BIEN");
		}
		break;
	default:
		Println("---------SOMETHING ISN'T GOING WELL-----------");
		break;
	}
}

bool Snake::CheckNeighbours(void) {
	if (position.x >= 1 && position.x <= (s_leveldata.columns - 1) && position.y >= 1 && position.y <= (s_leveldata.rows - 1)) {
		return true; //puede moverse a una posición permitida
	}
	else {
		return false; //se está intentando mover a una posición prohibida
	}
}

//SETTERS

void Snake::SetDirection(Direction direction) {
	s_direction = direction;
}

//GETTERS

Direction Snake::GetDirection() {
	return s_direction;
}

Position Snake::GetPosition() {
	return position;
}