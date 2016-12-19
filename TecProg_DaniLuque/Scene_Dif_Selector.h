#pragma once
#include "Grid.hh"
#include "Scene.hh"
#include "GameScene.h"

// GameScene class with the selection mode
class DifSelector : public Scene {
public:
	explicit DifSelector();
	~DifSelector() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	//Grid m_grid;
	Sprite m_background;
	int m_score{ 0 };
};