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

	s_speed = s_leveldata.VInit;
	lives = 2;
	bodySize = 4;
	s_score = 0;
	_serpiente.resize(bodySize);
	_serpiente[0] = Position{ 5,5 }; //cabeza
	_serpiente[1] = Position{ 5,4 };
	_serpiente[2] = Position{ 5,3 };
	_serpiente[3] = Position{ 5,2 }; //blanco

	_direction = RIGHT;

	percent = 0;
}

Snake::~Snake(void) {
}


void Snake::Update(void) {
	//static MouseCoords mouseCoords(0, 0);

	if (IM.IsKeyUp<KEY_BUTTON_DOWN>() && _lastDirection != UP) {
		_direction = DOWN;
		//Go();
	}
	if (IM.IsKeyUp<KEY_BUTTON_UP>() && _lastDirection != DOWN) {
		_direction = UP;
		//Go();
	}
	if (IM.IsKeyUp<KEY_BUTTON_LEFT>() && _lastDirection != RIGHT){
		_direction = LEFT;
		//Go();
	}
	if (IM.IsKeyUp<KEY_BUTTON_RIGHT>() && _lastDirection != LEFT){
		_direction = RIGHT;
		//Go();
	}
	
		
	//aqui se regula la velocidad de la serpiente
	if (percent > s_speed) {
		Go();
		percent = 0;
		//Println("speed: ", s_speed);
	}
	percent += TM.GetDeltaTime();
}

void Snake::UpdateSpeed() {
	s_speed = s_speed - 0.005;
}

void Snake::DowngradeSpeed() {
	s_speed = s_speed + 0.005;
}

void Snake::Draw(void) {

	


}

//done
void Snake::Go(void) {
	switch (_direction) {
	case DOWN:
		if (CheckNeighbours()) {
			for (int i = (_serpiente.size()-1); i > 0; i--) {
				Println(i, ": - X: ", _serpiente[i].x, "Y: ", _serpiente[i].y);
				_serpiente[i] = _serpiente[i - 1];
				Println(i, ": - X: ", _serpiente[i].x, "Y: ", _serpiente[i].y);
			}
			_serpiente[0].x += 1;
			Println("X: ", _serpiente[0].x, "Y: ", _serpiente[0].y);
		}
		else {
			Println("MUERTE");
			lives -= 1;
			dead = true;
		}
		break;
	case UP:
		if (CheckNeighbours()) {
			for (int i = (_serpiente.size() - 1); i > 0; i--) {
				Println(i, ": - X: ", _serpiente[i].x, "Y: ", _serpiente[i].y);
				_serpiente[i] = _serpiente[i - 1];
				Println(i, ": - X: ", _serpiente[i].x, "Y: ", _serpiente[i].y);
			}
			_serpiente[0].x -= 1;
			
			Println("X: ", _serpiente[0].x, "Y: ", _serpiente[0].y);
		}
		else {
			Println("MUERTE");
			lives -= 1;
			dead = true;
		}
		break;
	case LEFT:
		if (CheckNeighbours()) {
			for (int i = (_serpiente.size() - 1); i > 0; i--) {
				Println(i, ": - X: ", _serpiente[i].x, "Y: ", _serpiente[i].y);
				_serpiente[i] = _serpiente[i - 1];
				Println(i, ": - X: ", _serpiente[i].x, "Y: ", _serpiente[i].y);
			}
			_serpiente[0].y -= 1;
			Println("Cabeza: - X: ", _serpiente[0].x, "Y: ", _serpiente[0].y);
		}
		else {
			Println("MUERTE");
			lives -= 1;
			dead = true;
		}
		break;
	case RIGHT:
		if (CheckNeighbours()) {
			for (int i = (_serpiente.size() - 1); i > 0; i--) {
				Println(i, ": - X: ", _serpiente[i].x, "Y: ", _serpiente[i].y);
				_serpiente[i] = _serpiente[i - 1];
				Println(i, ": - X: ", _serpiente[i].x, "Y: ", _serpiente[i].y);
			}
			_serpiente[0].y += 1;
			Println("X: ", _serpiente[0].x, "Y: ", _serpiente[0].y);
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
	_lastDirection = _direction;
}

//ACTUALIZAR PARA CONTROLAR COLISION CON SU PROPIO CUERPO
bool Snake::CheckNeighbours(void) {
	
	
	switch (_direction) {
	case DOWN:
		if ((_serpiente[0].x + 1) > 0 && (_serpiente[0].x + 1) < (s_leveldata.rows - 1)) {
			for (int i = 1; i < _serpiente.size()-1; i++) {
				if (_serpiente[0].x + 1== _serpiente[i-1].x && _serpiente[0].y == _serpiente[i-1].y) {
					return false;
				}
			}
		return true;
		}
		else return false;
		break;
	case UP:
		if ((_serpiente[0].x - 1) > 0 && (_serpiente[0].x - 1) < (s_leveldata.rows - 1)) {
			for (int i = 1; i < _serpiente.size() - 1; i++) {
				if (_serpiente[0].x - 1== _serpiente[i-1].x && _serpiente[0].y == _serpiente[i-1].y) {
					return false;
				}
			}
			return true;
		}
		else return false;
		break;
	case LEFT:
		if ((_serpiente[0].y - 1) > 0 && (_serpiente[0].y - 1) < (s_leveldata.columns - 1)) {
			for (int i = 1; i < _serpiente.size() - 1; i++) {
				if (_serpiente[0].x == _serpiente[i - 1].x && _serpiente[0].y - 1== _serpiente[i - 1].y) {
					return false;
				}
			
			}
			return true;
		}
		else return false;
		break;
	case RIGHT:
		if ((_serpiente[0].y + 1) > 0 && (_serpiente[0].y + 1) < (s_leveldata.columns - 1)) {
			for (int i = 1; i < _serpiente.size() - 1; i++) {
				if (_serpiente[0].x == _serpiente[i - 1].x && _serpiente[0].y + 1 == _serpiente[i - 1].y) {
					return false;
				}
				
			}
			return true;
		}
		else return false;
		break;
	default:
		Println("---------SWITCH CHECKNEIGHBOURS FAIL-----------");
		break;
	}
}


void Snake::addBody(void) {
	bodySize++;
	_serpiente.resize(bodySize);

}

//SETTERS

void Snake::SetPosition(Position pos) {
	_serpiente[0] = pos;
}

void Snake::SetLastPosition(Position pos) {
	_lastPosition = pos;
}

void Snake::SetDirection(Direction direction) {
	_direction = direction;
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

void Snake::SetBodySize(int size) {
	bodySize = size;
}

void Snake::setGrow(bool _grow) {
	grow = _grow;
}

//GETTERS

Direction Snake::GetDirection(void) {
	return _direction;
}

Position Snake::GetPosition(void) {
	return _serpiente[0];
}

Position Snake::GetLastPosition(void) {
	return _lastPosition;
}

int Snake::GetScore(void) {
	return s_score;
}

int Snake::GetNumLives(void) {
	return lives;
}

bool Snake::GetDead(void) {
	return dead;
}

int Snake::GetBodySize(void) {
	return bodySize;
}

bool Snake::getGrow(void) {
	return grow;
}