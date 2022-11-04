#pragma once
#include "gameNode.h"

class Block;
class Ball;
class Bullet;
class Image;

enum ST_DIR
{
	RIGHT,
	LEFT,
};

class PlayGame : public gameNode
{
private:
	RECT			rcClient;

	/////////////////////////////////////////
	// 게임 정보
	/////////////////////////////////////////

	// 블럭
	Block			block[MAX_X][MAX_Y];

	// 플레이어 공
	Ball			playerBall;

	// 총알
	Bullet			bullet[MAXBULLET];


	// 초기화 타이머
	float initTimer;

	// 스위치
	bool switch_Lightning;
	bool switch_Green;
	bool switch_Orange;
	bool switch_Star;

	bool _isWin;

	/////////////////////////////////////////
	// 디버그
	/////////////////////////////////////////
	float tickCountStart, tickCountEnd;




public:
	PlayGame();
	~PlayGame();

	//=============================================


	//============================================
	virtual HRESULT init();
	virtual void	update();
	virtual void	render();
	virtual void	release();

	void createLevel();
	void checkCollision_PlayerToBlock();
	void checkCollision_PlayerToBullet();
	void checkCollision_BlockToBlock();
	void checkCollision_BulletToBlock();
	void setTempBlock();
	void setTempBlock2();

	Block* findBlock(int _findBoxindex, int _arrIndex = 0);

	void changeSwitch_Lightning()
	{
		if (switch_Lightning)
		{
			switch_Lightning = false;

			for (int x = 0; x < 25; x++)
			{
				for (int y = 0; y < 15; y++)
				{
					if (!block[x][y].isValid())
						continue;

					if (block[x][y].getIndex() == 1501)
						block[x][y].pushBlockBottom();
					else if (block[x][y].getIndex() == 1502)
						block[x][y].pushBlockLeft();
					else if (block[x][y].getIndex() == 1503)
						block[x][y].pushBlockTop();
					else if (block[x][y].getIndex() == 1504)
						block[x][y].pushBlockRight();
					else {}
				}
			}
		}
		else
		{
			switch_Lightning = true;

			for (int x = 0; x < 25; x++)
			{
				for (int y = 0; y < 15; y++)
				{
					if (!block[x][y].isValid())
						continue;

					if (block[x][y].getIndex() == 1501)
						block[x][y].pushBlockTop();
					else if (block[x][y].getIndex() == 1502)
						block[x][y].pushBlockRight();
					else if (block[x][y].getIndex() == 1503)
						block[x][y].pushBlockBottom();
					else if (block[x][y].getIndex() == 1504)
						block[x][y].pushBlockLeft();
					else {}
				}
			}
		}	
	}
	void changeSwitch_Green()
	{
		if (switch_Green)
			switch_Green = false;
		else
			switch_Green = true;
	}
	void changeSwitch_Orange()
	{
		if (switch_Orange)
			switch_Orange = false;
		else
			switch_Orange = true;
	}
	void changeSwitch_Star()
	{
		if (switch_Star)
			switch_Star = false;
		else
			switch_Star = true;
	}

	bool getSwitch_Lightning()
	{
		return switch_Lightning;
	}
	void setSwitch_Lightning(bool _switch)
	{
		switch_Lightning = _switch;
	}

	bool getSwitch_Green()
	{
		return switch_Green;
	}
	void setSwitch_Green(bool _switch)
	{
		switch_Green = _switch;
	}

	bool getSwitch_Orange()
	{
		return switch_Orange;
	}
	void setSwitch_Orange(bool _switch)
	{
		switch_Orange = _switch;
	}

	bool getSwitch_Star()
	{
		return switch_Star;
	}
	void setSwitch_Star(bool _switch)
	{
		switch_Star = _switch;
	}
};

