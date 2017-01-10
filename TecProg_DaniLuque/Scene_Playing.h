#pragma once
#include "Scene.hh"
#include "Snake.h"
#include "Food.h"
#include "GameMenu.hh"


// GameScene class with the selection mode
class GamePlaying : public Scene {
public:
	explicit GamePlaying();
	~GamePlaying() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;

	void RestartLevel(void);

	//getters
	static int GetScore(void);

	LevelData m_leveldata;
	Snake *s_snake;
	Food *f_food;

	

private:
	Sprite m_background;

	int foodcounter;
	int foodIncrement;
	int foodBase;
	static int score;
	int nivel;
	int incrNivel;
	int time;
	float percent;

	
	struct Cell : public Sprite { Sprite content; } **cellData; // Cell structure to store its position, its texture and its content (wether is empty or not)

	Position food_pos;

	inline ObjectID &ContentID(int i, int j) const { return cellData[i][j].content.objectID; }
	inline Transform &ContentTransform(int i, int j) const { return cellData[i][j].content.transform; }
};