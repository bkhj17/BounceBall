#include "Ball.h"
#include "PlayGame.h"

Ball::Ball()
{
}


Ball::~Ball()
{
}

void Ball::init(int _x, int _y)
{
	x = _x * 50 + 25;
	y = _y * 50 + 25;
	startX = x;
	startY = y;
	Xspeed = 0.f;
	Yspeed = 0.f;

	visible = true;
	stat = idle;
	itemStat = none;
}

void Ball::update()
{
	if (y >= WINSIZEY + 100)
	{
		die();
	}

	if (stat == idle)
	{
		// ÁÂ¿ì Á¶ÀÛ
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			stat = moving;
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			stat = moving;
		}

		// ÀÌµ¿ ÀúÇ×
		if (Xspeed > 0)
			Xspeed -= 0.1;
		if (Xspeed < 0)
			Xspeed += 0.1;
		if (-0.1 <= Xspeed && Xspeed <= 0.1) //À×¿© ½ºÇÇµå Á¦°Å
			Xspeed = 0;
	}

	if (stat == moving)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			if (Xspeed > -MAXINPUTSPEED)
				Xspeed -= 0.2;
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			if (Xspeed < MAXINPUTSPEED)
				Xspeed += 0.2;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			stat = idle;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			stat = idle;
		}
	}

	if (stat == idle || stat == moving)
	{
		Yspeed += GRAVITY;
	}

	if (stat == flying)
	{
		if (Xspeed > 0)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
			{
				Xspeed -= 5;
				stat = idle;
			}
		}
		if (Xspeed < 0)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
			{
				Xspeed += 5;
				stat = idle;
			}
		}
	}

	if (stat == climbing)
	{
		Yspeed = 1;
		if (KEYMANAGER->isOnceKeyUp(VK_SPACE))
		{
			Xspeed = cosf(rouletteAngle) * 5;
			Yspeed = -sinf(rouletteAngle) * 10;
			stat = idle;
			SOUNDMANAGER->Play(TEXT("BounceSound"), DEFAULT_VOLUME);
		}
	}

	if (stat == rouletteMode)
	{
		rouletteAngle -= PI / 180 * 2;

		if (KEYMANAGER->isOnceKeyUp(VK_SPACE)) //¾ÈÇÏ¸é ¹Ù·Î ¹ß»çµÊ
			inputLock = false;

		if (!inputLock)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				Xspeed = cosf(rouletteAngle) * 10;
				Yspeed = -sinf(rouletteAngle) * 10;
				stat = idle;
				SOUNDMANAGER->Play(TEXT("BounceSound"), DEFAULT_VOLUME);
			}
		}
	}

	if (stat == rouletteMode4)
	{
		if (tempBlock != NULL)
		{
			// ·ê·¿ ¾Ö´Ï¸ÞÀÌ¼Ç
			visible = false;
			tempBlock->setAniPlay(true);
			tempTime++;
			float deltaTime = 15;

			if (0 * deltaTime <= tempTime && tempTime < 1 * deltaTime)
			{
				tempBlock->setImageFrame(0, 0);
				if (tempTime == 0 * deltaTime)
					SOUNDMANAGER->Play(TEXT("RouletteSound"), DEFAULT_VOLUME);
			}
			if (1 * deltaTime <= tempTime && tempTime < 2 * deltaTime)
			{
				tempBlock->setImageFrame(1, 0);
				if (tempTime == 1 * deltaTime)
					SOUNDMANAGER->Play(TEXT("RouletteSound"), DEFAULT_VOLUME);
			}
			if (2 * deltaTime <= tempTime && tempTime < 3 * deltaTime)
			{
				tempBlock->setImageFrame(2, 0);
				if (tempTime == 2 * deltaTime)
					SOUNDMANAGER->Play(TEXT("RouletteSound"), DEFAULT_VOLUME);
			}
			if (3 * deltaTime <= tempTime && tempTime < 4 * deltaTime)
			{
				tempBlock->setImageFrame(3, 0);
				if (tempTime == 3 * deltaTime)
					SOUNDMANAGER->Play(TEXT("RouletteSound"), DEFAULT_VOLUME);
			}
			if (4 * deltaTime <= tempTime)
			{
				tempTime = -1;
			}

			// ¹ß»ç
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				visible = true;
				tempBlock->setAniPlay(false);
				SOUNDMANAGER->Play(TEXT("BounceSound"), DEFAULT_VOLUME);

				if (tempBlock->getFrameX() == 0)
				{
					x = tempBlock->getCenterX();
					y = tempBlock->getCenterY() - 50;

					stat = flying;
					Xspeed = 0;
					Yspeed = -7.5;
				}
				if (tempBlock->getFrameX() == 1)
				{
					x = tempBlock->getCenterX() + 50;
					y = tempBlock->getCenterY();

					stat = flying;
					Xspeed = 7.5;
					Yspeed = 0;
				}
				if (tempBlock->getFrameX() == 2)
				{
					x = tempBlock->getCenterX();
					y = tempBlock->getCenterY() + 50;

					stat = flying;
					Xspeed = 0;
					Yspeed = 7.5;
				}
				if (tempBlock->getFrameX() == 3)
				{
					x = tempBlock->getCenterX() - 50;
					y = tempBlock->getCenterY();

					stat = flying;
					Xspeed = -7.5;
					Yspeed = 0;
				}
			}
		}
	}

	if (stat == rouletteMode8)
	{
		if (tempBlock != NULL)
		{
			// ·ê·¿ ¾Ö´Ï¸ÞÀÌ¼Ç
			visible = false;
			tempBlock->setAniPlay(true);
			tempTime++;
			float deltaTime = 10;

			if (0 * deltaTime <= tempTime && tempTime < 1 * deltaTime)
			{
				tempBlock->setImageFrame(0, 0);

				if(tempTime == 0 * deltaTime)
					SOUNDMANAGER->Play(TEXT("RouletteSound"), DEFAULT_VOLUME);
			}
			if (1 * deltaTime <= tempTime && tempTime < 2 * deltaTime)
			{
				tempBlock->setImageFrame(1, 0);

				if (tempTime == 1 * deltaTime)
					SOUNDMANAGER->Play(TEXT("RouletteSound"), DEFAULT_VOLUME);
			}
			if (2 * deltaTime <= tempTime && tempTime < 3 * deltaTime)
			{
				tempBlock->setImageFrame(2, 0);

				if (tempTime == 2 * deltaTime)
					SOUNDMANAGER->Play(TEXT("RouletteSound"), DEFAULT_VOLUME);
			}
			if (3 * deltaTime <= tempTime && tempTime < 4 * deltaTime)
			{
				tempBlock->setImageFrame(3, 0);

				if (tempTime == 3 * deltaTime)
					SOUNDMANAGER->Play(TEXT("RouletteSound"), DEFAULT_VOLUME);
			}
			if (4 * deltaTime <= tempTime && tempTime < 5 * deltaTime)
			{
				tempBlock->setImageFrame(0, 1);

				if (tempTime == 4 * deltaTime)
					SOUNDMANAGER->Play(TEXT("RouletteSound"), DEFAULT_VOLUME);
			}
			if (5 * deltaTime <= tempTime && tempTime < 6 * deltaTime)
			{
				tempBlock->setImageFrame(1, 1);
				if (tempTime == 5 * deltaTime)
					SOUNDMANAGER->Play(TEXT("RouletteSound"), DEFAULT_VOLUME);
			}
			if (6 * deltaTime <= tempTime && tempTime < 7 * deltaTime)
			{
				tempBlock->setImageFrame(2, 1);
				if (tempTime == 6 * deltaTime)
					SOUNDMANAGER->Play(TEXT("RouletteSound"), DEFAULT_VOLUME);
			}
			if (7 * deltaTime <= tempTime && tempTime < 8 * deltaTime)
			{
				tempBlock->setImageFrame(3, 1);
				if (tempTime == 7 * deltaTime)
					SOUNDMANAGER->Play(TEXT("RouletteSound"), DEFAULT_VOLUME);
			}
			if (8 * deltaTime <= tempTime)
			{
				tempTime = -1;
			}

			// ¹ß»ç
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				visible = true;
				tempBlock->setAniPlay(false);
				SOUNDMANAGER->Play(TEXT("BounceSound"), DEFAULT_VOLUME);

				if (tempBlock->getFrameX() == 0 && tempBlock->getFrameY() == 0)
				{
					x = tempBlock->getCenterX();
					y = tempBlock->getCenterY() - 50;

					stat = flying;
					Xspeed = 0;
					Yspeed = -7.5;
				}
				if (tempBlock->getFrameX() == 1 && tempBlock->getFrameY() == 0)
				{
					x = tempBlock->getCenterX() + 50;
					y = tempBlock->getCenterY() - 50;

					stat = flying;
					Xspeed = 7.5;
					Yspeed = -7.5;
				}
				if (tempBlock->getFrameX() == 2 && tempBlock->getFrameY() == 0)
				{
					x = tempBlock->getCenterX() + 50;
					y = tempBlock->getCenterY();

					stat = flying;
					Xspeed = 7.5;
					Yspeed = 0;
				}
				if (tempBlock->getFrameX() == 3 && tempBlock->getFrameY() == 0)
				{
					x = tempBlock->getCenterX() + 50;
					y = tempBlock->getCenterY() + 50;

					stat = flying;
					Xspeed = 7.5;
					Yspeed = 7.5;
				}
				if (tempBlock->getFrameX() == 0 && tempBlock->getFrameY() == 1)
				{
					x = tempBlock->getCenterX();
					y = tempBlock->getCenterY() + 50;

					stat = flying;
					Xspeed = 0;
					Yspeed = 7.5;
				}
				if (tempBlock->getFrameX() == 1 && tempBlock->getFrameY() == 1)
				{
					x = tempBlock->getCenterX() - 50;
					y = tempBlock->getCenterY() + 50;

					stat = flying;
					Xspeed = -7.5;
					Yspeed = 7.5;
				}
				if (tempBlock->getFrameX() == 2 && tempBlock->getFrameY() == 1)
				{
					x = tempBlock->getCenterX() - 50;
					y = tempBlock->getCenterY();

					stat = flying;
					Xspeed = -7.5;
					Yspeed = 0;
				}
				if (tempBlock->getFrameX() == 3 && tempBlock->getFrameY() == 1)
				{
					x = tempBlock->getCenterX() - 50;
					y = tempBlock->getCenterY() - 50;

					stat = flying;
					Xspeed = -7.5;
					Yspeed = -7.5;
				}
			}
		}
	}

	if (itemStat == jumpWide)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				Xspeed -= 5;
				Yspeed = -3;
				itemStat = none;
				SOUNDMANAGER->Play(TEXT("BounceSound"), DEFAULT_VOLUME);
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				Xspeed += 5;
				Yspeed = -3;
				itemStat = none;
				SOUNDMANAGER->Play(TEXT("BounceSound"), DEFAULT_VOLUME);
			}
		}
	}
	if (itemStat == jumpHigh)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			Yspeed = -7.5;
			itemStat = none;
			SOUNDMANAGER->Play(TEXT("BounceSound"), DEFAULT_VOLUME);
		}
	}
	if (itemStat == warp)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				x -= 100;
				itemStat = none;
				SOUNDMANAGER->Play(TEXT("BounceSound"), DEFAULT_VOLUME);
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				x += 100;
				itemStat = none;
				SOUNDMANAGER->Play(TEXT("BounceSound"), DEFAULT_VOLUME);
			}
		}
	}
	if (itemStat == shadow)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			x = shadowX;
			y = shadowY;
			itemStat = none;
			SOUNDMANAGER->Play(TEXT("BounceSound"), DEFAULT_VOLUME);
		}
	}
	if (itemStat == roulette)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			itemStat = none;
			stat = rouletteMode;
			rouletteAngle = PI / 2;
			Xspeed = 0;
			Yspeed = 0;
			inputLock = true;
			SOUNDMANAGER->Play(TEXT("BounceSound"), DEFAULT_VOLUME);
		}
	}
	if (itemStat == fly)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				itemStat = none;
				stat = flying;
				Xspeed = -7.5;
				Yspeed = 0;
				SOUNDMANAGER->Play(TEXT("BounceSound"), DEFAULT_VOLUME);
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				itemStat = none;
				stat = flying;
				Xspeed = +7.5;
				Yspeed = 0;
				SOUNDMANAGER->Play(TEXT("BounceSound"), DEFAULT_VOLUME);
			}
		}
	}

	// ÃÖÁ¾ÀÌµ¿
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
}

void Ball::render(HDC _hdc)
{
	if (stat == rouletteMode)
	{
		float x2 = x + cosf(rouletteAngle) * 100;
		float y2 = y - sinf(rouletteAngle) * 100;

		LineMake(_hdc, x, y, x2, y2);
		EllipseMakeCenter(_hdc, x2, y2, 10, 10);
	}

	if (itemStat == none)
		IMAGEMANAGER->frameRender(TEXT("001-008_Ball"), _hdc, x - radius, y - radius, 0, 0);
	if (itemStat == jumpWide)
		IMAGEMANAGER->frameRender(TEXT("001-008_Ball"), _hdc, x - radius, y - radius, 0, 1);
	if (itemStat == jumpHigh)
		IMAGEMANAGER->frameRender(TEXT("001-008_Ball"), _hdc, x - radius, y - radius, 0, 2);
	if (itemStat == warp)
		IMAGEMANAGER->frameRender(TEXT("001-008_Ball"), _hdc, x - radius, y - radius, 0, 3);
	if (itemStat == transparency)
		IMAGEMANAGER->frameRender(TEXT("001-008_Ball"), _hdc, x - radius, y - radius, 1, 0);
	if (itemStat == shadow)
		IMAGEMANAGER->frameRender(TEXT("001-008_Ball"), _hdc, x - radius, y - radius, 1, 1);
	if (itemStat == roulette)
		IMAGEMANAGER->frameRender(TEXT("001-008_Ball"), _hdc, x - radius, y - radius, 1, 2);
	if (itemStat == fly)
		IMAGEMANAGER->frameRender(TEXT("001-008_Ball"), _hdc, x - radius, y - radius, 1, 3);
}

void Ball::collision(Block* _block, int _collisionface)
{
	int n = _block->getIndex();

	switch (n)
	{
	case 101:
		if (itemStat != transparency)
		{
			_block->setValid(false);
			SOUNDMANAGER->Play(TEXT("StarSound"), DEFAULT_VOLUME);
		}
		break;
	case 102:
		if (playGame->getSwitch_Star())
		{
			if (itemStat != transparency)
			{
				_block->setValid(false);
				SOUNDMANAGER->Play(TEXT("StarSound"), DEFAULT_VOLUME);
			}
		}
		break;
	case 103:
		if (itemStat != transparency)
		{
			_block->setValid(false);
			SOUNDMANAGER->Play(TEXT("StarSound"), DEFAULT_VOLUME);
			Yspeed = -8.5;
		}
		break;
	case 201:
	case 202:
	case 203:
	case 204:
	case 205:
	case 206:
	case 207:
	case 208:
	case 209:
	case 210:
	case 211:
	case 212:
	case 213:
	case 214:
	case 215:
	case 1001:
	case 1002:
	case 1003:
	case 1004:
	case 1101:
	case 1102:
	case 1103:
	case 1104:
	case 1501:
	case 1502:
	case 1503:
	case 1504:
	case 1801:
	case 1802:
	case 1803:
	case 1804:
	{
		if (_collisionface == 1) //À­¸é
		{
			collisionTop();
			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}

	case 216:
	{
		if (playGame->getSwitch_Green())
		{
			if (_collisionface == 1) //À­¸é
			{
				collisionTop();
				break;
			}
			if (_collisionface == 2) //ÁÂ¸é
			{
				collisionLeft();
				break;
			}
			if (_collisionface == 3) //¿ì¸é
			{
				collisionRight();
				break;
			}
			if (_collisionface == 4) //¹Ø¸é
			{
				collisionBottom();
				break;
			}
		}
		break;
	}
	case 217:
	{
		if (playGame->getSwitch_Orange())
		{
			if (_collisionface == 1) //À­¸é
			{
				collisionTop();
				break;
			}
			if (_collisionface == 2) //ÁÂ¸é
			{
				collisionLeft();
				break;
			}
			if (_collisionface == 3) //¿ì¸é
			{
				collisionRight();
				break;
			}
			if (_collisionface == 4) //¹Ø¸é
			{
				collisionBottom();
				break;
			}
		}
		break;
	}

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
	{
		if (_collisionface == 1) //À­¸é
		{
			die();
			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}

	case 801:
	case 802:
	case 803:
	case 804:
	case 1901:
	case 1902:
	{
		die();
		break;
	}

	case 401:
	{
		if (_collisionface == 1) //À­¸é
		{
			collisionTop();
			_block->setValid(false);
			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}

	case 501:
	{
		if (_collisionface == 1) //À­¸é
		{
			stat = idle;
			Yspeed = -10.2;
			SOUNDMANAGER->Play(TEXT("BounceSound"), DEFAULT_VOLUME);
			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}

	case 502:
	{
		if (_collisionface == 1) //À­¸é
		{
			x = _block->getCenterX() + 50;
			y = _block->getCenterY();

			stat = flying;
			Xspeed = +7.5;
			Yspeed = 0;
			SOUNDMANAGER->Play(TEXT("BounceSound"), DEFAULT_VOLUME);

			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}

	case 503:
	{
		if (_collisionface == 1) //À­¸é
		{
			x = _block->getCenterX() - 50;
			y = _block->getCenterY();

			stat = flying;
			Xspeed = -7.5;
			Yspeed = 0;
			SOUNDMANAGER->Play(TEXT("BounceSound"), DEFAULT_VOLUME);

			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}

	case 504:
	{
		if (_collisionface == 1) //À­¸é
		{
			collisionTop();
			_block->setUseUpdate(true);
			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}

	case 505:
		break;

	case 506:
	{
		if (_collisionface == 1) //À­¸é
		{
			stat = idle;
			Yspeed = -13;
			_block->setValid(false);
			SOUNDMANAGER->Play(TEXT("BounceSound"), DEFAULT_VOLUME);
			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}

	case 507:
	case 508:
	{
		if (_collisionface == 1) //À­¸é
		{
			playGame->changeSwitch_Lightning();
			collisionTop();
			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}

	case 509:
	{
		if (_block->getTempBlock() != NULL)
		{
			x = _block->getTempBlock()->getCenterX();
			y = _block->getTempBlock()->getCenterY();
		}
		break;
	}

	case 510:
		break;

	case 511:
	{
		if (_block->getTempBlock() != NULL)
		{
			x = _block->getTempBlock()->getCenterX();
			y = _block->getTempBlock()->getCenterY();
		}
		break;
	}

	case 512:
		break;

	case 513:
	{
		x = _block->getCenterX();
		y = _block->getCenterY();

		Xspeed = 0;
		Yspeed = 0;

		stat = rouletteMode4;
		setTempBlock(_block);
		tempTime = 0;
		break;
	}

	case 514:
	{
		if (_collisionface == 1) //À­¸é
		{
			x = _block->getCenterX() + 50;
			y = _block->getCenterY();

			stat = flying;
			Xspeed = +7.5;
			Yspeed = 0;
			SOUNDMANAGER->Play(TEXT("BounceSound"), DEFAULT_VOLUME);

			_block->setValid(false);

			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}

	case 515:
	{
		if (_collisionface == 1) //À­¸é
		{
			x = _block->getCenterX() - 50;
			y = _block->getCenterY();

			stat = flying;
			Xspeed = -7.5;
			Yspeed = 0;
			SOUNDMANAGER->Play(TEXT("BounceSound"), DEFAULT_VOLUME);
			
			_block->setValid(false);

			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}

	case 516:
	{
		x = _block->getCenterX();
		y = _block->getCenterY();

		Xspeed = 0;
		Yspeed = 0;

		stat = rouletteMode8;
		setTempBlock(_block);
		tempTime = 0;
		break;
	}

	case 517: //½ºÀ§Ä¡(³ì)(off)
	case 518: //½ºÀ§Ä¡(³ì)(on)
	{
		if (_collisionface == 1) //À­¸é
		{
			collisionTop();
			playGame->changeSwitch_Green();
			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}

	case 519: //½ºÀ§Ä¡(ÁÖ)(off)
	case 520: //½ºÀ§Ä¡(ÁÖ)(on)
	{
		if (_collisionface == 1) //À­¸é
		{
			collisionTop();
			playGame->changeSwitch_Orange();
			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}

	case 601:
		itemStat = jumpWide;
		_block->setValid(false);
		break;
	case 602:
		itemStat = jumpHigh;
		_block->setValid(false);
		break;
	case 603:
		itemStat = transparency;
		_block->setValid(false);
		break;
	case 604:
		itemStat = none;
		_block->setValid(false);
		break;
	case 605:
		itemStat = warp;
		_block->setValid(false);
		break;
	case 606:
		itemStat = shadow;
		shadowX = _block->getCenterX();
		shadowY = _block->getCenterY();
		_block->setValid(false);
		break;
	case 607:
		itemStat = roulette;
		_block->setValid(false);
		break;
	case 608:
		itemStat = fly;
		_block->setValid(false);
		break;
	case 701:
		if (playGame->getSwitch_Lightning())
		{
			die();
		}
		break;
	case 702:
		break;

	case 704:
	{
		if (_block->getStat() == on)
		{
			if (_collisionface == 1) //À­¸é
			{
				collisionTop();
				break;
			}
			if (_collisionface == 2) //ÁÂ¸é
			{
				collisionLeft();
				break;
			}
			if (_collisionface == 3) //¿ì¸é
			{
				collisionRight();
				break;
			}
			if (_collisionface == 4) //¹Ø¸é
			{
				collisionBottom();
				break;
			}
		}
		break;
	}

	case 705:
	{
		if (_block->getStat() == on)
		{
			die();
		}
		break;
	}

	case 706:
	{
		if (_block->getStat() == off)
		{
			_block->setStat(on);
		}
		if (_block->getStat() == redBlock)
		{
			die();
		}
		if (_block->getStat() == blueBlock)
		{
			if (_collisionface == 1) //À­¸é
			{
				collisionTop();
				break;
			}
			if (_collisionface == 2) //ÁÂ¸é
			{
				collisionLeft();
				break;
			}
			if (_collisionface == 3) //¿ì¸é
			{
				collisionRight();
				break;
			}
			if (_collisionface == 4) //¹Ø¸é
			{
				collisionBottom();
				break;
			}
		}
		break;
	}

	case 707:
		stat = idle;
		Yspeed = -8.5;
		SOUNDMANAGER->Play(TEXT("BounceSound"), DEFAULT_VOLUME);
		break;
	case 708:
		stat = idle;
		Xspeed = 10;
		Yspeed = -1;
		SOUNDMANAGER->Play(TEXT("BounceSound"), DEFAULT_VOLUME);
		break;
	case 709:
		stat = idle;
		Xspeed = -10;
		Yspeed = -1;
		SOUNDMANAGER->Play(TEXT("BounceSound"), DEFAULT_VOLUME);
		break;
	case 710:
		stat = idle;
		Yspeed = 8.5;
		SOUNDMANAGER->Play(TEXT("BounceSound"), DEFAULT_VOLUME);
		break;

	case 901:
	{
		if (_collisionface == 1) //À­¸é
		{
			collisionTop();
			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			stat = climbing;
			rouletteAngle = PI / 2 + PI / 4;
			Xspeed = 0;
			Yspeed = 0;
			x = _block->getCenterX() - 37.5;
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			stat = climbing;
			rouletteAngle = PI / 4;
			Xspeed = 0;
			Yspeed = 0;
			x = _block->getCenterX() + 37.5;
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}

	case 1201:
	{
		if (_collisionface == 1) //À­¸é
		{
			collisionTop();
			_block->moveTop();
			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}
	case 1202:
	{
		if (_collisionface == 1) //À­¸é
		{
			collisionTop();
			_block->moveRight();
			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}
	case 1203:
	{
		if (_collisionface == 1) //À­¸é
		{
			collisionTop();
			_block->moveLeft();
			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}
	case 1204:
	{
		if (_collisionface == 1) //À­¸é
		{
			collisionTop();
			_block->moveBottom();
			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}
	case 1205:
	{
		if (_collisionface == 1) //À­¸é
		{
			collisionTop();
			_block->moveTop(true);
			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}
	case 1206:
	{
		if (_collisionface == 1) //À­¸é
		{
			collisionTop();
			_block->moveRight(true);
			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}
	case 1207:
	{
		if (_collisionface == 1) //À­¸é
		{
			collisionTop();
			_block->moveLeft(true);
			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}
	case 1208:
	{
		if (_collisionface == 1) //À­¸é
		{
			collisionTop();
			_block->moveBottom(true);
			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}
	case 1301:
	{
		if (_collisionface == 1) //À­¸é
		{
			collisionTop();
			_block->grabBlockRight();
			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}

	case 1302:
	{
		if (_collisionface == 1) //À­¸é
		{
			collisionTop();
			_block->grabBlockLeft();
			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}

	case 1303:
	{
		if (_collisionface == 1) //À­¸é
		{
			collisionTop();
			_block->grabBlockBottom();
			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}

	case 1401:
	{
		if (_collisionface == 1) //À­¸é
		{
			collisionTop();
			_block->createBullet(blue);
			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}

	case 1402:
	{
		if (_collisionface == 1) //À­¸é
		{
			collisionTop();
			_block->createBullet(blue);
			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}

	case 1403:
	{
		if (_collisionface == 1) //À­¸é
		{
			collisionTop();
			_block->createBullet(blue);
			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}

	case 1404:
	{
		if (_collisionface == 1) //À­¸é
		{
			collisionTop();
			_block->createBullet(blue);
			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}

	case 1601:
	{
		if (_collisionface == 1) //À­¸é
		{
			collisionTop();
			if (_block->getTempBlock()->getCanMoveTop())
				_block->createBullet(white);
			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}

	case 1602:
	{
		if (_collisionface == 1) //À­¸é
		{
			collisionTop();
			if (_block->getTempBlock()->getCanMoveRight())
				_block->createBullet(white);
			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}

	case 1603:
	{
		if (_collisionface == 1) //À­¸é
		{
			collisionTop();
			if (_block->getTempBlock()->getCanMoveBottom())
				_block->createBullet(white);
			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}

	case 1604:
	{
		if (_collisionface == 1) //À­¸é
		{
			collisionTop();
			if (_block->getTempBlock()->getCanMoveLeft())
				_block->createBullet(white);
			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}
	}
}

void Ball::collisionToBullet(Bullet* _bullet, int _collisionface)
{
	int n = _bullet->getIndex();
	switch (n)
	{
	case 1101:
	case 1102:
	case 1103:
	case 1104:
	case 1601:
	case 1602:
	case 1603:
	case 1604:
	{
		if (_collisionface == 1) //À­¸é
		{
			collisionTop();
			break;
		}
		if (_collisionface == 2) //ÁÂ¸é
		{
			collisionLeft();
			break;
		}
		if (_collisionface == 3) //¿ì¸é
		{
			collisionRight();
			break;
		}
		if (_collisionface == 4) //¹Ø¸é
		{
			collisionBottom();
			break;
		}
		break;
	}

	case 505:
	case 1001:
	case 1002:
	case 1003:
	case 1004:
	case 1401:
	case 1402:
	case 1403:
	case 1404:
	{
		die();
		break;
	}

	}
}

void Ball::collisionTop()
{
	stat = idle;
	Yspeed = -JUMPPOWER;

	if (Xspeed >= 3)
		Xspeed = 3;
	if (Xspeed <= -3)
		Xspeed = -3;
	SOUNDMANAGER->Play(TEXT("BallSound"), DEFAULT_VOLUME);
}

void Ball::collisionLeft()
{
	stat = idle;
	Xspeed = -2;
	SOUNDMANAGER->Play(TEXT("BallSound"), DEFAULT_VOLUME);
}

void Ball::collisionRight()
{
	stat = idle;
	Xspeed = 2;
	SOUNDMANAGER->Play(TEXT("BallSound"), DEFAULT_VOLUME);
}

void Ball::collisionBottom()
{
	stat = idle;
	Yspeed = 0.75;

	if (Xspeed >= 3)
		Xspeed = 3;
	if (Xspeed <= -3)
		Xspeed = -3;
	SOUNDMANAGER->Play(TEXT("BallSound"), DEFAULT_VOLUME);
}

void Ball::die()
{
	stat = dead;
	itemStat = none;
	x = startX;
	y = startY;
	Xspeed = 0;
	Yspeed = 0;
	visible = false;

	//¼Ò¸®
	SOUNDMANAGER->Play(TEXT("DieSound"), DEFAULT_VOLUME);
}