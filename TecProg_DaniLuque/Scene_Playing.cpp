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
	//inicializar variables
	foodcounter = 1;
	score = 0;

	//inicializar el mapa
	cellData = new Cell*[m_leveldata.rows];
	for (int i = 0; i < m_leveldata.rows; ++i) cellData[i] = new Cell[m_leveldata.columns];
	//srand(unsigned(time(nullptr)));
	for (int i = 0; i < m_leveldata.rows; ++i) {
		for (int j = 0; j <m_leveldata.columns; ++j) {
			cellData[i][j].transform = { j * (CELL_WIDTH + 2) + ((W.GetWidth() - CELL_WIDTH*m_leveldata.columns) >> 1),
				i * (CELL_HEIGHT + 2) + ((W.GetHeight() - CELL_HEIGHT*m_leveldata.rows) >> 1),
				CELL_WIDTH, CELL_HEIGHT };
			if (i == 0 || j == 0 || i == (m_leveldata.rows - 1) || j == (m_leveldata.columns - 1)) {
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
	//inicializar comida
	f_food = new Food(m_leveldata, foodcounter);

}

void GamePlaying::OnExit(void) {
	delete s_snake;
	delete f_food;

	Println("LEAVING_GAME");
	//	IM.SetQuit();
}

void GamePlaying::Update(void) {

	if (IM.IsKeyUp<KEY_BUTTON_ESCAPE>()) {
		Println("GOING BACK");
		SM.SetCurScene <DifSelector>();
	}
	if (IM.IsKeyUp<'s'>()) {
		Println("----------------GAMEDATA-----------\n", "Score: ", s_snake->GetScore(), "\n",
			"Lives: ", s_snake->GetNumLives());
	}
	if (IM.IsKeyUp<'z'>()) {
		Println("----------------RESTARTING LEVEL-----------\n");
		RestartLevel();
	}
	

	//update del snake (inputs i tal)
	s_snake->Update();
	
	//Comprobar si la serpiente sigue viva
	if (s_snake->GetDead()) { //take out 1 live
		RestartLevel();
	}

	//check if snake eats food
	if (s_snake->GetPosition().x == f_food->GetPosition().x && s_snake->GetPosition().y == f_food->GetPosition().y) {
		s_snake->SetScore(score += f_food->GetValue());
		foodcounter++;
		f_food->Spawn(*s_snake, foodcounter);
		
	}

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

	//pinta la comida en el mapa
	cellData[f_food->GetPosition().x][f_food->GetPosition().y].objectID = ObjectID::FOOD_APPLE;

	//imprime el contenido de la matriz
	for (int i = 0; i < m_leveldata.rows; ++i) for (int j = 0; j < m_leveldata.columns; ++j) cellData[i][j].Draw();

}

void GamePlaying::RestartLevel(void) {
	if (s_snake->GetNumLives() > 0) {
		//erase drawn sprites
		for (int i = 0; i < m_leveldata.rows; ++i) {
			for (int j = 0; j < m_leveldata.columns; ++j) {
				if (i == 0 || j == 0 || i == (m_leveldata.rows - 1) || j == (m_leveldata.columns - 1)) {
					cellData[i][j].objectID = ObjectID::CELL_WALL;
				}
				else {
					cellData[i][j].objectID = ObjectID::CELL_EMPTY;
				}
			}
		}
		/*cellData[f_food->GetPosition().x][f_food->GetPosition().y].objectID = ObjectID::CELL_EMPTY;
		cellData[s_snake->GetLastPosition().x][s_snake->GetLastPosition().y].objectID = ObjectID::CELL_EMPTY;*/

		//restore initial parameters	
		s_snake->SetScore(0);
		s_snake->SetDirection(RIGHT);
		s_snake->SetPosition({ 5,5 });
		s_snake->SetLastPosition({ 4,4 });

		//restore initial parameters
		foodcounter = 1;
		score = 0;
		s_snake->SetDead(false);
		//aqui va velocidad inicial snake
	}
	else { //snake is dead
		SM.SetCurScene <DifSelector>();
	}
}