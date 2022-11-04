#include "BounceBallHeader.h"

Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

void Bullet::init(int _index, bool _valid, Block* _srcBlock)
{
	index = _index;
	valid = _valid;
	color = white;

	if (_srcBlock != NULL)
	{
		srcBlock = _srcBlock;
		x = srcBlock->getCenterX();
		y = srcBlock->getCenterY();
		startX = x;
		startY = y;
	}

	switch (index)
	{
	case 505:
		shape = rectangle;
		width = 25;
		height = 25;
		Xspeed = 0;
		Yspeed = 0;
		break;

	case 1401:
		shape = rectangle;
		width = 20;
		height = 20;
		Xspeed = 0;
		Yspeed = -7.5;
		break;
	case 1402:
		shape = rectangle;
		width = 20;
		height = 20;
		Xspeed = 7.5;
		Yspeed = 0;
		break;
	case 1403:
		shape = rectangle;
		width = 20;
		height = 20;
		Xspeed = 0;
		Yspeed = 7.5;
		break;
	case 1404:
		shape = rectangle;
		width = 20;
		height = 20;
		Xspeed = -7.5;
		Yspeed = 0;
		break;

	case 1001:
	case 1101:
		shape = rectangle;

		width = 5;
		height = WINSIZEY;

		Xspeed = 0;
		Yspeed = 0;
		break;

	case 1002:
	case 1102:
		shape = rectangle;

		width = WINSIZEX;
		height = 5;

		Xspeed = 0;
		Yspeed = 0;
		break;

	case 1003:
	case 1103:
		shape = rectangle;

		width = 5;
		height = WINSIZEY;

		Xspeed = 0;
		Yspeed = 0;
		break;

	case 1004:
	case 1104:
		shape = rectangle;

		width = WINSIZEX;
		height = 5;

		Xspeed = 0;
		Yspeed = 0;
		break;

	case 1602:
	case 1604:
		shape = rectangle;
		width = 25;
		height = 5;
		Xspeed = 0;
		Yspeed = 0;
		break;

	case 1601:
	case 1603:
		shape = rectangle;
		width = 5;
		height = 25;
		Xspeed = 0;
		Yspeed = 0;
		break;
	}

	updateRect();
}

void Bullet::update()
{
	switch (index)
	{
	case 505:
		Yspeed += GRAVITY * 0.75;
		break;

	case 1001:
	case 1101:
		if (srcBlock->getTempBlock() != NULL)
		{
			height = (srcBlock->getY() - srcBlock->getTempBlock()->getY()) / 2;
		}
		else
		{
			height = WINSIZEY;
		}

		if (srcBlock->getIndex() == 1801 || srcBlock->getIndex() == 1802) //안으로 꺽이는거 방지
		{
			if (srcBlock->getTempBlock2() != NULL)
			{
				height = (srcBlock->getY() - srcBlock->getTempBlock2()->getY()) / 2;
			}
			else
			{
				height = WINSIZEY;
			}
		}

		x = srcBlock->getCenterX();
		y = srcBlock->getCenterY() - height;
		height -= 20;
		updateRect();
		break;

	case 1002:
	case 1102:
		if (srcBlock->getTempBlock() != NULL)
		{
			width = (srcBlock->getTempBlock()->getX() - srcBlock->getX()) / 2;
		}
		else
		{
			width = WINSIZEX;
		}

		x = srcBlock->getCenterX() + width;
		y = srcBlock->getCenterY();
		width -= 20;
		updateRect();
		break;

	case 1003:
	case 1103:
		if (srcBlock->getTempBlock() != NULL)
		{
			height = (srcBlock->getTempBlock()->getY() - srcBlock->getY()) / 2;
		}
		else
		{
			height = WINSIZEY;
		}

		if (srcBlock->getIndex() == 1803 || srcBlock->getIndex() == 1804) //안으로 꺽이는거 방지
		{
			if (srcBlock->getTempBlock2() != NULL)
			{
				height = (srcBlock->getTempBlock2()->getY() - srcBlock->getY()) / 2;
			}
			else
			{
				height = WINSIZEY;
			}
		}

		x = srcBlock->getCenterX();
		y = srcBlock->getCenterY() + height;
		height -= 20;
		updateRect();
		break;

	case 1004:
	case 1104:
		if (srcBlock->getTempBlock() != NULL)
		{
			width = (srcBlock->getX() - srcBlock->getTempBlock()->getX()) / 2;
		}
		else
		{
			width = WINSIZEY;
		}

		x = srcBlock->getCenterX() - width;
		y = srcBlock->getCenterY();
		width -= 20;
		updateRect();
		break;
	}

	if (Xspeed >= MAXXSPEED)
	{
		Xspeed = MAXXSPEED;
	}
	if (Xspeed <= -MAXXSPEED)
	{
		Xspeed = -MAXXSPEED;
	}
	if (Yspeed >= MAXYSPEED)
	{
		Yspeed = MAXYSPEED;
	}
	if (Yspeed <= -MAXYSPEED)
	{
		Yspeed = -MAXYSPEED;
	}
	x += Xspeed;
	y += Yspeed;

	updateRect();
}

void Bullet::render(HDC _hdc)
{
	switch (index)
	{
	case 505:
		frameX = 0;
		frameY = 4;
		IMAGEMANAGER->frameRender(TEXT("501-520_Block"), _hdc, rect.left, rect.top, frameX, frameY);
		break;

	case 1001:
	case 1002:
	case 1003:
	case 1004:
		Brush = CreateSolidBrush(RGB(239, 28, 123));
		oBrush = (HBRUSH)SelectObject(_hdc, Brush);


		Rectangle(_hdc, rect.left, rect.top, rect.right, rect.bottom);

		SelectObject(_hdc, oBrush);
		DeleteObject(Brush);
		break;

	case 1101:
	case 1102:
	case 1103:
	case 1104:
		Brush = CreateSolidBrush(RGB(41, 170, 231));
		oBrush = (HBRUSH)SelectObject(_hdc, Brush);

		Rectangle(_hdc, rect.left, rect.top, rect.right, rect.bottom);

		SelectObject(_hdc, oBrush);
		DeleteObject(Brush);
		break;

	case 1401:
	case 1402:
	case 1403:
	case 1404:
		if (color == red)
			Brush = CreateSolidBrush(RGB(239, 28, 123));
		if (color == blue)
			Brush = CreateSolidBrush(RGB(41, 170, 231));

		oBrush = (HBRUSH)SelectObject(_hdc, Brush);

		Rectangle(_hdc, rect.left, rect.top, rect.right, rect.bottom);

		SelectObject(_hdc, oBrush);
		DeleteObject(Brush);
		break;

	case 1601:
	case 1602:
	case 1603:
	case 1604:
		Brush = CreateSolidBrush(RGB(100, 100, 100));

		oBrush = (HBRUSH)SelectObject(_hdc, Brush);

		Rectangle(_hdc, rect.left, rect.top, rect.right, rect.bottom);

		SelectObject(_hdc, oBrush);
		DeleteObject(Brush);
		break;
	}
}

void Bullet::collision(Block * _block, int _collisionface)
{
	switch (index)
	{
	case 505:
	case 1401:
	case 1402:
	case 1403:
	case 1404:
		valid = false;
		Yspeed = 0;
		break;

	case 1601:
		_block->pushBlockTop();
		break;
	case 1602:
		_block->pushBlockRight();
		break;
	case 1603:
		_block->pushBlockBottom();
		break;
	case 1604:
		_block->pushBlockLeft();
		break;
	}
}
