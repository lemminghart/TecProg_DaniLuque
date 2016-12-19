#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "GameScene.h"
#pragma region TODO



using namespace Logger;

#define CELL_WIDTH 80
#define CELL_HEIGHT 80

GameScene::GameScene(void) {
	s2_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };
}

GameScene::~GameScene(void) {
}

void GameScene::OnEntry(void) {
	Update();
	
}

void GameScene::OnExit(void) {

}

void GameScene::Update(void) {
	Println("conseguit");
	system("pause");
}

void GameScene::Draw(void) {
	s2_background.Draw();

}
