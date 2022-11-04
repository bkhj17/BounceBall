#pragma once

class Block;

enum Shape
{
	circle,
	rectangle
};

class Bullet
{
private:
	int index;
	int shape;
	int color;
	HBRUSH Brush;
	HBRUSH oBrush;
	int frameX, frameY;

	RECT rect;
	float x, y;
	float width, height;
	float startX, startY;
	float Xspeed, Yspeed;

	bool  valid;
	bool  useUpdate;

	Block* srcBlock; //소스블록(쏜사람주인)

public:
	Bullet();
	~Bullet();

	void init(int _index = 0, bool _valid = false, Block* _srcBlock = NULL);
	void update();
	void render(HDC _hdc);
	void collision(Block* _block, int _collisionface = 0);

	void updateRect(bool _square = true)
	{
		rect = RectMakeCenter(x, y, width * 2, height * 2);
	}

	int getIndex()
	{
		return index;
	}
	void setIndex(int _index)
	{
		index = _index;
	}

	int getShape()
	{
		return shape;
	}
	void setShape(int _shape)
	{
		shape = _shape;
	}

	RECT getRect()
	{
		return rect;
	}
	void setRect(RECT _rect)
	{
		rect = _rect;
	}

	float getX()
	{
		return x;
	}
	void setX(float _x)
	{
		x = _x;
	}

	float getY()
	{
		return y;
	}
	void setY(float _y)
	{
		y = _y;
	}

	bool getValid()
	{
		return valid;
	}
	void setValid(bool _valid)
	{
		valid = _valid;
	}

	bool getUseUpdate()
	{
		return useUpdate;
	}
	void setUseUpdate(bool _useUpdate)
	{
		useUpdate = _useUpdate;
	}

	int getStartX()
	{
		return startX;
	}
	void setStartX(float _startX)
	{
		startX = _startX;
	}

	int getStartY()
	{
		return startY;
	}
	void setStartY(float _startY)
	{
		startY = _startY;
	}

	float getXspeed()
	{
		return Xspeed;
	}
	void setXspeed(float _Xspeed)
	{
		Xspeed = _Xspeed;
	}

	float getYspeed()
	{
		return Yspeed;
	}
	void setYspeed(float _Yspeed)
	{
		Yspeed = _Yspeed;
	}

	Block* getSrcBlock()
	{
		return srcBlock;
	}
	void setSrcBlock(Block* _srcBlock)
	{
		srcBlock = _srcBlock;
	}

	void setColor(int _color)
	{
		color = _color;
	}
	int getColor()
	{
		return color;
	}
};

