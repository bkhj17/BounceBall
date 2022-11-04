#include "BounceBallHeader.h"
#include "PlayGame.h"
#include "Block.h"

Block::Block()
{
}

Block::~Block()
{
}

void Block::init(int _index, bool _valid)
{
	index = _index;
	valid = _valid;

	startX = x;
	startY = y;

	updateRect();
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	isCollision_PlayerToBlock = true;
	isCollision_BlockToBlock = true;
	isCollision_BulletToBlock = true;

	aniPlay = false;
	useUpdate = true;
	isRender = true;
	useBullet = false;

	overlaped = false;
	bulletCount = 0;

	stat = move;

	canMoveTop = true;
	canMoveLeft = true;
	canMoveRight = true;
	canMoveBottom = true;

	Xspeed = 0;
	Yspeed = 0;

	switch (index)
	{
	case 101:
	case 102:
	case 103:
	case 601:
	case 602:
	case 603:
	case 604:
	case 605:
	case 606:
	case 607:
	case 608:
	case 702:
	{
		isCollision_BulletToBlock = false;
		isCollision_BlockToBlock = false;
		break;
	}

	case 504:
	{
		useUpdate = false;
		break;
	}

	case 505:
	{
		isRender = false;
		isCollision_PlayerToBlock = false;
		isCollision_BlockToBlock = false;

		useBullet = true;
		useUpdate = true;

		maxTimer = 75;
		currentTimer = maxTimer;
		break;
	}

	case 701:
	{
		isCollision_BlockToBlock = false;
		break;
	}

	case 704:
	case 705:
	case 706:
	{
		useUpdate = true;
		maxTimer = 100;
		stat = off;
		break;
	}

	case 801:
	case 802:
	case 803:
	case 804:
	{
		maxTimer = 10;
		currentTimer = maxTimer;

		Yspeed = 0;
		stat = move;

		useUpdate = true;
		break;
	}
	case 1001:
	case 1002:
	case 1003:
	case 1004:
	case 1101:
	case 1102:
	case 1103:
	case 1104:
	case 1601:
	case 1602:
	case 1603:
	case 1604:
	case 1801:
	case 1802:
	case 1803:
	case 1804:
	{
		tempBlock = NULL;
		tempBlock2 = NULL;
		useBullet = true;
		break;
	}

	case 1301:
	case 1302:
	case 1303:
	{
		useUpdate = true;
		break;
	}
	case 1401:
	case 1402:
	case 1403:
	case 1404:
	{
		useBullet = true;
		useUpdate = true;

		maxTimer = 75;
		currentTimer = maxTimer;
		break;
	}

	case 1901:
	{
		Xspeed = 3;
		Yspeed = 0;
		useUpdate = true;
		break;
	}
	case 1902:
	{
		Xspeed = 0;
		Yspeed = 3;
		useUpdate = true;
		break;
	}
	default:
		break;
	}
}

void Block::init(Bullet * _bullet, int i)
{
	bullet[i] = _bullet;
}

void Block::update()
{
	switch (index)
	{
	case 504:
	{
		Yspeed += GRAVITY;
		break;
	}
	case 505:
	{
		currentTimer++;
		if (currentTimer >= maxTimer)
		{
			createBullet();
			currentTimer = 0;
		}
		break;
	}

	case 702:
	{
		RECT temp;
		RECT rcBall = RectMakeCenter(playerBall->getX(), playerBall->getY(), playerBall->getRadius(), playerBall->getRadius());
		POINT ptBall = { playerBall->getX(),playerBall->getY() };

		if (IntersectRect(&temp, &rcBall, &rect)) //버그때매 더럽게 코드가 바뀜
		{
			float lengthX = temp.right - temp.left;
			float lengthY = temp.bottom - temp.top;

			if (lengthX > 5)
			{
				playgame->setSwitch_Star(true);
			}
			if (lengthY > 5)
			{
				playgame->setSwitch_Star(true);
			}

			if (lengthX <= 5)
			{
				playgame->setSwitch_Star(false);
			}
			if (lengthY <= 5)
			{
				playgame->setSwitch_Star(false);
			}
		}

		if (overlaped)
		{
			playgame->setSwitch_Star(true);
		}

		break;
	}

	case 704:
	{
		if (stat == on)
		{
			currentTimer++;
			if (currentTimer >= maxTimer)
			{
				stat = off;
				currentTimer = 0;
			}
		}
		if (stat == off)
		{
			currentTimer++;
			if (currentTimer >= maxTimer)
			{
				stat = on;
				currentTimer = 0;
			}
		}
		break;
	}
	case 705:
	{
		if (stat == on)
		{
			currentTimer++;
			if (currentTimer >= maxTimer)
			{
				stat = off;
				currentTimer = 0;
			}
		}
		if (stat == off)
		{
			currentTimer++;
			if (currentTimer >= maxTimer)
			{
				stat = on;
				currentTimer = 0;
			}
		}
		break;
	}
	case 706:
	{
		if (stat == on)
		{
			currentTimer++;
			if (currentTimer >= maxTimer)
			{
				stat = redBlock;
				currentTimer = 0;
			}
		}
		if (stat == redBlock)
		{
			currentTimer++;
			if (currentTimer >= maxTimer)
			{
				stat = blueBlock;
				currentTimer = 0;
			}
		}
		break;
	}

	case 801:
	{
		if (currentTimer <= 0 && stat == stop)
		{
			currentTimer = maxTimer;
			Yspeed = -10;
			stat = move;
		}

		if (stat == stop)
		{
			Yspeed = 0;
			currentTimer -= 0.1;
		}

		if (stat == move)
		{
			Yspeed += GRAVITY;
		}
		break;
	}
	case 802:
	{
		if (currentTimer <= 0 && stat == stop)
		{
			currentTimer = maxTimer;
			Xspeed = 10;
			stat = move;
		}

		if (stat == stop)
		{
			Yspeed = 0;
			currentTimer -= 0.1;
		}

		if (stat == move)
		{
			Xspeed -= GRAVITY;
		}
		break;
	}
	case 803:
	{
		if (currentTimer <= 0 && stat == stop)
		{
			currentTimer = maxTimer;
			Yspeed = 10;
			stat = move;
		}

		if (stat == stop)
		{
			Yspeed = 0;
			currentTimer -= 0.1;
		}

		if (stat == move)
		{
			Yspeed -= GRAVITY;
		}
		break;
	}
	case 804:
	{
		if (currentTimer <= 0 && stat == stop)
		{
			currentTimer = maxTimer;
			Xspeed = -10;
			stat = move;
		}

		if (stat == stop)
		{
			Xspeed = 0;
			currentTimer -= 0.1;
		}

		if (stat == move)
		{
			Xspeed += GRAVITY;
		}
		break;
	}

	case 1401:
	{
		currentTimer++;
		if (currentTimer >= maxTimer)
		{
			createBullet(red);
			currentTimer = 0;
		}
		break;
	}
	case 1402:
	{
		currentTimer++;
		if (currentTimer >= maxTimer)
		{
			createBullet(red);
			currentTimer = 0;
		}
		break;
	}
	case 1403:
	{
		currentTimer++;
		if (currentTimer >= maxTimer)
		{
			createBullet(red);
			currentTimer = 0;
		}
		break;
	}
	case 1404:
	{
		currentTimer++;
		if (currentTimer >= maxTimer)
		{
			createBullet(red);
			currentTimer = 0;
		}
		break;
	}
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

	if (stat == move)
	{
		x += Xspeed;
		y += Yspeed;
		updateRect();
	}

	if (stat == tempOff)
	{
		isCollision_PlayerToBlock = false;
		isRender = false;
		currentTimer -= 0.1;
		if (currentTimer <= 0)
		{
			stat = tempOn;
		}
	}

	if (stat == tempOn)
	{
		isCollision_PlayerToBlock = true;
		isRender = true;
		if (loop)
			switch (index)
			{
			case 1205:
				moveTop();
				break;
			case 1206:
				moveRight();
				break;
			case 1207:
				moveLeft();
				break;
			case 1208:
				moveBottom();
				break;
			}
	}
}

void Block::render(HDC _hdc)
{
	if (!aniPlay)
	{
		renderByIndex(_hdc);
	}
	else // 애니메이션이 있으면 애니메이션 출력
	{
		switch (index)
		{
		case 513:
			IMAGEMANAGER->frameRender(TEXT("513_Block_ani"), _hdc, x, y, frameX, frameY);
			break;

		case 516:
			IMAGEMANAGER->frameRender(TEXT("516_Block_ani"), _hdc, x, y, frameX, frameY);
			break;
		}
	}
}

void Block::collision(Block * _otherBlock, int _collisionface)
{
	switch (index)
	{
	case 504:
	{
		Yspeed = 0;
		useUpdate = false;
		break;
	}

	case 801:
	{
		if (_collisionface == 4)
		{
			stat = stop;
		}
		if (_collisionface == 1)
		{
			Yspeed = 0.75;
		}
		break;
	}
	case 802:
	{
		if (_collisionface == 2)
		{
			stat = stop;
		}
		if (_collisionface == 3)
		{
			Xspeed = -0.75;
		}
		break;
	}
	case 803:
	{
		if (_collisionface == 1)
		{
			stat = stop;
		}
		if (_collisionface == 4)
		{
			Yspeed = -0.75;
		}
		break;
	}
	case 804:
	{
		if (_collisionface == 3)
		{
			stat = stop;
		}
		if (_collisionface == 2)
		{
			Xspeed = +0.75;
		}
		break;
	}

	case 1201:
		y = _otherBlock->getY() + height;
		updateRect();
		break;
	case 1202:
		x = _otherBlock->getX() - width;
		updateRect();
		break;
	case 1203:
		x = _otherBlock->getX() + width;
		updateRect();
		break;
	case 1204:
		y = _otherBlock->getY() - height;
		updateRect();
		break;
	case 1205:
		y = _otherBlock->getY() + height;
		updateRect();
		loop = false;
		break;
	case 1206:
		x = _otherBlock->getX() - width;
		updateRect();
		loop = false;
		break;
	case 1207:
		x = _otherBlock->getX() + width;
		updateRect();
		loop = false;
		break;
	case 1208:
		y = _otherBlock->getY() - height;
		updateRect();
		loop = false;
		break;

	case 1901:
		Xspeed = -Xspeed;
		break;
	case 1902:
		Yspeed = -Yspeed;
		break;
	}
}

void Block::collisionToBullet(Bullet * _otherBullet, int _collisionface)
{
	switch (index)
	{
	case 1801:
	{
		if (_collisionface == 1) //윗면
		{
			//파랑 레이저
			if (_otherBullet->getIndex() == 1103) //아래쪽으로 진행중인 빛이면
			{
				if (bulletCount <= 0)
				{
					createBullet(0, 1104); //왼쪽으로 쏜다
					bulletCount++;
				}
				break;
			}

			//빨강 레이저
			if (_otherBullet->getIndex() == 1003) //아래쪽으로 진행중인 빛이면
			{
				if (bulletCount <= 0)
				{
					createBullet(0, 1004); //왼쪽으로 쏜다
					bulletCount++;
				}
				break;
			}
		}
		if (_collisionface == 2) //왼면
		{
			//파랑 레이저
			if (_otherBullet->getIndex() == 1102) //오른쪽으로 진행중인 빛이면
			{
				if (bulletCount <= 0)
				{
					createBullet(0, 1101); //위로 쏜다
					bulletCount++;
				}
				break;
			}

			//빨강 레이저
			if (_otherBullet->getIndex() == 1002) //오른쪽으로 진행중인 빛이면
			{
				if (bulletCount <= 0)
				{
					createBullet(0, 1001); //위로 쏜다
					bulletCount++;
				}
				break;
			}
		}
		break;
	}
	case 1802:
	{
		if (_collisionface == 1) //윗면
		{
			//파랑 레이저
			if (_otherBullet->getIndex() == 1103) //아래쪽으로 진행중인 빛이면
			{
				if (bulletCount <= 0)
				{
					createBullet(0, 1102); //오른쪽으로 쏜다
					bulletCount++;
				}
				break;
			}

			//빨강 레이저
			if (_otherBullet->getIndex() == 1003) //아래쪽으로 진행중인 빛이면
			{
				if (bulletCount <= 0)
				{
					createBullet(0, 1002); //오른쪽으로 쏜다
					bulletCount++;
				}
				break;
			}
		}
		if (_collisionface == 3) //오른쪽면
		{
			//파랑 레이저
			if (_otherBullet->getIndex() == 1104) //왼쪽으로 진행중인 빛이면
			{
				if (bulletCount <= 0)
				{
					createBullet(0, 1101); //위로 쏜다
					bulletCount++;
				}
				break;
			}

			//빨강 레이저
			if (_otherBullet->getIndex() == 1004) //왼쪽으로 진행중인 빛이면
			{
				if (bulletCount <= 0)
				{
					createBullet(0, 1001); //위로 쏜다
					bulletCount++;
				}
				break;
			}
		}
		break;
	}
	case 1803:
	{
		if (_collisionface == 3) //오른쪽면
		{
			//파랑 레이저
			if (_otherBullet->getIndex() == 1104) //왼쪽으로 진행중인 빛이면
			{
				if (bulletCount <= 0)
				{
					createBullet(0, 1103); //아래로 쏜다
					bulletCount++;
				}
				break;
			}

			//빨강 레이저
			if (_otherBullet->getIndex() == 1004) //왼쪽으로 진행중인 빛이면
			{
				if (bulletCount <= 0)
				{
					createBullet(0, 1003); //아래로 쏜다
					bulletCount++;
				}
				break;
			}
		}
		if (_collisionface == 4) //밑면
		{
			//파랑 레이저
			if (_otherBullet->getIndex() == 1101) //위로 진행중인 빛이면
			{
				if (bulletCount <= 0)
				{
					createBullet(0, 1102); //오른쪽으로 쏜다
					bulletCount++;
				}
				break;
			}

			//빨강 레이저
			if (_otherBullet->getIndex() == 1001) //위로 진행중인 빛이면
			{
				if (bulletCount <= 0)
				{
					createBullet(0, 1002); //오른쪽으로 쏜다
					bulletCount++;
				}
				break;
			}
		}
		break;
	}
	case 1804:
	{
		if (_collisionface == 2) //왼면
		{
			//파랑 레이저
			if (_otherBullet->getIndex() == 1102) //오른쪽으로 진행중인 빛이면
			{
				if (bulletCount <= 0)
				{
					createBullet(0, 1103); //밑으로 쏜다
					bulletCount++;
				}
				break;
			}

			//빨강 레이저
			if (_otherBullet->getIndex() == 1002) //오른쪽으로 진행중인 빛이면
			{
				if (bulletCount <= 0)
				{
					createBullet(0, 1003); //밑으로 쏜다
					bulletCount++;
				}
				break;
			}
		}
		if (_collisionface == 4) //밑면
		{
			//파랑 레이저
			if (_otherBullet->getIndex() == 1101) //위쪽으로 들어온 빛이면
			{
				if (bulletCount <= 0)
				{
					createBullet(0, 1104); //왼쪽으로 쏜다
					bulletCount++;
				}
				break;
			}

			//빨강 레이저
			if (_otherBullet->getIndex() == 1001) //위쪽으로 들어온 빛이면
			{
				if (bulletCount <= 0)
				{
					createBullet(0, 1004); //왼쪽으로 쏜다
					bulletCount++;
				}
				break;
			}
		}
		break;
	}
	}
}

void Block::createBullet(int _color, int _index)
{
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (bullet[i]->getValid())
			continue;

		if (_index)
			bullet[i]->init(_index, true, this);
		else
			bullet[i]->init(index, true, this);

		bullet[i]->setColor(_color);

		switch (index)
		{
		case 1601:
		{
			bullet[i]->setY(y - (25 + bulletCount * 50));
			bulletCount++;
			bullet[i]->updateRect(false);
			break;
		}
		case 1602:
		{
			bulletCount++; //한칸 덜가는데 이유를 모름
			bullet[i]->setX(x + (25 + bulletCount * 50));
			bullet[i]->updateRect(false);
			break;
		}
		case 1603:
		{
			bullet[i]->setY(y + 25 + bulletCount * 50);
			bulletCount++;
			bullet[i]->updateRect(false);
			break;
		}
		case 1604:
		{
			bullet[i]->setX(x - (25 + bulletCount * 50));
			bulletCount++;
			bullet[i]->updateRect(false);
			break;
		}
		}
		break;
	}
}

void Block::removeBullet()
{
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (!bullet[i]->getValid())
			continue;
		if (bullet[i]->getSrcBlock() == this)
			bullet[i]->init(0, false, NULL);
	}
}

void Block::renderByIndex(HDC _hdc)
{
	switch (index)
	{
	case 101:
		frameX = 0;
		frameY = 0;
		IMAGEMANAGER->frameRender(TEXT("101-103_Star"), _hdc, x, y, frameX, frameY);
		break;

	case 102:
		if (playgame != NULL)
		{
			if (playgame->getSwitch_Star())
			{
				frameX = 0;
				frameY = 0;
			}
			else
			{
				frameX = 0;
				frameY = 1;
			}
			IMAGEMANAGER->frameRender(TEXT("101-103_Star"), _hdc, x, y, frameX, frameY);
		}
		else
		{
			frameX = 0;
			frameY = 1;
			IMAGEMANAGER->frameRender(TEXT("101-103_Star"), _hdc, x, y, frameX, frameY);
		}
		break;


	case 103:
		frameX = 0;
		frameY = 2;
		IMAGEMANAGER->frameRender(TEXT("101-103_Star"), _hdc, x, y, frameX, frameY);
		break;

	case 201:
		frameX = 0;
		frameY = 0;
		IMAGEMANAGER->frameRender(TEXT("201-217_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 202:
		frameX = 0;
		frameY = 1;
		IMAGEMANAGER->frameRender(TEXT("201-217_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 203:
		frameX = 0;
		frameY = 2;
		IMAGEMANAGER->frameRender(TEXT("201-217_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 204:
		frameX = 0;
		frameY = 3;
		IMAGEMANAGER->frameRender(TEXT("201-217_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 205:
		frameX = 0;
		frameY = 4;
		IMAGEMANAGER->frameRender(TEXT("201-217_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 206:
		frameX = 0;
		frameY = 5;
		IMAGEMANAGER->frameRender(TEXT("201-217_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 207:
		frameX = 1;
		frameY = 0;
		IMAGEMANAGER->frameRender(TEXT("201-217_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 208:
		frameX = 1;
		frameY = 1;
		IMAGEMANAGER->frameRender(TEXT("201-217_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 209:
		frameX = 1;
		frameY = 2;
		IMAGEMANAGER->frameRender(TEXT("201-217_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 210:
		frameX = 1;
		frameY = 3;
		IMAGEMANAGER->frameRender(TEXT("201-217_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 211:
		frameX = 1;
		frameY = 4;
		IMAGEMANAGER->frameRender(TEXT("201-217_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 212:
		frameX = 1;
		frameY = 5;
		IMAGEMANAGER->frameRender(TEXT("201-217_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 213:
		frameX = 2;
		frameY = 0;
		IMAGEMANAGER->frameRender(TEXT("201-217_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 214:
		frameX = 2;
		frameY = 1;
		IMAGEMANAGER->frameRender(TEXT("201-217_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 215:
		frameX = 2;
		frameY = 2;
		IMAGEMANAGER->frameRender(TEXT("201-217_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 216:
		if (playgame != NULL)
		{
			if (playgame->getSwitch_Green())
			{
				frameX = 2;
				frameY = 3;
				IMAGEMANAGER->frameRender(TEXT("201-217_Block"), _hdc, x, y, frameX, frameY);
			}
			else
			{
				IMAGEMANAGER->render(TEXT("216_Block_ani"), _hdc, x, y);
			}
		}
		else
		{
			frameX = 2;
			frameY = 3;
			IMAGEMANAGER->frameRender(TEXT("201-217_Block"), _hdc, x, y, frameX, frameY);
		}
		break;

	case 217:
		if (playgame != NULL)
		{
			if (playgame->getSwitch_Orange())
			{
				frameX = 2;
				frameY = 4;
				IMAGEMANAGER->frameRender(TEXT("201-217_Block"), _hdc, x, y, frameX, frameY);
			}
			else
			{
				IMAGEMANAGER->render(TEXT("217_Block_ani"), _hdc, x, y);
			}
		}
		else
		{
			frameX = 2;
			frameY = 4;
			IMAGEMANAGER->frameRender(TEXT("201-217_Block"), _hdc, x, y, frameX, frameY);
		}
		break;

	case 301:
		frameX = 0;
		frameY = 0;
		IMAGEMANAGER->frameRender(TEXT("301-314_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 302:
		frameX = 0;
		frameY = 1;
		IMAGEMANAGER->frameRender(TEXT("301-314_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 303:
		frameX = 0;
		frameY = 2;
		IMAGEMANAGER->frameRender(TEXT("301-314_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 304:
		frameX = 0;
		frameY = 3;
		IMAGEMANAGER->frameRender(TEXT("301-314_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 305:
		frameX = 0;
		frameY = 4;
		IMAGEMANAGER->frameRender(TEXT("301-314_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 306:
		frameX = 0;
		frameY = 5;
		IMAGEMANAGER->frameRender(TEXT("301-314_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 307:
		frameX = 1;
		frameY = 0;
		IMAGEMANAGER->frameRender(TEXT("301-314_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 308:
		frameX = 1;
		frameY = 1;
		IMAGEMANAGER->frameRender(TEXT("301-314_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 309:
		frameX = 1;
		frameY = 2;
		IMAGEMANAGER->frameRender(TEXT("301-314_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 310:
		frameX = 1;
		frameY = 3;
		IMAGEMANAGER->frameRender(TEXT("301-314_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 311:
		frameX = 1;
		frameY = 4;
		IMAGEMANAGER->frameRender(TEXT("301-314_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 312:
		frameX = 1;
		frameY = 5;
		IMAGEMANAGER->frameRender(TEXT("301-314_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 313:
		frameX = 2;
		frameY = 0;
		IMAGEMANAGER->frameRender(TEXT("301-314_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 314:
		frameX = 2;
		frameY = 1;
		IMAGEMANAGER->frameRender(TEXT("301-314_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 401:
		frameX = 0;
		frameY = 0;
		IMAGEMANAGER->frameRender(TEXT("401_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 501:
		frameX = 0;
		frameY = 0;
		IMAGEMANAGER->frameRender(TEXT("501-520_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 502:
		frameX = 0;
		frameY = 1;
		IMAGEMANAGER->frameRender(TEXT("501-520_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 503:
		frameX = 0;
		frameY = 2;
		IMAGEMANAGER->frameRender(TEXT("501-520_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 504:
		frameX = 0;
		frameY = 3;
		IMAGEMANAGER->frameRender(TEXT("501-520_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 505:
		frameX = 0;
		frameY = 4;
		IMAGEMANAGER->frameRender(TEXT("501-520_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 506:
		frameX = 0;
		frameY = 5;
		IMAGEMANAGER->frameRender(TEXT("501-520_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 507:
		if (playgame != NULL)
		{
			if (playgame->getSwitch_Lightning())
			{
				frameX = 1;
				frameY = 0;
			}
			else
			{
				frameX = 1;
				frameY = 1;
			}
			IMAGEMANAGER->frameRender(TEXT("501-520_Block"), _hdc, x, y, frameX, frameY);
		}
		else
		{
			frameX = 1;
			frameY = 0;
			IMAGEMANAGER->frameRender(TEXT("501-520_Block"), _hdc, x, y, frameX, frameY);
		}
		break;
	case 508:
		if (playgame != NULL)
		{
			if (playgame->getSwitch_Lightning())
			{
				frameX = 1;
				frameY = 0;
			}
			else
			{
				frameX = 1;
				frameY = 1;
			}
			IMAGEMANAGER->frameRender(TEXT("501-520_Block"), _hdc, x, y, frameX, frameY);
		}
		else
		{
			frameX = 1;
			frameY = 1;
			IMAGEMANAGER->frameRender(TEXT("501-520_Block"), _hdc, x, y, frameX, frameY);
		}
		break;

	case 509:
		frameX = 1;
		frameY = 2;
		IMAGEMANAGER->frameRender(TEXT("501-520_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 510:
		frameX = 1;
		frameY = 3;
		IMAGEMANAGER->frameRender(TEXT("501-520_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 511:
		frameX = 1;
		frameY = 4;
		IMAGEMANAGER->frameRender(TEXT("501-520_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 512:
		frameX = 1;
		frameY = 5;
		IMAGEMANAGER->frameRender(TEXT("501-520_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 513:
		frameX = 2;
		frameY = 0;
		IMAGEMANAGER->frameRender(TEXT("501-520_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 514:
		frameX = 2;
		frameY = 1;
		IMAGEMANAGER->frameRender(TEXT("501-520_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 515:
		frameX = 2;
		frameY = 2;
		IMAGEMANAGER->frameRender(TEXT("501-520_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 516:
		frameX = 2;
		frameY = 3;
		IMAGEMANAGER->frameRender(TEXT("501-520_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 517:
		if (playgame != NULL)
		{
			if (!playgame->getSwitch_Green())
			{
				frameX = 2;
				frameY = 4;
			}
			else
			{
				frameX = 2;
				frameY = 5;
			}
			IMAGEMANAGER->frameRender(TEXT("501-520_Block"), _hdc, x, y, frameX, frameY);
		}
		else
		{
			frameX = 2;
			frameY = 4;
			IMAGEMANAGER->frameRender(TEXT("501-520_Block"), _hdc, x, y, frameX, frameY);
		}
		break;

	case 518:
		if (playgame != NULL)
		{
			if (!playgame->getSwitch_Green())
			{
				frameX = 2;
				frameY = 4;
			}
			else
			{
				frameX = 2;
				frameY = 5;
			}
			IMAGEMANAGER->frameRender(TEXT("501-520_Block"), _hdc, x, y, frameX, frameY);
		}
		else
		{
			frameX = 2;
			frameY = 5;
			IMAGEMANAGER->frameRender(TEXT("501-520_Block"), _hdc, x, y, frameX, frameY);
		}
		break;

	case 519:
		if (playgame != NULL)
		{
			if (!playgame->getSwitch_Orange())
			{
				frameX = 3;
				frameY = 0;
			}
			else
			{
				frameX = 3;
				frameY = 1;
			}
			IMAGEMANAGER->frameRender(TEXT("501-520_Block"), _hdc, x, y, frameX, frameY);
		}
		else
		{
			frameX = 3;
			frameY = 0;
			IMAGEMANAGER->frameRender(TEXT("501-520_Block"), _hdc, x, y, frameX, frameY);
		}
		break;

	case 520:
		if (playgame != NULL)
		{
			if (!playgame->getSwitch_Orange())
			{
				frameX = 3;
				frameY = 0;
			}
			else
			{
				frameX = 3;
				frameY = 1;
			}
			IMAGEMANAGER->frameRender(TEXT("501-520_Block"), _hdc, x, y, frameX, frameY);
		}
		else
		{
			frameX = 3;
			frameY = 1;
			IMAGEMANAGER->frameRender(TEXT("501-520_Block"), _hdc, x, y, frameX, frameY);
		}
		break;

	case 601:
		frameX = 0;
		frameY = 0;
		IMAGEMANAGER->frameRender(TEXT("601-608_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 602:
		frameX = 0;
		frameY = 1;
		IMAGEMANAGER->frameRender(TEXT("601-608_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 603:
		frameX = 0;
		frameY = 2;
		IMAGEMANAGER->frameRender(TEXT("601-608_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 604:
		frameX = 0;
		frameY = 3;
		IMAGEMANAGER->frameRender(TEXT("601-608_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 605:
		frameX = 0;
		frameY = 4;
		IMAGEMANAGER->frameRender(TEXT("601-608_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 606:
		frameX = 0;
		frameY = 5;
		IMAGEMANAGER->frameRender(TEXT("601-608_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 607:
		frameX = 1;
		frameY = 0;
		IMAGEMANAGER->frameRender(TEXT("601-608_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 608:
		frameX = 1;
		frameY = 1;
		IMAGEMANAGER->frameRender(TEXT("601-608_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 701:
		if (playgame != NULL)
		{
			if (playgame->getSwitch_Lightning())
			{
				frameX = 0;
				frameY = 0;
				IMAGEMANAGER->frameRender(TEXT("701-710_Block"), _hdc, x, y, frameX, frameY);
				break;
			}
			else
			{
				IMAGEMANAGER->render(TEXT("701_Block_ani"), _hdc, x, y);
			}
		}
		else
		{
			frameX = 0;
			frameY = 0;
			IMAGEMANAGER->frameRender(TEXT("701-710_Block"), _hdc, x, y, frameX, frameY);
			break;
		}
		break;


	case 702:
		if (playgame != NULL)
		{
			if (playgame->getSwitch_Star())
			{
				IMAGEMANAGER->render(TEXT("702_Block_ani"), _hdc, x, y);
			}
			else
			{
				frameX = 0;
				frameY = 1;
				IMAGEMANAGER->frameRender(TEXT("701-710_Block"), _hdc, x, y, frameX, frameY);
			}
		}
		else
		{
			frameX = 0;
			frameY = 1;
			IMAGEMANAGER->frameRender(TEXT("701-710_Block"), _hdc, x, y, frameX, frameY);
		}
		break;

	case 703:
		frameX = 0;
		frameY = 2;
		IMAGEMANAGER->frameRender(TEXT("701-710_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 704:
		if (stat == on)
		{
			Brush = CreateSolidBrush(RGB(41, 170, 231));

			oBrush = (HBRUSH)SelectObject(_hdc, Brush);

			Rectangle(_hdc, rect.left, rect.top, rect.right, rect.bottom);

			SelectObject(_hdc, oBrush);
			DeleteObject(Brush);
		}
		else
		{
			frameX = 0;
			frameY = 3;
			IMAGEMANAGER->frameRender(TEXT("701-710_Block"), _hdc, x, y, frameX, frameY);
		}
		break;

	case 705:
		if (stat == on)
		{
			Brush = CreateSolidBrush(RGB(239, 28, 123));

			oBrush = (HBRUSH)SelectObject(_hdc, Brush);

			Rectangle(_hdc, rect.left, rect.top, rect.right, rect.bottom);

			SelectObject(_hdc, oBrush);
			DeleteObject(Brush);
		}
		else
		{
			frameX = 0;
			frameY = 4;
			IMAGEMANAGER->frameRender(TEXT("701-710_Block"), _hdc, x, y, frameX, frameY);
		}
		break;

	case 706:
		if (stat == redBlock)
		{
			Brush = CreateSolidBrush(RGB(239, 28, 123));

			oBrush = (HBRUSH)SelectObject(_hdc, Brush);

			Rectangle(_hdc, rect.left, rect.top, rect.right, rect.bottom);

			SelectObject(_hdc, oBrush);
			DeleteObject(Brush);
		}
		else if (stat == blueBlock)
		{
			Brush = CreateSolidBrush(RGB(41, 170, 231));

			oBrush = (HBRUSH)SelectObject(_hdc, Brush);

			Rectangle(_hdc, rect.left, rect.top, rect.right, rect.bottom);

			SelectObject(_hdc, oBrush);
			DeleteObject(Brush);
		}
		else
		{
			frameX = 0;
			frameY = 5;
			IMAGEMANAGER->frameRender(TEXT("701-710_Block"), _hdc, x, y, frameX, frameY);
		}
		break;

	case 707:
		frameX = 1;
		frameY = 0;
		IMAGEMANAGER->frameRender(TEXT("701-710_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 708:
		frameX = 1;
		frameY = 1;
		IMAGEMANAGER->frameRender(TEXT("701-710_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 709:
		frameX = 1;
		frameY = 2;
		IMAGEMANAGER->frameRender(TEXT("701-710_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 710:
		frameX = 1;
		frameY = 3;
		IMAGEMANAGER->frameRender(TEXT("701-710_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 801:
		frameX = 0;
		frameY = 0;
		IMAGEMANAGER->frameRender(TEXT("801-804_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 802:
		frameX = 0;
		frameY = 1;
		IMAGEMANAGER->frameRender(TEXT("801-804_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 803:
		frameX = 0;
		frameY = 2;
		IMAGEMANAGER->frameRender(TEXT("801-804_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 804:
		frameX = 0;
		frameY = 3;
		IMAGEMANAGER->frameRender(TEXT("801-804_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 901:
		frameX = 0;
		frameY = 0;
		IMAGEMANAGER->frameRender(TEXT("901_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1001:
		frameX = 0;
		frameY = 0;
		IMAGEMANAGER->frameRender(TEXT("1001-1004_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1002:
		frameX = 0;
		frameY = 1;
		IMAGEMANAGER->frameRender(TEXT("1001-1004_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1003:
		frameX = 0;
		frameY = 2;
		IMAGEMANAGER->frameRender(TEXT("1001-1004_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1004:
		frameX = 0;
		frameY = 3;
		IMAGEMANAGER->frameRender(TEXT("1001-1004_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1101:
		frameX = 0;
		frameY = 0;
		IMAGEMANAGER->frameRender(TEXT("1101-1104_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1102:
		frameX = 0;
		frameY = 1;
		IMAGEMANAGER->frameRender(TEXT("1101-1104_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1103:
		frameX = 0;
		frameY = 2;
		IMAGEMANAGER->frameRender(TEXT("1101-1104_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1104:
		frameX = 0;
		frameY = 3;
		IMAGEMANAGER->frameRender(TEXT("1101-1104_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1201:
		frameX = 0;
		frameY = 0;
		IMAGEMANAGER->frameRender(TEXT("1201-1208_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1202:
		frameX = 0;
		frameY = 1;
		IMAGEMANAGER->frameRender(TEXT("1201-1208_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1203:
		frameX = 0;
		frameY = 2;
		IMAGEMANAGER->frameRender(TEXT("1201-1208_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1204:
		frameX = 0;
		frameY = 3;
		IMAGEMANAGER->frameRender(TEXT("1201-1208_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1205:
		frameX = 0;
		frameY = 4;
		IMAGEMANAGER->frameRender(TEXT("1201-1208_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1206:
		frameX = 0;
		frameY = 5;
		IMAGEMANAGER->frameRender(TEXT("1201-1208_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1207:
		frameX = 1;
		frameY = 0;
		IMAGEMANAGER->frameRender(TEXT("1201-1208_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1208:
		frameX = 1;
		frameY = 1;
		IMAGEMANAGER->frameRender(TEXT("1201-1208_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1301:
		frameX = 0;
		frameY = 0;
		IMAGEMANAGER->frameRender(TEXT("1301-1303_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1302:
		frameX = 0;
		frameY = 1;
		IMAGEMANAGER->frameRender(TEXT("1301-1303_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1303:
		frameX = 0;
		frameY = 2;
		IMAGEMANAGER->frameRender(TEXT("1301-1303_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1401:
		frameX = 0;
		frameY = 0;
		IMAGEMANAGER->frameRender(TEXT("1401-1404_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1402:
		frameX = 0;
		frameY = 1;
		IMAGEMANAGER->frameRender(TEXT("1401-1404_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1403:
		frameX = 0;
		frameY = 2;
		IMAGEMANAGER->frameRender(TEXT("1401-1404_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1404:
		frameX = 0;
		frameY = 3;
		IMAGEMANAGER->frameRender(TEXT("1401-1404_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1501:
		if (playgame != NULL)
		{
			if (playgame->getSwitch_Lightning())
			{
				frameX = 0;
				frameY = 0;
				IMAGEMANAGER->frameRender(TEXT("1501-1504_Block"), _hdc, x, y, frameX, frameY);
			}
			else
			{
				frameX = 0;
				frameY = 0;
				IMAGEMANAGER->frameRender(TEXT("1501-1504_Block_ani"), _hdc, x, y, frameX, frameY);
			}
		}
		else
		{
			frameX = 0;
			frameY = 0;
			IMAGEMANAGER->frameRender(TEXT("1501-1504_Block"), _hdc, x, y, frameX, frameY);
		}
		break;

	case 1502:
		if (playgame != NULL)
		{
			if (playgame->getSwitch_Lightning())
			{
				frameX = 0;
				frameY = 1;
				IMAGEMANAGER->frameRender(TEXT("1501-1504_Block"), _hdc, x, y, frameX, frameY);
			}
			else
			{
				frameX = 0;
				frameY = 1;
				IMAGEMANAGER->frameRender(TEXT("1501-1504_Block_ani"), _hdc, x, y, frameX, frameY);
			}
		}
		else
		{
			frameX = 0;
			frameY = 1;
			IMAGEMANAGER->frameRender(TEXT("1501-1504_Block"), _hdc, x, y, frameX, frameY);
		}
		break;

	case 1503:
		if (playgame != NULL)
		{
			if (playgame->getSwitch_Lightning())
			{
				frameX = 0;
				frameY = 2;
				IMAGEMANAGER->frameRender(TEXT("1501-1504_Block"), _hdc, x, y, frameX, frameY);
			}
			else
			{
				frameX = 0;
				frameY = 2;
				IMAGEMANAGER->frameRender(TEXT("1501-1504_Block_ani"), _hdc, x, y, frameX, frameY);
			}
		}
		else
		{
			frameX = 0;
			frameY = 2;
			IMAGEMANAGER->frameRender(TEXT("1501-1504_Block"), _hdc, x, y, frameX, frameY);
		}
		break;

	case 1504:
		if (playgame != NULL)
		{
			if (playgame->getSwitch_Lightning())
			{
				frameX = 0;
				frameY = 3;
				IMAGEMANAGER->frameRender(TEXT("1501-1504_Block"), _hdc, x, y, frameX, frameY);
			}
			else
			{
				frameX = 0;
				frameY = 3;
				IMAGEMANAGER->frameRender(TEXT("1501-1504_Block_ani"), _hdc, x, y, frameX, frameY);
			}
		}
		else
		{
			frameX = 0;
			frameY = 3;
			IMAGEMANAGER->frameRender(TEXT("1501-1504_Block"), _hdc, x, y, frameX, frameY);
		}
		break;

	case 1601:
		frameX = 0;
		frameY = 0;
		IMAGEMANAGER->frameRender(TEXT("1601-1604_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1602:
		frameX = 0;
		frameY = 1;
		IMAGEMANAGER->frameRender(TEXT("1601-1604_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1603:
		frameX = 0;
		frameY = 2;
		IMAGEMANAGER->frameRender(TEXT("1601-1604_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1604:
		frameX = 0;
		frameY = 3;
		IMAGEMANAGER->frameRender(TEXT("1601-1604_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1701:
		frameX = 0;
		frameY = 0;
		IMAGEMANAGER->frameRender(TEXT("1701_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1801:
		frameX = 0;
		frameY = 0;
		IMAGEMANAGER->frameRender(TEXT("1801-1804_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1802:
		frameX = 0;
		frameY = 1;
		IMAGEMANAGER->frameRender(TEXT("1801-1804_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1803:
		frameX = 0;
		frameY = 2;
		IMAGEMANAGER->frameRender(TEXT("1801-1804_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1804:
		frameX = 0;
		frameY = 3;
		IMAGEMANAGER->frameRender(TEXT("1801-1804_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1901:
		frameX = 0;
		frameY = 0;
		IMAGEMANAGER->frameRender(TEXT("1901-1902_Block"), _hdc, x, y, frameX, frameY);
		break;

	case 1902:
		frameX = 0;
		frameY = 1;
		IMAGEMANAGER->frameRender(TEXT("1901-1902_Block"), _hdc, x, y, frameX, frameY);
		break;
	}
}

void Block::moveTop(bool _loop)
{
	stat = tempOff;
	useUpdate = true;
	y -= height;
	maxTimer = 1.2;
	currentTimer = maxTimer;
	updateRect();
	loop = _loop;
}

void Block::moveLeft(bool _loop)
{
	stat = tempOff;
	useUpdate = true;
	x -= width;
	maxTimer = 1.2;
	currentTimer = maxTimer;
	updateRect();
	loop = _loop;
}

void Block::moveRight(bool _loop)
{
	stat = tempOff;
	useUpdate = true;
	x += width;
	maxTimer = 1.2;
	currentTimer = maxTimer;
	updateRect();
	loop = _loop;
}

void Block::moveBottom(bool _loop)
{
	stat = tempOff;
	useUpdate = true;
	y += height;
	maxTimer = 1.2;
	currentTimer = maxTimer;
	updateRect();
	loop = _loop;
}

void Block::grabBlockBottom()
{
	if (tempBlock != NULL)
	{
		tempBlock->setX(x);
		tempBlock->setY(y + height);
		tempBlock->updateRect();
	}
}

void Block::grabBlockLeft()
{
	if (tempBlock != NULL)
	{
		tempBlock->setX(x - width);
		tempBlock->setY(y);
		tempBlock->updateRect();
	}
}

void Block::grabBlockRight()
{
	if (tempBlock != NULL)
	{
		tempBlock->setX(x + width);
		tempBlock->setY(y);
		tempBlock->updateRect();
	}
}

void Block::pushBlockTop()
{
	if (canMoveTop)
	{
		y -= 50;
		updateRect();
	}
}

void Block::pushBlockLeft()
{
	if (canMoveLeft)
	{
		x -= 50;
		updateRect();
	}
}

void Block::pushBlockRight()
{
	if (canMoveRight)
	{
		x += 50;
		updateRect();
	}
}

void Block::pushBlockBottom()
{
	if (canMoveBottom)
	{
		y += 50;
		updateRect();
	}
}


