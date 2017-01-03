#pragma once
#include "Scene.hh"
#include "GameScene.h"

struct Position {
	int x;
	int y;
};

// GameScene class with the menu
class Snake{
public:
	Snake();
	~Snake();
	void Update(void);
	void Draw(void);
	//setters & getters
	void SetPosition(struct position);
	void SetScore(int score);
	void SetNumLives(int numLives);
	void SetBodySize(int bodySize);

	Position GetPosition(void);
	int GetScore(void);
	int GetNumLives(void);
	int GetBodySize(void);
private:
	int lives;
	int bodySize;
	int score; //poner aqui o en mapa?
	Position position;
};