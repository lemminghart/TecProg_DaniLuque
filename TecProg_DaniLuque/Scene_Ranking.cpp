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

	switch (GameMenu::gameDifficulty) {
	case EASY:
		std::cout << "ABRIENDO RANKING_EASY" << std::endl;
		IOManager::SetScores("Ranking_EASY.bin", 1);
		break;
	case MEDIUM:
		std::cout << "ABRIENDO RANKING_MEDIUM" << std::endl;
		IOManager::SetScores("Ranking_MEDIUM.bin", 1);
		break;
	case HARD:
		std::cout << "ABRIENDO RANKING_HARD" << std::endl;
		IOManager::SetScores("Ranking_HARD.bin", 1);
		break;
	}
	
}
void Ranking::OnExit(void) {
	Println("Leaving Ranking_scene");
}
void Ranking::Update(void){
	if (IM.IsKeyUp<'s'>()) {
		Println("----------------GAMEDATA-----------\n", "Score: ", score, "\n");
	
	}
	if (IM.IsKeyUp<KEY_BUTTON_ESCAPE>()) {
		Println("GOING BACK");
		SM.SetCurScene <GameMenu>();
	}
}
void Ranking::Draw(void) {
	m_background.Draw();

	GUI::DrawTextBlended<FontID::ARIAL>("RANKING SCENE",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.2f), 1, 1 },
	{ 115, 0, 180 });
}