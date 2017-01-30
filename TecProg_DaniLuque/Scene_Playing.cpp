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
#define SPAWN_TIME 3

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
	saved_level, nivel = 0; //lvl 1
	foodIncrement = m_leveldata.NumFoodIncr;
	foodBase = m_leveldata.NumFoodInit;
	time = m_leveldata.time;
	percent, percent_2 = 0;
	spawn_counter = SPAWN_TIME;
	

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
	f_food = new Food(m_leveldata, foodcounter, s_snake);
}

void GamePlaying::OnExit(void) {
	Println("-------------------------GAME OVER------------------------------");
	Println("SCORE: ", s_snake->GetScore());
	Println("NIVEL ALCANZADO: ", (nivel+1));
	Println("------------------------FELICIDADES!----------------------------");
	delete s_snake;
	delete f_food;
	Println("LEAVING_GAME");
	//	IM.SetQuit();
}

void GamePlaying::Update(void) {
	
	//movimiento de la cabeza
	s_snake->Update();
	
	//set grow to false to later prove if snake has grown
	s_snake->setGrow(false);

	//check if snake eats food
	if (s_snake->GetPosition().x == f_food->GetPosition().x && s_snake->GetPosition().y == f_food->GetPosition().y) {
		std::cout << "EAT FOOD!" << std::endl;
		s_snake->SetScore(score += f_food->GetValue());
		foodcounter++;

		
		//spawneamos nueva comida
		
		/*food_pos.x = rand() % ((m_leveldata.rows - 2) - 0) + 1;
		food_pos.y = rand() % ((m_leveldata.columns - 2) - 0) + 1;
		for (int i = 0; i < s_snake->_serpiente.size(); i++) {
			if (food_pos.x == s_snake->_serpiente[i].x && food_pos.y == s_snake->_serpiente[i].y) {
				food_pos.x = rand() % ((m_leveldata.rows - 2) - 0) + 1;
				food_pos.y = rand() % ((m_leveldata.columns - 2) - 0) + 1;
				i = 0;
			}
		}
		f_food->SetPosition(food_pos);*/
		f_food->Spawn(foodcounter);

		s_snake->UpdateSpeed();
		//hacer crecer la serpiente
		s_snake->addBody();
	}

	//Comprobar si la serpiente sigue viva
	if (s_snake->GetDead()) {
		RestartLevel();
	}
		
	//superar nivel
	if (foodcounter > foodBase) {
		Println("LVL UP!");
		
		nivel++;
		//basic level parameter
		foodcounter = 1;
		foodBase = m_leveldata.NumFoodInit + foodIncrement * nivel;
		time = m_leveldata.time;
		saved_level = nivel;

		//snake parameters
		s_snake->_serpiente_saved = s_snake->_serpiente;
		s_snake->SetBodySize_saved(s_snake->GetBodySize());
		s_snake->SetDirection_saved(s_snake->GetDirection());
		s_snake->SetLastDirection_saved(s_snake->GetLastDirection());
		s_snake->SetLastPosition_saved(s_snake->GetLastPosition());
		Println("Level Saved");
	}

	//Time manager
	//cada 1 segundo entra en el bucle
	if (percent > 1) {
		if (time > 1) {
			time--;
			Println("time: ",time);
		}
		else {
			RestartLevel();
		}
		//Println(percent);
		percent = 0;
	}
	percent += TM.GetDeltaTime();
	
	//KEY INPUTS
	if (IM.IsKeyUp<'n'>()) {
		s_snake->UpdateSpeed();
		Println("more speed");
	}
	if (IM.IsKeyUp<'m'>()) {
		s_snake->DowngradeSpeed();
		Println("Less speed");
	}
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
	if (IM.IsKeyHold<'x'>()) {
		Println("----------------RESPAWNING A FRUIT-----------\n");
		cellData[f_food->GetPosition().x][f_food->GetPosition().y].objectID = ObjectID::CELL_EMPTY;
		f_food->Spawn(foodcounter);
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
	//limpia la ultima posición de la serpiente
	cellData[s_snake->_serpiente[(s_snake->_serpiente.size()-1)].x][s_snake->_serpiente[(s_snake->_serpiente.size()-1)].y].objectID = ObjectID::CELL_EMPTY;
	
	//pinta la cabeza de la serpiente
	cellData[s_snake->_serpiente[0].x][s_snake->_serpiente[0].y].objectID = ObjectID::SNAKE_HEAD;

#pragma endregion

	//pinta la comida en el mapa
	cellData[f_food->GetPosition().x][f_food->GetPosition().y].objectID = ObjectID::FOOD_APPLE;

	
	cellData[0][0].objectID = ObjectID::CELL_WALL;
	//imprime el contenido de la matriz
	for (int i = 0; i < m_leveldata.rows; ++i) for (int j = 0; j < m_leveldata.columns; ++j) cellData[i][j].Draw();

	//time
	GUI::DrawTextBlended<FontID::ARIAL>("Time: ",
	{ int(W.GetWidth()*.2f), int(W.GetHeight()*.1f), 1, 1 },
	{ 255, 255, 255 });
	GUI::DrawTextBlended<FontID::ARIAL>(std::to_string(time),
	{ int(W.GetWidth()*.3f), int(W.GetHeight()*.1f), 1, 1 },
	{ 255, 255, 255 });
	//level
	GUI::DrawTextBlended<FontID::ARIAL>("Level: ",
	{ int(W.GetWidth()*.7f), int(W.GetHeight()*.1f), 1, 1 },
	{ 255, 255, 255 });
	GUI::DrawTextBlended<FontID::ARIAL>(std::to_string(nivel+1),
	{ int(W.GetWidth()*.8f), int(W.GetHeight()*.1f), 1, 1 },
	{ 255, 255, 255 });
	//lives
	GUI::DrawTextBlended<FontID::ARIAL>("Lives: ",
	{ int(W.GetWidth()*.2f), int(W.GetHeight()*.95f), 1, 1 },
	{ 255, 255, 255 });
	GUI::DrawTextBlended<FontID::ARIAL>(std::to_string(s_snake->GetNumLives()),
	{ int(W.GetWidth()*.3f), int(W.GetHeight()*.95f), 1, 1 },
	{ 255, 255, 255 });
	//score
	GUI::DrawTextBlended<FontID::ARIAL>("Score: ",
	{ int(W.GetWidth()*.7f), int(W.GetHeight()*.95f), 1, 1 },
	{ 255, 255, 255 });
	GUI::DrawTextBlended<FontID::ARIAL>(std::to_string(score),
	{ int(W.GetWidth()*.9f), int(W.GetHeight()*.95f), 1, 1 },
	{ 255, 255, 255 });

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

		
		//basic level parameter
		foodcounter = 1;
		foodBase = m_leveldata.NumFoodInit + foodIncrement * nivel;
		time = m_leveldata.time;
		s_snake->SetDead(false);

		if (nivel < 1) {
			//restore initial parameters	
			//s_snake->SetScore(0); //No me parece apropiado
			//reiniciamos cuerpo
			s_snake->SetDirection(RIGHT);
			s_snake->_serpiente[0] = Position{ 5,5 }; //cabeza
			s_snake->_serpiente[1] = Position{ 5,4 };
			s_snake->_serpiente[2] = Position{ 5,3 };
			s_snake->_serpiente[3] = Position{ 5,2 }; //blanco
			s_snake->SetBodySize(4);
			s_snake->_serpiente.resize(4);
			
			//aqui va velocidad inicial snake
			s_snake->SetSpeed();
		}
		else {
			s_snake->_serpiente = s_snake->_serpiente_saved;
			s_snake->SetBodySize(s_snake->GetBodySize_saved());
			s_snake->SetDirection(s_snake->GetDirection_saved());
			s_snake->SetLastDirection(s_snake->GetLastDirection_saved());
			s_snake->SetLastPosition(s_snake->GetLastPosition_saved());
		}

		nivel = saved_level;

	}
	else { //snake is dead
		score = s_snake->GetScore();
		SM.SetCurScene <Ranking>();
	}
}

int GamePlaying::GetScore() {
	return score;
}