#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "Scene_Playing.h"
#include "Scene_Dif_Selector.h"
#include "GameMenu.hh"
#include "IOManager.hh"
#include "Snake.h"
#pragma region TODO



using namespace Logger;

#define CELL_WIDTH 80
#define CELL_HEIGHT 80

GamePlaying::GamePlaying(void) {
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };
}

GamePlaying::~GamePlaying(void) {
}

void GamePlaying::OnEntry(void) {
	switch (DifSelector::gameDifficulty) {
	case EASY:
		std::cout << "CARGANDO NIVEL FACIL" << std::endl;
		IOManager::LoadLevelData("cfg/Level_Data.xml", EASY);
		break;
	case MEDIUM:
		std::cout << "CARGANDO NIVEL MEDIO" << std::endl;
		IOManager::LoadLevelData("cfg/Level_Data.xml", MEDIUM);
		break;
	case HARD:
		std::cout << "CARGANDO NIVEL DIFICL" << std::endl;
		IOManager::LoadLevelData("cfg/Level_Data.xml", HARD);
		break;
	}
}

void GamePlaying::OnExit(void) {

	Println("LEAVING_GAME");
	//	IM.SetQuit();


}

void GamePlaying::Update(void) {
	static MouseCoords mouseCoords(0, 0);
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		Println("===============");
		Println("mxp: ", mouseCoords);
		mouseCoords = IM.GetMouseCoords();
	}
	else if (IM.IsMouseUp<MOUSE_BUTTON_LEFT>()) {
		Println("mxn: ", IM.GetMouseCoords());


	}

	// Test InputManager key methods
	if (IM.IsKeyHold<'a'>()) Println("a hold");
	if (IM.IsKeyDown<'0'>()) Println("0 down");
	if (IM.IsKeyUp<KEY_BUTTON_DOWN>()) Println("down arrow up");
	if (IM.IsKeyUp<KEY_BUTTON_ESCAPE>()) {
		Println("GOING BACK");
		SM.SetCurScene <DifSelector>();
	}
	
}

void GamePlaying::Draw(void) {
	m_background.Draw();

	GUI::DrawTextShaded<FontID::ARIAL>("HERE GOES THE GAME :)",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.1f), 1, 1 },
	{ 0, 255, 0 }, { 0, 0, 0 });

	//GUI::DrawTextBlended<FontID::ARIAL>("EASY",
	//{ W.GetWidth() >> 1, int(W.GetHeight()*.2f), 1, 1 },
	//{ 115, 0, 180 });
	//GUI::DrawTextBlended<FontID::ARIAL>("MEDIUM",
	//{ W.GetWidth() >> 1, int(W.GetHeight()*.4f), 1, 1 },
	//{ 115, 0, 180 });
	//GUI::DrawTextBlended<FontID::ARIAL>("HARD",
	//{ W.GetWidth() >> 1, int(W.GetHeight()*.6f), 1, 1 },
	//{ 115, 0, 180 });

	//GUI::DrawTextBlended<FontID::ARIAL>("BACK",
	//{ W.GetWidth() >> 1, int(W.GetHeight()*.8f), 1, 1 },
	//{ 255, 0, 0 });
}