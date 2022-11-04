#pragma once
#include "gameNode.h"

class LevelButton;

class LevelSelect : public gameNode
{
	vector<LevelButton *> vLevel;

public:
	LevelSelect();
	~LevelSelect();

	HRESULT init();
	void release();
	void update();
	void render();
};

