#pragma once
#include "Scene.hh"
#include "TimeManager.hh"

struct LevelData {
	int rows;
	int columns;
	int time;
	float VInit;
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
	void addBody(void);
	void UpdateSpeed(void);
	void DowngradeSpeed(void);
	//change

	//setters & getters
	void SetPosition(Position pos);
	void SetLastPosition(Position pos);
	void SetLastPosition_saved(Position pos);
	void SetScore(int score);
	void SetNumLives(int numLives);
	void SetBodySize(int bodySize);
	void SetBodySize_saved(int bodySize);
	void SetDirection(Direction direction);
	void SetDirection_saved(Direction direction);
	void SetLastDirection(Direction direction);
	void SetLastDirection_saved(Direction direction);
	void SetDead(bool state);
	void setGrow(bool grow);
	void SetSpeed();

	Position GetPosition(void);
	Position GetLastPosition(void);
	Position GetLastPosition_saved(void);
	int GetScore(void);
	int GetNumLives(void);
	int GetBodySize(void);
	int GetBodySize_saved(void);
	Direction GetDirection(void);
	Direction GetDirection_saved(void);
	Direction GetLastDirection(void);
	Direction GetLastDirection_saved(void);
	bool GetDead(void);
	bool getGrow(void);

	struct S_Cell : public Sprite { Sprite content; } **cellData; // Cell structure to store its position, its texture and its content (wether is empty or not)
	
	std::vector<Position> _serpiente;
	std::vector<Position> _serpiente_saved;
	
private:
	int lives;
	int bodySize;
	int bodySize_saved;
	float s_speed;
	int s_score;
	bool dead;
	bool grow;
	
	
	Direction _direction;
	Direction _lastDirection;
	Position _lastPosition;
	
	Direction _direction_saved;
	Direction _lastDirection_saved;
	Position _lastPosition_saved;

	double percent;


	LevelData s_leveldata;


	inline ObjectID &ContentID(int i, int j) const { return cellData[i][j].content.objectID; }
	inline Transform &ContentTransform(int i, int j) const { return cellData[i][j].content.transform; }
};