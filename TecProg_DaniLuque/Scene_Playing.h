#pragma once
#include "Scene.hh"
#include "GameScene.h"
#include "Snake.h"

struct LevelData {
	int rows;
	int columns;
	int time;
	int VInit;
	int NumFoodInit;
	int NumFoodIncr;
};

// GameScene class with the selection mode
class GamePlaying : public Scene {
public:
	explicit GamePlaying();
	~GamePlaying() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	LevelData m_leveldata;
	Sprite m_background;
	int m_score{ 0 };
	//Snake go_snake; //go stands for Game Object

	struct Cell : public Sprite { Sprite content; } **cellData; // Cell structure to store its position, its texture and its content (wether is empty or not)
	inline ObjectID &ContentID(int i, int j) const { return cellData[i][j].content.objectID; }
	inline Transform &ContentTransform(int i, int j) const { return cellData[i][j].content.transform; }
};