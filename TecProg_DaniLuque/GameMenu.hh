/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#pragma once
#include "Scene.hh"

static enum GameDifficulty {
	EASY = 1,
	MEDIUM = 2,
	HARD = 3
} DF;

// GameScene class with the menu
class GameMenu : public Scene {
public:
	explicit GameMenu();
	~GameMenu() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;

	int *gameDifficulty;

private:
	//Grid m_grid;
	bool selector;
	Sprite m_background;
	int m_score{ 0 };
};