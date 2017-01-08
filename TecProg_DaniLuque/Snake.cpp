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
	s_score = 0;

	s_direction = RIGHT;
	s_position = { 5,5 };
	s_lastPosition = { 4,4 };
	
}

Snake::~Snake(void) {
}


void Snake::Update(void) {
	//static MouseCoords mouseCoords(0, 0);

	if (IM.IsKeyHold<'l'>()) Println("SNAKE VIVE!");

	if (IM.IsKeyUp<KEY_BUTTON_DOWN>()) {
		s_lastDirection = s_direction;
		s_direction = DOWN;
		Go();
	}
	if (IM.IsKeyUp<KEY_BUTTON_UP>()) {
		s_lastDirection = s_direction;
		s_direction = UP;
		Go();
	}
	if (IM.IsKeyUp<KEY_BUTTON_LEFT>()){
		s_lastDirection = s_direction;
		s_direction = LEFT;
		Go();
	}
	if (IM.IsKeyUp<KEY_BUTTON_RIGHT>()){
		s_lastDirection = s_direction;
		s_direction = RIGHT;
		Go();
	}
	
	

	//PONER EL GO AQUI PARA QUE AVANCE SOLA (SE TIENE QUE REGULAR ANTES EL FRAMERATE)
	//Go();

}

void Snake::Draw(void) {

	

}

void Snake::Go(void) {
	switch (s_direction) {
	case DOWN:
		if (s_lastDirection == UP) {
			s_direction = s_lastDirection;
			break;
		}
		else if (CheckNeighbours()) {
			s_lastPosition = s_position;
			s_position.x += 1;
			Println("X: ", s_position.x, "Y: ", s_position.y);
		}
		else {
			Println("MUERTE");
			lives -= 1;
			dead = true;
		}
		break;
	case UP:
		if (s_lastDirection == DOWN) {
			s_direction = s_lastDirection;
			break;
		}
		else if (CheckNeighbours()) {
			s_lastPosition = s_position;
			s_position.x -= 1;
			Println("X: ", s_position.x, "Y: ", s_position.y);
		}
		else {
			Println("MUERTE");
			lives -= 1;
			dead = true;
		}
		break;
	case LEFT:
		if (s_lastDirection == RIGHT) {
			s_direction = s_lastDirection;
			break;
		}
		else if (CheckNeighbours()) {
			s_lastPosition = s_position;
			s_position.y -= 1;
			Println("X: ", s_position.x, "Y: ", s_position.y);
		}
		else {
			Println("MUERTE");
			lives -= 1;
			dead = true;
		}
		break;
	case RIGHT:
		if (s_lastDirection == LEFT) {
			s_direction = s_lastDirection;
			break;
		}
		else if (CheckNeighbours()) {
			s_lastPosition = s_position;
			s_position.y += 1;
			Println("X: ", s_position.x, "Y: ", s_position.y);
		}
		else {
			Println("MUERTE");
			lives -= 1;
			dead = true;
		}
		break;
	default:
		Println("---------SWITCH GO FAIL-----------");
		break;
	}
}

bool Snake::CheckNeighbours(void) {
	switch (s_direction) {
	case DOWN:
		if ((s_position.x + 1) > 0 && (s_position.x + 1) < (s_leveldata.rows - 1)) return true;
		else return false;
		break;
	case UP:
		if ((s_position.x - 1) > 0 && (s_position.x - 1) < (s_leveldata.rows - 1)) return true;
		else return false;
		break;
	case LEFT:
		if ((s_position.y - 1) > 0 && (s_position.y - 1) < (s_leveldata.columns - 1)) return true;
		else return false;
		break;
	case RIGHT:
		if ((s_position.y + 1) > 0 && (s_position.y + 1) < (s_leveldata.columns - 1)) return true;
		else return false;
		break;
	default:
		Println("---------SWITCH CHECKNEIGHBOURS FAIL-----------");
		break;
	}
}

//SETTERS

void Snake::SetPosition(Position pos) {
	s_position = pos;
}

void Snake::SetLastPosition(Position pos) {
	s_lastPosition = pos;
}

void Snake::SetDirection(Direction direction) {
	s_direction = direction;
}

void Snake::SetScore(int score) {
	s_score = score;
}

void Snake::SetNumLives(int numLives) {
	lives = numLives;
}

void Snake::SetDead(bool state) {
	dead = state;
}


//GETTERS

Direction Snake::GetDirection() {
	return s_direction;
}

Position Snake::GetPosition() {
	return s_position;
}

Position Snake::GetLastPosition() {
	return s_lastPosition;
}

int Snake::GetScore() {
	return s_score;
}

int Snake::GetNumLives() {
	return lives;
}

bool Snake::GetDead() {
	return dead;
}