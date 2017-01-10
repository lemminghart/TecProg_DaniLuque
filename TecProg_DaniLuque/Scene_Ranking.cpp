#include "Scene_Ranking.h"
#include "Scene_Playing.h"
#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "GameMenu.hh"
#include "IOManager.hh"
#include "Snake.h"

using namespace Logger;

Ranking::Ranking() {
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };
}
Ranking::~Ranking() {

}

void Ranking::OnEntry(void) {
	score = GamePlaying::GetScore();

//	IOManager::ManageRanking(GameMenu::gameDifficulty, score);
	
}
void Ranking::OnExit(void) {
	Println("Leaving Ranking_scene");
}
void Ranking::Update(void){
	if (IM.IsKeyUp<'s'>()) {
		Println("----------------GAMEDATA-----------\n", "Score: ", score, "\n");
	
	}
	if (IM.IsKeyUp<'a'>()) {
		Println("----------------Scores-----------\n");

	}
	if (IM.IsKeyUp<KEY_BUTTON_ESCAPE>()) {
		Println("GOING BACK");
		SM.SetCurScene <GameMenu>();
	}
	if (IM.IsKeyUp<'k'>()) {
		Println("---------COMMANDS:---------\n", "- A to print scores\n", "- S to print gameData\n", "- ESC to go back\n");

	}
}
void Ranking::Draw(void) {
	m_background.Draw();

	GUI::DrawTextBlended<FontID::ARIAL>("RANKING SCENE",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.2f), 1, 1 },
	{ 115, 0, 180 });
}