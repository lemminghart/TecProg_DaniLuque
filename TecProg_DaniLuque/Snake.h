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
	Snake(Position pos, int speed);
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

	struct S_Cell : public Sprite { Sprite content; } **cellData; // Cell structure to store its position, its texture and its content (wether is empty or not)
private:
	int lives;
	int bodySize;
	int s_speed;
	Position position;
};