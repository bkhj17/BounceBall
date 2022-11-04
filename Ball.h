#pragma once
#include "BounceBallHeader.h"

#define JUMPPOWER 6.6
#define MAXINPUTSPEED 3.5

class PlayGame;

enum Stat
{
	dead,
	idle,
	moving,
	flying,
	climbing,
	rouletteMode,
	rouletteMode4,
	rouletteMode8,
};

enum ItemStat
{
	none,
	jumpWide,
	jumpHigh,
	warp,
	transparency,
	shadow,
	roulette,
	fly,
};

class Ball
{
private:
	float startX, startY;
	float x, y, radius;
	float Xspeed, Yspeed;
	float XAxis;
	float Xdistance, Ydistance;
	float shadowX, shadowY;

	int stat;
	int itemStat;

	bool visible;
	bool inputLock;

	Block* tempBlock;
	float tempTime;

	float rouletteAngle;

	PlayGame* playGame;

public:
	Ball();
	~Ball();

	void init(int _x, int _y);

	void update();
	void render(HDC _hdc);

	void collision(Block* _block, int _collisionface = 0);
	void collisionToBullet(Bullet* _bullet, int _collisionface = 0);

	void collisionTop();
	void collisionLeft();
	void collisionRight();
	void collisionBottom();

	void die();

	void setX(float _x)
	{
		x = _x;
	}

	float getX()
	{ 
		return x;
	}

	void setY(float _y)
	{
		y = _y; 
	}

	float getY()
	{
		return y;
	}

	void setRadius(float _radius)
	{
		radius = _radius;
	}

	float getRadius()
	{
		return radius;
	}

	void setYspeed(float _Yspeed)
	{
		Yspeed = _Yspeed;
	}

	float getGravity()
	{
		return Yspeed;
	}

	Block* getTempBlock()
	{
		return tempBlock;
	}

	void setTempBlock(Block* _block)
	{
		tempBlock = _block;
	}

	bool getVisible()
	{
		return visible;
	}

	void setVisible(bool _visible)
	{
		visible = _visible;
	}

	int getStat()
	{
		return stat;
	}

	void setPlayGame(PlayGame* _playGame)
	{
		playGame = _playGame;
	}
};

