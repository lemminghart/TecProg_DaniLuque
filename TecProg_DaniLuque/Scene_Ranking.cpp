#include "Scene_Ranking.h"
#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "GameMenu.hh"

using namespace Logger;

Ranking::Ranking() {
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };
}
Ranking::~Ranking() {

}

void Ranking::OnEntry(void) {

}
void Ranking::OnExit(void) {
	Println("Leaving Ranking_scene");
}
void Ranking::Update(void){
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