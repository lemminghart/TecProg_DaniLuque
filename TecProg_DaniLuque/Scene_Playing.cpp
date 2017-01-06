#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "Scene_Playing.h"
#include "Scene_Dif_Selector.h"
#include "GameMenu.hh"
#include "IOManager.hh"
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
			if (i == 0 || j == 0 || i == (m_leveldata.rows-1) || j == (m_leveldata.columns-1)) {
				cellData[i][j].objectID = ObjectID::CELL_WALL;
			}
			else {
				cellData[i][j].objectID = ObjectID::CELL_EMPTY;
			}
			ContentTransform(i, j) = cellData[i][j].transform;
		}
	}

	//inicializar serpiente

	s_snake = new Snake(m_leveldata);


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
	if (IM.IsKeyUp<'s'>()) {
		Println("----------------GAMEDATA-----------\n", "Score: ", s_snake->GetScore());
	}

	

	//update del snake (inputs i tal)
	s_snake->Update();


	//mover: consecuencias (avanza, come fruta, muere)

	//m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };


	//// Test InputManager key methods
	//if (IM.IsKeyHold<'a'>()) Println("a hold");
	//if (IM.IsKeyDown<'0'>()) Println("0 down");
	//if (IM.IsKeyUp<KEY_BUTTON_DOWN>()) Println("down arrow up");
	
}

void GamePlaying::Draw(void) {
	m_background.Draw();
	

	//pinta la cabeza de la serpiente
	cellData[s_snake->GetPosition().x][s_snake->GetPosition().y].objectID = ObjectID::SNAKE_HEAD;

	//limpia la ultima posición de la serpiente
	cellData[s_snake->GetLastPosition().x][s_snake->GetLastPosition().y].objectID = ObjectID::CELL_EMPTY;
	//ContentTransform(s_snake->GetPosition().x, s_snake->GetPosition().y) = cellData[s_snake->GetPosition().x][s_snake->GetPosition().y].transform;

	//imprime el contenido de la matriz
	for (int i = 0; i < m_leveldata.rows; ++i) for (int j = 0; j < m_leveldata.columns; ++j) cellData[i][j].Draw();

}