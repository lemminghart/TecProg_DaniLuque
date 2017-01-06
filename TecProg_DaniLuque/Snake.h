#pragma once
#include "Scene.hh"
#include "GameScene.h"

struct LevelData {
	int rows;
	int columns;
	int time;
	int VInit;
	int NumFoodInit;
	int NumFoodIncr;
};

struct Position {
	int x;
	int y;
};

enum Direction {UP, DOWN, RIGHT, LEFT};


// GameScene class with the menu
class Snake{
public:
	Snake();
	Snake(LevelData &lvldata);
	~Snake();
	void Update(void);
	void Draw();
	
	void Go(void);
	bool CheckNeighbours(void);

	//setters & getters
	void SetPosition(struct position);
	void SetScore(int score);
	void SetNumLives(int numLives);
	void SetBodySize(int bodySize);
	void SetDirection(Direction direction);

	Position GetPosition(void);
	Position GetLastPosition(void);
	int GetScore(void);
	int GetNumLives(void);
	int GetBodySize(void);
	Direction GetDirection(void);

	struct S_Cell : public Sprite { Sprite content; } **cellData; // Cell structure to store its position, its texture and its content (wether is empty or not)

private:
	Direction s_direction;
	Direction s_lastDirection;
	int lives;
	int bodySize;
	int s_speed;
	int s_score;
	Position position;
	Position lastPosition;

	LevelData s_leveldata;


	inline ObjectID &ContentID(int i, int j) const { return cellData[i][j].content.objectID; }
	inline Transform &ContentTransform(int i, int j) const { return cellData[i][j].content.transform; }
};