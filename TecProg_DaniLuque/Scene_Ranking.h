#pragma once
#include "Scene.hh"
#include "Scene_playing.h"

// GameScene class with the selection mode
class Ranking : public Scene {
public:
	explicit Ranking();
	~Ranking() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:
	Sprite m_background;
	int score;
	struct Cell : public Sprite { Sprite content; } **cellData; // Cell structure to store its position, its texture and its content (wether is empty or not)
	inline ObjectID &ContentID(int i, int j) const { return cellData[i][j].content.objectID; }
	inline Transform &ContentTransform(int i, int j) const { return cellData[i][j].content.transform; }
};