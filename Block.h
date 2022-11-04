#pragma once
#define MAXBULLET 500

class Ball;
class Bullet;
class PlayGame;

enum Stat_Block
{
	stop,
	move,
	on,
	off,
	tempOff,
	tempOn,
	redBlock,
	blueBlock,
};

class Block
{
private:
	int index;
	int frameX;
	int frameY;
	bool  aniPlay;
	HBRUSH Brush;
	HBRUSH oBrush;

	RECT rect;
	float x, y;
	float startX, startY;
	float Xspeed, Yspeed;
	float width, height;
	int stat;

	bool  valid;
	bool  isRender;
	bool  isCollision_PlayerToBlock;
	bool  isCollision_BlockToBlock;
	bool  isCollision_BulletToBlock;

	bool  useBullet;
	bool  useUpdate;

	bool overlaped;
	bool loop;

	bool canMoveTop;
	bool canMoveLeft;
	bool canMoveRight;
	bool canMoveBottom;

	Block* tempBlock;
	Block* tempBlock2;
	Bullet* bullet[MAXBULLET];
	int bulletCount;

	float currentTimer, maxTimer;

	PlayGame* playgame;
	Ball* playerBall;

public:
	Block();
	~Block();

	void init(int _index, bool _valid = true);
	void init(Bullet * _bullet, int i);
	void update();
	void render(HDC _hdc);
	void collision(Block* _otherBlock, int _collisionface = 0);
	void collisionToBullet(Bullet* _otherBullet, int _collisionface = 0);

	void createBullet(int _color = 0, int _index = 0);
	void removeBullet();
	void renderByIndex(HDC _hdc);
	void moveTop(bool _loop = false);
	void moveLeft(bool _loop = false);
	void moveRight(bool _loop = false);
	void moveBottom(bool _loop = false);

	void grabBlockBottom();
	void grabBlockLeft();
	void grabBlockRight();

	void pushBlockTop();
	void pushBlockLeft();
	void pushBlockRight();
	void pushBlockBottom();

	void updateRect()
	{
		rect = RectMake(x, y, 50, 50);
		switch (index)
		{
		case 301:
		case 302:
		case 303:
		case 304:
		case 305:
		case 306:
		case 307:
		case 308:
		case 309:
		case 310:
		case 311:
		case 312:
		case 313:
		case 314:
			rect = RectMake(x, y + 25, 50, 25);
		}
	}

	RECT getRect()
	{
		return rect;
	}

	void setIndex(int _index)
	{
		index = _index;
	}

	int getIndex()
	{
		return index;
	}

	void setValid(bool _valid)
	{
		valid = _valid;
	}

	bool isValid()
	{
		return valid;
	}

	int getFrameX()
	{
		return frameX;
	}

	int getFrameY()
	{
		return frameY;
	}


	void setImageFrame(int _frameX, int _frameY)
	{
		frameX = _frameX;
		frameY = _frameY;
	}

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

	float getCenterX()
	{
		return (rect.left + rect.right) / 2;
	}

	float getCenterY()
	{
		return (rect.top + rect.bottom) / 2;
	}

	void setAniPlay(bool _aniPlay)
	{
		aniPlay = _aniPlay;
	}

	bool getAniPlay()
	{
		return aniPlay;
	}

	void setTempBlock(Block* _tempBlock)
	{
		tempBlock = _tempBlock;
	}

	Block* getTempBlock()
	{
		return tempBlock;
	}

	void setTempBlock2(Block* _tempBlock2)
	{
		tempBlock2 = _tempBlock2;
	}

	Block* getTempBlock2()
	{
		return tempBlock2;
	}

	void setUseUpdate(bool _useUpdate)
	{
		useUpdate = _useUpdate;
	}

	bool getUseUpdate()
	{
		return useUpdate;
	}

	bool getUseBullet()
	{
		return useBullet;
	}

	bool getIsRender()
	{
		return isRender;
	}

	void setIsCollision_PlayerToBlock(bool _isCollision)
	{
		isCollision_PlayerToBlock = _isCollision;
	}

	bool getIsCollision_PlayerToBlock()
	{
		return isCollision_PlayerToBlock;
	}

	bool getIsCollision_BlockToBlock()
	{
		return isCollision_BlockToBlock;
	}

	bool getIsCollision_BulletToBlock()
	{
		return isCollision_BulletToBlock;
	}

	float getWidth()
	{
		return width;
	}

	float getHeight()
	{
		return height;
	}

	bool getOverlaped()
	{
		return overlaped;
	}

	void setOverlaped(bool _overlaped)
	{
		overlaped = _overlaped;
	}

	float getTimer()
	{
		return currentTimer;
	}

	void setBulletCount(int _bulletCount)
	{
		bulletCount = _bulletCount;
	}
	int getBulletCount()
	{
		return bulletCount;
	}

	void setCanMoveTop(bool _canMove)
	{
		canMoveTop = _canMove;
	}
	bool getCanMoveTop()
	{
		return canMoveTop;
	}

	void setCanMoveLeft(bool _canMove)
	{
		canMoveLeft = _canMove;
	}
	bool getCanMoveLeft()
	{
		return canMoveLeft;
	}

	void setCanMoveRight(bool _canMove)
	{
		canMoveRight = _canMove;
	}
	bool getCanMoveRight()
	{
		return canMoveRight;
	}

	void setCanMoveBottom(bool _canMove)
	{
		canMoveBottom = _canMove;
	}
	bool getCanMoveBottom()
	{
		return canMoveBottom;
	}

	PlayGame* getPlayGame()
	{
		return playgame;
	}
	void setPlayGame(PlayGame* _playGame)
	{
		playgame = _playGame;
	}

	void setPlayerBall(Ball* _playerBall)
	{
		playerBall = _playerBall;
	}

	void setStat(int stat2)
	{
		stat = stat2;
	}
	int getStat()
	{
		return stat;
	}

};

