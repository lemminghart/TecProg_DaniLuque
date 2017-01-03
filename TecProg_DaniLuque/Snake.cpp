#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "GameMenu.hh"
#include "Snake.h"
#pragma region TODO



using namespace Logger;

#define CELL_WIDTH 80
#define CELL_HEIGHT 80

Snake::Snake(void) {
}

Snake::~Snake(void) {
}


void Snake::Update(void) {
	static MouseCoords mouseCoords(0, 0);

	if (IM.IsKeyHold<'l'>()) Println("SNAKE VIVE!");

}

void Snake::Draw(void) {
	


}
