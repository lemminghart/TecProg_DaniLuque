#pragma once
#include "Scene.hh"
#include "GameScene.h"

// GameScene class with the menu
class Map : Scene{
public:
	explicit Map();
	~Map() override;
	void Update(void) override;
	void Draw(void) override;
private:
	//Grid m_grid;
	Sprite m_background;
	int rows;
	int cols;
};