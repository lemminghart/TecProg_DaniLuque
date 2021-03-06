#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "Scene_Playing.h"
#include "GameMenu.hh"
#include "IOManager.hh"
#include "TimeManager.hh"
#include "Scene_Ranking.h"
#include "Snake.h"
#pragma region TODO

int GamePlaying::score = 0;

using namespace Logger;

#define CELL_WIDTH 20
#define CELL_HEIGHT 20

GamePlaying::GamePlaying(void) {
	
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };
}

GamePlaying::~GamePlaying(void) {
}

void GamePlaying::OnEntry(void) {
	switch (GameMenu::gameDifficulty) {
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
	
	//movimiento de la cabeza
	s_snake->Update();
	
	//Comprobar si la serpiente sigue viva
	if (s_snake->GetDead()) { //take out 1 live
		RestartLevel();
	}

	//set grow to false to later prove if snake has grown
	s_snake->setGrow(false);

	//check if snake eats food
	if (s_snake->GetPosition().x == f_food->GetPosition().x && s_snake->GetPosition().y == f_food->GetPosition().y) {
		std::cout << "EAT FOOD!" << std::endl;
		s_snake->SetScore(score += f_food->GetValue());
		foodcounter++;
		f_food->Spawn(*s_snake, foodcounter);

		//hacer crecer la serpiente
		s_snake->addBody();
	}
		
	
	//KEY INPUTS
	if (IM.IsKeyUp<'d'>()) {
		Println("----------------HEADDATA-----------\n", "X: ", s_snake->_serpiente[0].x,"\n",
			"Y: ", s_snake->_serpiente[0].y);
	}
	/*if (IM.IsKeyUp<'t'>()) {
		Println("----------------TAILDATA-----------\n", "X: ", s_snake->tail->s_position.x, " ",
			"Y: ", s_snake->tail->s_position.y);
	}*/
	if (IM.IsKeyUp<'s'>()) {
		Println("----------------GAMEDATA-----------\n", "Score: ", s_snake->GetScore(), "\n",
			"Lives: ", s_snake->GetNumLives());
	}
	if (IM.IsKeyUp<'z'>()) {
		Println("----------------RESTARTING LEVEL-----------\n");
		RestartLevel();
	}
	if (IM.IsKeyUp<'x'>()) {
		Println("----------------RESPAWNING A FRUIT-----------\n");
		cellData[f_food->GetPosition().x][f_food->GetPosition().y].objectID = ObjectID::CELL_EMPTY;
		f_food->Spawn(*s_snake, foodcounter);
	}
	if (IM.IsKeyUp<'k'>()) {
		Println("---------COMMANDS:---------\n", "- Z to restart level\n", "- S to print gameData\n", "- X reposition the fruit\n", "- ESC to go back\n");
	}
	if (IM.IsKeyUp<KEY_BUTTON_ESCAPE>()) {
		Println("GOING BACK");
		SM.SetCurScene <GameMenu>();
	}
}

void GamePlaying::Draw(void) {
	m_background.Draw();
	
#pragma region SNAKE

	//pinta el cuerpo de la serpiente
	for (int i = 1; i < s_snake->_serpiente.size()-1; i++) {
		cellData[s_snake->_serpiente[i].x][s_snake->_serpiente[i].y].objectID = ObjectID::SNAKE_BODY;
	}

	int lol = (s_snake->_serpiente.size() - 1);
	//limpia la ultima posici�n de la serpiente
	cellData[s_snake->_serpiente[(s_snake->_serpiente.size()-1)].x][s_snake->_serpiente[(s_snake->_serpiente.size()-1)].y].objectID = ObjectID::CELL_EMPTY;
	
	//pinta la cabeza de la serpiente
	cellData[s_snake->_serpiente[0].x][s_snake->_serpiente[0].y].objectID = ObjectID::SNAKE_HEAD;

#pragma endregion

	//pinta la comida en el mapa
	cellData[f_food->GetPosition().x][f_food->GetPosition().y].objectID = ObjectID::FOOD_APPLE;

	

	//imprime el contenido de la matriz
	for (int i = 0; i < m_leveldata.rows; ++i) for (int j = 0; j < m_leveldata.columns; ++j) cellData[i][j].Draw();

}

void GamePlaying::RestartLevel(void) {
	if (s_snake->GetNumLives() > 0) {
		std::cout << "RESTART LEVEL!" << std::endl;
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
		score = s_snake->GetScore();
		SM.SetCurScene <Ranking>();
	}
}

int GamePlaying::GetScore() {
	return score;
}