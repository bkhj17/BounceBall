#include "BounceBallHeader.h"
#include "PlayGame.h"

PlayGame::PlayGame()
{
}


PlayGame::~PlayGame()
{
}

HRESULT PlayGame::init()
{
	GetClientRect(g_hWnd, &rcClient);

	// 레벨 정보 초기화
	switch_Lightning = true;
	switch_Green = false;
	switch_Orange = false;
	switch_Star = false;

	// 총알 초기화
	for (int i = 0; i < MAXBULLET; i++)
	{
		bullet[i].init(505);
	}

	// 플레이어 초기화, 블록 초기화
	createLevel();

	// 타이머 초기화
	initTimer = 0;

	return S_OK;
}

void PlayGame::release()
{
}

void PlayGame::update()
{

	//나가기 버튼
	if (KEYMANAGER->isOnceKeyUp(VK_BACK)) {
		if (_tcscmp(TEXT("Test"), _fileNow) == 0)
		{
			SCENEMANAGER->ChangeScene(TEXT("editerMode"));
			EDITER->load(TEXT("Stage\\Test"), MAX_X, MAX_Y, block);
		}
		else {
			SCENEMANAGER->ChangeScene(TEXT("levelSelect"));
		}
	}
	
	// 플레이어 업데이트
	playerBall.update();
	if (playerBall.getStat() == dead)
	{
		initTimer += 1;
		if (initTimer >= 50)
		{
			init();
		}
	}

	// 모든 블럭 업데이트
	for (int x = 0; x < MAX_X; x++)
	{
		for (int y = 0; y < MAX_Y; y++)
		{
			if (!block[x][y].isValid())
				continue;

			if (!block[x][y].getUseUpdate())
				continue;
			block[x][y].update();
		}
	}

	// 모든 총알 업데이트
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (!bullet[i].getValid())
			continue;
		bullet[i].update();
	}
	
	// 플레이어-블럭충돌 검사
	checkCollision_PlayerToBlock();

	// 플레이어-총알 충돌검사
	checkCollision_PlayerToBullet();

	// 블럭-블럭 충돌검사
	checkCollision_BlockToBlock();

	// 총알-블럭 충돌검사
	checkCollision_BulletToBlock();
	
	// 다른 블럭과 상호작용하기 위해 다른 블록 주소 저장
	setTempBlock();
	setTempBlock2();


	//승리 검사 : 처리가 안된 별이 존재하는지(100으로 나눈 수가 1인 블록이 valid)
	bool win = true;
	for (int x = 0; x < MAX_X; x++)
	{
		for (int y = 0; y < MAX_Y; y++)
		{
			//없어지지 않은 별이 존재한다면
			if ((int)(block[x][y].getIndex() / 100) == 1 && block[x][y].isValid())
				win = false;	//승리하지 않음
		}
	}
	//승리처리
	if (win)
	{
		initTimer += 1;
		if (initTimer >= 50) {
			//테스트모드
			if (_tcscmp(TEXT("Test"), _fileNow) == 0)
			{
				EDITER->load(TEXT("Stage\\Test"), MAX_X, MAX_Y, block);
				SCENEMANAGER->ChangeScene(TEXT("editerMode"));
			}
			//일반 게임 진행
			else
			{
				vector<pair<string, bool>>::iterator it_vStg = _vStage.begin();	//현재 스테이지

				for (; it_vStg != _vStage.end(); it_vStg++) {
					if (_tcscmp(it_vStg->first.c_str(), _fileNow) == 0) {
						it_vStg++;
						break;
					}
				}													//의 다음 스테이지
				if (it_vStg != _vStage.end())									//만약 다음 포인터가 맵의 마지막이 아니라면
					it_vStg->second = true;									//의 잠금을 해제
				SCENEMANAGER->ChangeScene(TEXT("levelSelect"));				//후 레벨 선택으로 돌아감
			}
		}
	}


}

void PlayGame::render()
{
	// 바탕화면 렌더링
	IMAGEMANAGER->render(TEXT("BackGround_game"), getMemDC());

	TIMEMANAGER->render(getMemDC());
	

	// 모든 불렛 렌더링
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (!bullet[i].getValid())
			continue;
		bullet[i].render(getMemDC());
	}

	// 모든 블럭 렌더링
	for (int x = 0; x < MAX_X; x++)
	{
		for (int y = 0; y < MAX_Y; y++)
		{
			if (!block[x][y].isValid())
				continue;
			if (!block[x][y].getIsRender())
				continue;
			block[x][y].render(getMemDC());
		}
	}

	// 플레이어공 렌더링
	if (playerBall.getVisible())
		playerBall.render(getMemDC());
}

void PlayGame::createLevel()
{
	for (int x = 0; x < MAX_X; x++)
	{
		for (int y = 0; y < MAX_Y; y++)
		{
			block[x][y].setX(x * 50);
			block[x][y].setY(y * 50);
			block[x][y].updateRect();
			block[x][y].setPlayGame(this);
			block[x][y].setPlayerBall(&playerBall);
			block[x][y].init(0, false);
		}
	}
	playerBall.setRadius(12.5);

	TCHAR fileName[128];
	_stprintf_s(fileName, _countof(fileName), TEXT("Stage\\%s"), _fileNow);
	EDITER->load(fileName, MAX_X, MAX_Y, block);

	// 플레이어 초기화 : 볼 블록(시작위치)을 받아온다 + 스위치 설정
	for (int x = 0; x < MAX_X; x++)
	{
		for (int y = 0; y < MAX_Y; y++)
		{
			if (block[x][y].getIndex() == 001)
			{
				playerBall.init(x, y);
				playerBall.setPlayGame(this);
				break;
			}

			if (block[x][y].getIndex() == 508)
			{
				switch_Lightning = false;
			}
			if (block[x][y].getIndex() == 518)
			{
				switch_Green = true;
			}
			if (block[x][y].getIndex() == 520)
			{
				switch_Orange = true;
			}
		}
	}

	// 블럭끼리 상호작용을 하기 위해 주소를 미리 넣어줌
	{
		// 블랙홀(네모)
		for (int x = 0; x < MAX_X; x++)
		{
			for (int y = 0; y < MAX_Y; y++)
			{
				if (block[x][y].getIndex() == 509)
					block[x][y].setTempBlock(findBlock(510));
			}
		}

		//블랙홀(원)
		for (int x = 0; x < MAX_X; x++)
		{
			for (int y = 0; y < MAX_Y; y++)
			{
				if (block[x][y].getIndex() == 511)
					block[x][y].setTempBlock(findBlock(512));
			}
		}
	}

	// 총알을 사용하는 블럭일 경우 총알 주소를 미리 넣어줌
	for (int x = 0; x < MAX_X; x++)
	{
		for (int y = 0; y < MAX_Y; y++)
		{
			if (!block[x][y].getUseBullet()) //
				continue;

			for (int i = 0; i < MAXBULLET; i++)
			{
				block[x][y].init(&bullet[i], i);
			}

			if (block[x][y].getIndex() == 1001)
				block[x][y].createBullet();
			else if (block[x][y].getIndex() == 1002)
				block[x][y].createBullet();
			else if (block[x][y].getIndex() == 1003)
				block[x][y].createBullet();
			else if (block[x][y].getIndex() == 1004)
				block[x][y].createBullet();

			else if (block[x][y].getIndex() == 1101)
				block[x][y].createBullet();
			else if (block[x][y].getIndex() == 1102)
				block[x][y].createBullet();
			else if (block[x][y].getIndex() == 1103)
				block[x][y].createBullet();
			else if (block[x][y].getIndex() == 1104)
				block[x][y].createBullet();
			else {}
		}
	}
}

void PlayGame::checkCollision_PlayerToBlock()
{
	for (int x = 0; x < MAX_X; x++)
	{
		for (int y = 0; y < MAX_Y; y++)
		{
			if (!block[x][y].isValid()) //블록이 유효할때만 검사
				continue;
			if (!block[x][y].getIsCollision_PlayerToBlock()) //플레이어와 부딪히지 않는 블럭이면 무시
				continue;

			POINT ptBall = { playerBall.getX(), playerBall.getY() };
			RECT rcBlock = block[x][y].getRect();

			RECT rcTop = RectMakeCenter((rcBlock.left + rcBlock.right) / 2, rcBlock.top - playerBall.getRadius() / 2 + 10, rcBlock.right - rcBlock.left + playerBall.getRadius() * 2 - 10, playerBall.getRadius() + 20);
			RECT rcBottom = RectMakeCenter((rcBlock.left + rcBlock.right) / 2, rcBlock.bottom + playerBall.getRadius() / 2, rcBlock.right - rcBlock.left + playerBall.getRadius() * 2 - 10, playerBall.getRadius());
			RECT rcLeft = RectMake(rcBlock.left - playerBall.getRadius(), rcBlock.top, playerBall.getRadius(), rcBlock.bottom - rcBlock.top);
			RECT rcRight = RectMake(rcBlock.right, rcBlock.top, playerBall.getRadius(), rcBlock.bottom - rcBlock.top);

			int nFace = 0;

			if (PtInRect(&rcTop, ptBall)) //윗면과 충둘
				nFace = 1;
			if (PtInRect(&rcLeft, ptBall)) //좌면과 충둘
				nFace = 2;
			if (PtInRect(&rcRight, ptBall)) //우면과 충둘
				nFace = 3;
			if (PtInRect(&rcBottom, ptBall)) //밑면과 충둘
				nFace = 4;

			if (nFace)
				playerBall.collision(&block[x][y], nFace);
		}
	}
}

void PlayGame::checkCollision_PlayerToBullet()
{
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (!bullet[i].getValid())
			continue;

		POINT ptBall = { playerBall.getX(),playerBall.getY() };
		RECT rcBlock = bullet[i].getRect();

		RECT rcTop = RectMakeCenter((rcBlock.left + rcBlock.right) / 2, rcBlock.top - playerBall.getRadius() / 2, rcBlock.right - rcBlock.left + playerBall.getRadius() * 2 - 10, playerBall.getRadius());
		RECT rcBottom = RectMakeCenter((rcBlock.left + rcBlock.right) / 2, rcBlock.bottom + playerBall.getRadius() / 2, rcBlock.right - rcBlock.left + playerBall.getRadius() * 2 - 10, playerBall.getRadius());
		RECT rcLeft = RectMake(rcBlock.left - playerBall.getRadius(), rcBlock.top, playerBall.getRadius(), rcBlock.bottom - rcBlock.top);
		RECT rcRight = RectMake(rcBlock.right, rcBlock.top, playerBall.getRadius(), rcBlock.bottom - rcBlock.top);

		int nFace = 0;

		if (PtInRect(&rcTop, ptBall)) //윗면과 충둘
			nFace = 1;
		if (PtInRect(&rcLeft, ptBall)) //좌면과 충둘
			nFace = 2;
		if (PtInRect(&rcRight, ptBall)) //우면과 충둘
			nFace = 3;
		if (PtInRect(&rcBottom, ptBall)) //밑면과 충둘
			nFace = 4;

		if (nFace)
			playerBall.collisionToBullet(&bullet[i], nFace);
	}
}

void PlayGame::checkCollision_BlockToBlock()
{
	for (int x = 0; x < MAX_X; x++)
	{
		for (int y = 0; y < MAX_Y; y++)
		{
			if (!block[x][y].isValid()) // 월드에 존재하지 않거나
				continue;
			if (!block[x][y].getUseUpdate()) // 검사하지 않는 블럭이면 생략
				continue;

			for (int x2 = 0; x2 < MAX_X; x2++)
			{
				for (int y2 = 0; y2 < MAX_Y; y2++)
				{

					if (!block[x2][y2].isValid()) //월드에 존재하지 않거나
						continue;
					if (x == x2 && y == y2) //자기 자신이면 생략
						continue;

					RECT rcTemp;
					Block* checkBlock = &block[x][y];
					Block* otherBlock = &block[x2][y2];

					POINT ptTop = { checkBlock->getCenterX(),checkBlock->getCenterY() - 50 };
					POINT ptLeft = { checkBlock->getCenterX() - 50,checkBlock->getCenterY() };
					POINT ptRight = { checkBlock->getCenterX() + 50 ,checkBlock->getCenterY() };
					POINT ptBottom = { checkBlock->getCenterX(),checkBlock->getCenterY() + 50 };

					if (IntersectRect(&rcTemp, &checkBlock->getRect(), &otherBlock->getRect()))
					{
						checkBlock->setOverlaped(true);

						if (!block[x2][y2].getIsCollision_BlockToBlock()) //충돌하지 않는 물체면 생략
							continue;

						if (rcTemp.top == checkBlock->getRect().top) //윗면
							checkBlock->collision(otherBlock, 1);
						if (rcTemp.left == checkBlock->getRect().left) //왼쪽면
							checkBlock->collision(otherBlock, 2);
						if (rcTemp.right == checkBlock->getRect().right) //오른쪽면
							checkBlock->collision(otherBlock, 3);
						if (rcTemp.bottom == checkBlock->getRect().bottom) //밑면
							checkBlock->collision(otherBlock, 4);
					}

					if (PtInRect(&otherBlock->getRect(), ptTop)) //위쪽에 다른 블록이 있으면
					{
						checkBlock->setCanMoveTop(false);
					}
					else
					{
						//checkBlock->setCanMoveTop(true); // 버그 : 충돌처리가 안됨
					}

					if (PtInRect(&otherBlock->getRect(), ptLeft)) //왼쪽에 다른 블록이 있으면
					{
						checkBlock->setCanMoveLeft(false);
					}
					else
					{
						//checkBlock->setCanMoveLeft(true); // 버그 : 충돌처리가 안됨
					}

					if (PtInRect(&otherBlock->getRect(), ptRight)) //오른쪽에 다른 블록이 있으면
					{
						checkBlock->setCanMoveRight(false);
					}
					else
					{
						//checkBlock->setCanMoveRight(true); // 버그 : 충돌처리가 안됨
					}

					if (PtInRect(&otherBlock->getRect(), ptBottom)) //아래쪽에 다른 블록이 있으면
					{
						checkBlock->setCanMoveBottom(false);
					}
					else
					{
						//checkBlock->setCanMoveBottom(true); // 버그 : 충돌처리가 안됨
					}
				}
			}
		}
	}
}

void PlayGame::checkCollision_BulletToBlock()
{
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (!bullet[i].getValid())
			continue;

		for (int x = 0; x < MAX_X; x++)
		{
			for (int y = 0; y < MAX_Y; y++)
			{
				if (!block[x][y].isValid())
					continue;
				if (!block[x][y].getIsCollision_BulletToBlock())
					continue;
				if (bullet[i].getSrcBlock() == &block[x][y]) //소스블럭이면 무시
					continue;

				RECT rcTemp;
				RECT rcBullet = bullet[i].getRect();
				RECT rcBlock = block[x][y].getRect();

				if (IntersectRect(&rcTemp, &rcBullet, &rcBlock))
				{
					bullet[i].collision(&block[x][y]);

					if (rcTemp.bottom - rcTemp.top == rcBlock.bottom - rcBlock.top || rcTemp.right - rcTemp.left == rcBlock.right - rcBlock.left) //collision이 여러번 호출되는 것을 방지
					{
						block[x][y].collisionToBullet(&bullet[i]);
					}
					else
					{
						if (rcTemp.top == rcBlock.top) //윗면
							block[x][y].collisionToBullet(&bullet[i], 1);
						if (rcTemp.left == rcBlock.left) //왼쪽면
							block[x][y].collisionToBullet(&bullet[i], 2);
						if (rcTemp.right == rcBlock.right) //오른쪽면
							block[x][y].collisionToBullet(&bullet[i], 3);
						if (rcTemp.bottom == rcBlock.bottom) //밑면
							block[x][y].collisionToBullet(&bullet[i], 4);
					}
				}
			}
		}
	}
}

void PlayGame::setTempBlock()
{
	//1번째 블록
	for (int x = 0; x < MAX_X; x++)
	{
		for (int y = 0; y < MAX_Y; y++)
		{
			if (!block[x][y].isValid()) // 월드에 존재하지 않거나
				continue;
			if (!block[x][y].getUseUpdate()) // 검사하지 않는 블럭이면 생략
				continue;

			float length = WINSIZEX;

			//2번째 블록
			for (int x2 = 0; x2 < MAX_X; x2++)
			{
				for (int y2 = 0; y2 < MAX_Y; y2++)
				{
					if (!block[x][y].getUseUpdate()) //업데이트를 쓰지 않거나
						continue;
					if (!block[x2][y2].isValid()) //월드에 존재하지 않거나
						continue;
					if (!block[x2][y2].getIsCollision_BlockToBlock()) //충돌하지 않는 물체거나
						continue;
					if (x == x2 && y == y2) //자기 자신이면 생략
						continue;

					float templength = WINSIZEX;

					Block* source = &block[x][y];
					Block* dest = &block[x2][y2];

					//윗쪽 레이저 검사
					if (block[x][y].getIndex() == 1601 || block[x][y].getIndex() == 1001 || block[x][y].getIndex() == 1101) 
					{
						//레이저에 안 맞는 위치면 넘기기
						//레이저 X값이 목표에 맞지 않음
						if(source->getCenterX() > dest->getRect().right || source->getCenterX() < dest->getRect().left)
							continue;
						//쏘는 위치가 맞을 위치보다 위
						if (source->getCenterY() < dest->getCenterY()) 
							continue;
						//맞는 위치라면 그 블록까지의 거리를 저장
						templength = UTIL::getDistance(dest->getX(), dest->getY(), source->getX(), source->getY());
					}

					//오른쪽 레이저 검사
					else if (block[x][y].getIndex() == 1301  || block[x][y].getIndex() == 1602 || block[x][y].getIndex() == 1002 || block[x][y].getIndex() == 1102 || block[x][y].getIndex() == 1802 || block[x][y].getIndex() == 1803)
					{
						//레이저에 안 맞는 위치면 넘기기
						//레이저 Y값이 목표에 맞지 않음
						if (source->getCenterY() > dest->getRect().bottom || source->getCenterY() < dest->getRect().top)
							continue;
						//쏘는 위치가 맞을 위치보다 오른쪽
						if (source->getCenterX() > dest->getCenterX())
							continue;
						//맞는 위치라면 그 블록까지의 거리를 저장
						templength = UTIL::getDistance(dest->getX(), dest->getY(), source->getX(), source->getY());
					}

					//왼쪽 레이저 검사
					else if (block[x][y].getIndex() == 1302 || block[x][y].getIndex() == 1604 || block[x][y].getIndex() == 1004 || block[x][y].getIndex() == 1104 || block[x][y].getIndex() == 1801 || block[x][y].getIndex() == 1804)
					{
						//레이저에 안 맞는 위치면 넘기기
						//레이저 Y값이 목표에 맞지 않음
						if (source->getCenterY() > dest->getRect().bottom || source->getCenterY() < dest->getRect().top)
							continue;
						//쏘는 위치가 맞을 위치보다 왼쪽
						if (source->getCenterX() < dest->getCenterX())
							continue;
						//맞는 위치라면 그 블록까지의 거리를 저장
						templength = UTIL::getDistance(dest->getX(), dest->getY(), source->getX(), source->getY());
					}
					//밑쪽 레이저 검사
					else if (block[x][y].getIndex() == 1303 || block[x][y].getIndex() == 1603 || block[x][y].getIndex() == 1003 || block[x][y].getIndex() == 1103)
					{
						//레이저에 안 맞는 위치면 넘기기
						//레이저 X값이 목표에 맞지 않음
						if (source->getCenterX() > dest->getRect().right || source->getCenterX() < dest->getRect().left)
							continue;
						//쏘는 위치가 맞을 위치보다 아래
						if (source->getCenterY() > dest->getCenterY())
							continue;
						//맞는 위치라면 그 블록까지의 거리를 저장
						templength = UTIL::getDistance(dest->getX(), dest->getY(), source->getX(), source->getY());
					}
					else {}

					if (templength < length)
					{
						length = templength;
						source->setTempBlock(dest);
					}	
				}
			}
		}
	}
}

void PlayGame::setTempBlock2()
{
	for (int x = 0; x < MAX_X; x++)
	{
		for (int y = 0; y < MAX_Y; y++)
		{
			if (!block[x][y].isValid()) // 월드에 존재하지 않거나
				continue;
			if (!block[x][y].getUseUpdate()) // 검사하지 않는 블럭이면 생략
				continue;
			float length = WINSIZEX;

			for (int x2 = 0; x2 < MAX_X; x2++)
			{
				for (int y2 = 0; y2 < MAX_Y; y2++)
				{
					if (!block[x][y].getUseUpdate()) //업데이트를 쓰지 않거나
						continue;
					if (!block[x2][y2].isValid()) //월드에 존재하지 않거나
						continue;
					if (!block[x2][y2].getIsCollision_BlockToBlock()) //충돌하지 않는 물체거나
						continue;
					if (x == x2 && y == y2) //자기 자신이면 생략
						continue;

					//레이저 길이 최대치
					float templength = WINSIZEX;

					Block* source = &block[x][y];
					Block* dest = &block[x2][y2];

					if (block[x][y].getIndex() == 1801 || block[x][y].getIndex() == 1802) //윗쪽 레이저 검사
					{
						//레이저에 안 맞는 위치면 넘기기
						//레이저 X값이 목표에 맞지 않음
						if (source->getCenterX() > dest->getRect().right || source->getCenterX() < dest->getRect().left)
							continue;
						//쏘는 위치가 맞을 위치보다 위
						if (source->getCenterY() < dest->getCenterY())
							continue;
						//맞는 위치라면 그 블록까지의 거리를 저장
						templength = UTIL::getDistance(dest->getX(), dest->getY(), source->getX(), source->getY());
					}

					if (block[x][y].getIndex() == 1803 || block[x][y].getIndex() == 1804) //밑쪽 레이저 검사
					{
						//레이저에 안 맞는 위치면 넘기기
						//레이저 X값이 목표에 맞지 않음
						if (source->getCenterX() > dest->getRect().right || source->getCenterX() < dest->getRect().left)
							continue;
						//쏘는 위치가 맞을 위치보다 아래
						if (source->getCenterY() > dest->getCenterY())
							continue;
						//맞는 위치라면 그 블록까지의 거리를 저장
						templength = UTIL::getDistance(dest->getX(), dest->getY(), source->getX(), source->getY());
					}

					if (templength < length)
					{
						length = templength;
						source->setTempBlock2(dest);
					}
				}
			}
		}
	}
}

Block * PlayGame::findBlock(int _findBoxindex, int _arrIndex)
{
	int arrIndex = 0;
	for (int x = 0; x < MAX_X; x++)
	{
		for (int y = 0; y < MAX_Y; y++)
		{
			if (block[x][y].getIndex() == _findBoxindex)
			{
				if (arrIndex == _arrIndex)
				{
					return &block[x][y];
				}
				arrIndex++;
			}
		}
	}
	return nullptr;
}
