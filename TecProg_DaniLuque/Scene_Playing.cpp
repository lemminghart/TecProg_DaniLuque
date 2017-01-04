#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "Scene_Playing.h"
#include "Scene_Dif_Selector.h"
#include "GameMenu.hh"
#include "IOManager.hh"
#include "Snake.h"
#include "TimeManager.hh"
#pragma region TODO



using namespace Logger;

#define CELL_WIDTH 20
#define CELL_HEIGHT 20

GamePlaying::GamePlaying(void) {
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };
}

GamePlaying::~GamePlaying(void) {
}

void GamePlaying::OnEntry(void) {
	switch (DifSelector::gameDifficulty) {
	case EASY:
		std::cout << "CARGANDO NIVEL FACIL" << std::endl;
		m_leveldata = IOManager::LoadLevelData("cfg/Level_Data.xml", EASY, m_leveldata);
		break;
	case MEDIUM:
		std::cout << "CARGANDO NIVEL MEDIO" << std::endl;
		m_leveldata = IOManager::LoadLevelData("cfg/Level_Data.xml", MEDIUM, m_leveldata);
		break;
	case HARD:
		std::cout << "CARGANDO NIVEL DIFICL" << std::endl;
		m_leveldata = IOManager::LoadLevelData("cfg/Level_Data.xml", HARD, m_leveldata);
		break;
	}

	//inicializar el mapa
	cellData = new Cell*[m_leveldata.rows];
	for (int i = 0; i < m_leveldata.rows; ++i) cellData[i] = new Cell[m_leveldata.columns];
	//srand(unsigned(time(nullptr)));
	for (int i = 0; i < m_leveldata.rows; ++i) {
		for (int j = 0; j <m_leveldata.columns; ++j) {
			cellData[i][j].transform = { j * (CELL_WIDTH + 2) + ((W.GetWidth() - CELL_WIDTH*m_leveldata.columns) >> 1),
				i * (CELL_HEIGHT + 2) + ((W.GetHeight() - CELL_HEIGHT*m_leveldata.rows) >> 1),
				CELL_WIDTH, CELL_HEIGHT };
			cellData[i][j].objectID = ObjectID::CELL_EMPTY;
			ContentTransform(i, j) = cellData[i][j].transform;
		}
	}

	//inicializar serpiente
	/*Position pos{ 5,5 };
	Snake go_snake(pos, m_leveldata.VInit);*/

}

void GamePlaying::OnExit(void) {

	Println("LEAVING_GAME");
	//	IM.SetQuit();


}

void GamePlaying::Update(void) {

	if (IM.IsKeyUp<KEY_BUTTON_ESCAPE>()) {
		Println("GOING BACK");
		SM.SetCurScene <DifSelector>();
	}

	

	//comprobar los vecinos de la cabeza de la serpiente

	//mirar si hay cambio de dirección

	//mover: consecuencias (avanza, come fruta, muere)

	//m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };


	// Test InputManager key methods
	if (IM.IsKeyHold<'a'>()) Println("a hold");
	if (IM.IsKeyDown<'0'>()) Println("0 down");
	if (IM.IsKeyUp<KEY_BUTTON_DOWN>()) Println("down arrow up");
	
}

void GamePlaying::Draw(void) {
	m_background.Draw();

	//GUI::DrawTextShaded<FontID::ARIAL>("HERE GOES THE GAME :)",
	//{ W.GetWidth() >> 1, int(W.GetHeight()*.1f), 1, 1 },
	//{ 0, 255, 0 }, { 0, 0, 0 });

	for (int i = 0; i < m_leveldata.rows; ++i) for (int j = 0; j < m_leveldata.columns; ++j) cellData[i][j].Draw();

}