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

	// ���� ���� �ʱ�ȭ
	switch_Lightning = true;
	switch_Green = false;
	switch_Orange = false;
	switch_Star = false;

	// �Ѿ� �ʱ�ȭ
	for (int i = 0; i < MAXBULLET; i++)
	{
		bullet[i].init(505);
	}

	// �÷��̾� �ʱ�ȭ, ��� �ʱ�ȭ
	createLevel();

	// Ÿ�̸� �ʱ�ȭ
	initTimer = 0;

	return S_OK;
}

void PlayGame::release()
{
}

void PlayGame::update()
{

	//������ ��ư
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
	
	// �÷��̾� ������Ʈ
	playerBall.update();
	if (playerBall.getStat() == dead)
	{
		initTimer += 1;
		if (initTimer >= 50)
		{
			init();
		}
	}

	// ��� �� ������Ʈ
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

	// ��� �Ѿ� ������Ʈ
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (!bullet[i].getValid())
			continue;
		bullet[i].update();
	}
	
	// �÷��̾�-���浹 �˻�
	checkCollision_PlayerToBlock();

	// �÷��̾�-�Ѿ� �浹�˻�
	checkCollision_PlayerToBullet();

	// ��-�� �浹�˻�
	checkCollision_BlockToBlock();

	// �Ѿ�-�� �浹�˻�
	checkCollision_BulletToBlock();
	
	// �ٸ� ���� ��ȣ�ۿ��ϱ� ���� �ٸ� ��� �ּ� ����
	setTempBlock();
	setTempBlock2();


	//�¸� �˻� : ó���� �ȵ� ���� �����ϴ���(100���� ���� ���� 1�� ����� valid)
	bool win = true;
	for (int x = 0; x < MAX_X; x++)
	{
		for (int y = 0; y < MAX_Y; y++)
		{
			//�������� ���� ���� �����Ѵٸ�
			if ((int)(block[x][y].getIndex() / 100) == 1 && block[x][y].isValid())
				win = false;	//�¸����� ����
		}
	}
	//�¸�ó��
	if (win)
	{
		initTimer += 1;
		if (initTimer >= 50) {
			//�׽�Ʈ���
			if (_tcscmp(TEXT("Test"), _fileNow) == 0)
			{
				EDITER->load(TEXT("Stage\\Test"), MAX_X, MAX_Y, block);
				SCENEMANAGER->ChangeScene(TEXT("editerMode"));
			}
			//�Ϲ� ���� ����
			else
			{
				vector<pair<string, bool>>::iterator it_vStg = _vStage.begin();	//���� ��������

				for (; it_vStg != _vStage.end(); it_vStg++) {
					if (_tcscmp(it_vStg->first.c_str(), _fileNow) == 0) {
						it_vStg++;
						break;
					}
				}													//�� ���� ��������
				if (it_vStg != _vStage.end())									//���� ���� �����Ͱ� ���� �������� �ƴ϶��
					it_vStg->second = true;									//�� ����� ����
				SCENEMANAGER->ChangeScene(TEXT("levelSelect"));				//�� ���� �������� ���ư�
			}
		}
	}


}

void PlayGame::render()
{
	// ����ȭ�� ������
	IMAGEMANAGER->render(TEXT("BackGround_game"), getMemDC());

	TIMEMANAGER->render(getMemDC());
	

	// ��� �ҷ� ������
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (!bullet[i].getValid())
			continue;
		bullet[i].render(getMemDC());
	}

	// ��� �� ������
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

	// �÷��̾�� ������
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

	// �÷��̾� �ʱ�ȭ : �� ���(������ġ)�� �޾ƿ´� + ����ġ ����
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

	// ������ ��ȣ�ۿ��� �ϱ� ���� �ּҸ� �̸� �־���
	{
		// ��Ȧ(�׸�)
		for (int x = 0; x < MAX_X; x++)
		{
			for (int y = 0; y < MAX_Y; y++)
			{
				if (block[x][y].getIndex() == 509)
					block[x][y].setTempBlock(findBlock(510));
			}
		}

		//��Ȧ(��)
		for (int x = 0; x < MAX_X; x++)
		{
			for (int y = 0; y < MAX_Y; y++)
			{
				if (block[x][y].getIndex() == 511)
					block[x][y].setTempBlock(findBlock(512));
			}
		}
	}

	// �Ѿ��� ����ϴ� ���� ��� �Ѿ� �ּҸ� �̸� �־���
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
			if (!block[x][y].isValid()) //����� ��ȿ�Ҷ��� �˻�
				continue;
			if (!block[x][y].getIsCollision_PlayerToBlock()) //�÷��̾�� �ε����� �ʴ� ���̸� ����
				continue;

			POINT ptBall = { playerBall.getX(), playerBall.getY() };
			RECT rcBlock = block[x][y].getRect();

			RECT rcTop = RectMakeCenter((rcBlock.left + rcBlock.right) / 2, rcBlock.top - playerBall.getRadius() / 2 + 10, rcBlock.right - rcBlock.left + playerBall.getRadius() * 2 - 10, playerBall.getRadius() + 20);
			RECT rcBottom = RectMakeCenter((rcBlock.left + rcBlock.right) / 2, rcBlock.bottom + playerBall.getRadius() / 2, rcBlock.right - rcBlock.left + playerBall.getRadius() * 2 - 10, playerBall.getRadius());
			RECT rcLeft = RectMake(rcBlock.left - playerBall.getRadius(), rcBlock.top, playerBall.getRadius(), rcBlock.bottom - rcBlock.top);
			RECT rcRight = RectMake(rcBlock.right, rcBlock.top, playerBall.getRadius(), rcBlock.bottom - rcBlock.top);

			int nFace = 0;

			if (PtInRect(&rcTop, ptBall)) //����� ���
				nFace = 1;
			if (PtInRect(&rcLeft, ptBall)) //�¸�� ���
				nFace = 2;
			if (PtInRect(&rcRight, ptBall)) //���� ���
				nFace = 3;
			if (PtInRect(&rcBottom, ptBall)) //�ظ�� ���
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

		if (PtInRect(&rcTop, ptBall)) //����� ���
			nFace = 1;
		if (PtInRect(&rcLeft, ptBall)) //�¸�� ���
			nFace = 2;
		if (PtInRect(&rcRight, ptBall)) //���� ���
			nFace = 3;
		if (PtInRect(&rcBottom, ptBall)) //�ظ�� ���
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
			if (!block[x][y].isValid()) // ���忡 �������� �ʰų�
				continue;
			if (!block[x][y].getUseUpdate()) // �˻����� �ʴ� ���̸� ����
				continue;

			for (int x2 = 0; x2 < MAX_X; x2++)
			{
				for (int y2 = 0; y2 < MAX_Y; y2++)
				{

					if (!block[x2][y2].isValid()) //���忡 �������� �ʰų�
						continue;
					if (x == x2 && y == y2) //�ڱ� �ڽ��̸� ����
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

						if (!block[x2][y2].getIsCollision_BlockToBlock()) //�浹���� �ʴ� ��ü�� ����
							continue;

						if (rcTemp.top == checkBlock->getRect().top) //����
							checkBlock->collision(otherBlock, 1);
						if (rcTemp.left == checkBlock->getRect().left) //���ʸ�
							checkBlock->collision(otherBlock, 2);
						if (rcTemp.right == checkBlock->getRect().right) //�����ʸ�
							checkBlock->collision(otherBlock, 3);
						if (rcTemp.bottom == checkBlock->getRect().bottom) //�ظ�
							checkBlock->collision(otherBlock, 4);
					}

					if (PtInRect(&otherBlock->getRect(), ptTop)) //���ʿ� �ٸ� ����� ������
					{
						checkBlock->setCanMoveTop(false);
					}
					else
					{
						//checkBlock->setCanMoveTop(true); // ���� : �浹ó���� �ȵ�
					}

					if (PtInRect(&otherBlock->getRect(), ptLeft)) //���ʿ� �ٸ� ����� ������
					{
						checkBlock->setCanMoveLeft(false);
					}
					else
					{
						//checkBlock->setCanMoveLeft(true); // ���� : �浹ó���� �ȵ�
					}

					if (PtInRect(&otherBlock->getRect(), ptRight)) //�����ʿ� �ٸ� ����� ������
					{
						checkBlock->setCanMoveRight(false);
					}
					else
					{
						//checkBlock->setCanMoveRight(true); // ���� : �浹ó���� �ȵ�
					}

					if (PtInRect(&otherBlock->getRect(), ptBottom)) //�Ʒ��ʿ� �ٸ� ����� ������
					{
						checkBlock->setCanMoveBottom(false);
					}
					else
					{
						//checkBlock->setCanMoveBottom(true); // ���� : �浹ó���� �ȵ�
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
				if (bullet[i].getSrcBlock() == &block[x][y]) //�ҽ����̸� ����
					continue;

				RECT rcTemp;
				RECT rcBullet = bullet[i].getRect();
				RECT rcBlock = block[x][y].getRect();

				if (IntersectRect(&rcTemp, &rcBullet, &rcBlock))
				{
					bullet[i].collision(&block[x][y]);

					if (rcTemp.bottom - rcTemp.top == rcBlock.bottom - rcBlock.top || rcTemp.right - rcTemp.left == rcBlock.right - rcBlock.left) //collision�� ������ ȣ��Ǵ� ���� ����
					{
						block[x][y].collisionToBullet(&bullet[i]);
					}
					else
					{
						if (rcTemp.top == rcBlock.top) //����
							block[x][y].collisionToBullet(&bullet[i], 1);
						if (rcTemp.left == rcBlock.left) //���ʸ�
							block[x][y].collisionToBullet(&bullet[i], 2);
						if (rcTemp.right == rcBlock.right) //�����ʸ�
							block[x][y].collisionToBullet(&bullet[i], 3);
						if (rcTemp.bottom == rcBlock.bottom) //�ظ�
							block[x][y].collisionToBullet(&bullet[i], 4);
					}
				}
			}
		}
	}
}

void PlayGame::setTempBlock()
{
	//1��° ���
	for (int x = 0; x < MAX_X; x++)
	{
		for (int y = 0; y < MAX_Y; y++)
		{
			if (!block[x][y].isValid()) // ���忡 �������� �ʰų�
				continue;
			if (!block[x][y].getUseUpdate()) // �˻����� �ʴ� ���̸� ����
				continue;

			float length = WINSIZEX;

			//2��° ���
			for (int x2 = 0; x2 < MAX_X; x2++)
			{
				for (int y2 = 0; y2 < MAX_Y; y2++)
				{
					if (!block[x][y].getUseUpdate()) //������Ʈ�� ���� �ʰų�
						continue;
					if (!block[x2][y2].isValid()) //���忡 �������� �ʰų�
						continue;
					if (!block[x2][y2].getIsCollision_BlockToBlock()) //�浹���� �ʴ� ��ü�ų�
						continue;
					if (x == x2 && y == y2) //�ڱ� �ڽ��̸� ����
						continue;

					float templength = WINSIZEX;

					Block* source = &block[x][y];
					Block* dest = &block[x2][y2];

					//���� ������ �˻�
					if (block[x][y].getIndex() == 1601 || block[x][y].getIndex() == 1001 || block[x][y].getIndex() == 1101) 
					{
						//�������� �� �´� ��ġ�� �ѱ��
						//������ X���� ��ǥ�� ���� ����
						if(source->getCenterX() > dest->getRect().right || source->getCenterX() < dest->getRect().left)
							continue;
						//��� ��ġ�� ���� ��ġ���� ��
						if (source->getCenterY() < dest->getCenterY()) 
							continue;
						//�´� ��ġ��� �� ��ϱ����� �Ÿ��� ����
						templength = UTIL::getDistance(dest->getX(), dest->getY(), source->getX(), source->getY());
					}

					//������ ������ �˻�
					else if (block[x][y].getIndex() == 1301  || block[x][y].getIndex() == 1602 || block[x][y].getIndex() == 1002 || block[x][y].getIndex() == 1102 || block[x][y].getIndex() == 1802 || block[x][y].getIndex() == 1803)
					{
						//�������� �� �´� ��ġ�� �ѱ��
						//������ Y���� ��ǥ�� ���� ����
						if (source->getCenterY() > dest->getRect().bottom || source->getCenterY() < dest->getRect().top)
							continue;
						//��� ��ġ�� ���� ��ġ���� ������
						if (source->getCenterX() > dest->getCenterX())
							continue;
						//�´� ��ġ��� �� ��ϱ����� �Ÿ��� ����
						templength = UTIL::getDistance(dest->getX(), dest->getY(), source->getX(), source->getY());
					}

					//���� ������ �˻�
					else if (block[x][y].getIndex() == 1302 || block[x][y].getIndex() == 1604 || block[x][y].getIndex() == 1004 || block[x][y].getIndex() == 1104 || block[x][y].getIndex() == 1801 || block[x][y].getIndex() == 1804)
					{
						//�������� �� �´� ��ġ�� �ѱ��
						//������ Y���� ��ǥ�� ���� ����
						if (source->getCenterY() > dest->getRect().bottom || source->getCenterY() < dest->getRect().top)
							continue;
						//��� ��ġ�� ���� ��ġ���� ����
						if (source->getCenterX() < dest->getCenterX())
							continue;
						//�´� ��ġ��� �� ��ϱ����� �Ÿ��� ����
						templength = UTIL::getDistance(dest->getX(), dest->getY(), source->getX(), source->getY());
					}
					//���� ������ �˻�
					else if (block[x][y].getIndex() == 1303 || block[x][y].getIndex() == 1603 || block[x][y].getIndex() == 1003 || block[x][y].getIndex() == 1103)
					{
						//�������� �� �´� ��ġ�� �ѱ��
						//������ X���� ��ǥ�� ���� ����
						if (source->getCenterX() > dest->getRect().right || source->getCenterX() < dest->getRect().left)
							continue;
						//��� ��ġ�� ���� ��ġ���� �Ʒ�
						if (source->getCenterY() > dest->getCenterY())
							continue;
						//�´� ��ġ��� �� ��ϱ����� �Ÿ��� ����
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
			if (!block[x][y].isValid()) // ���忡 �������� �ʰų�
				continue;
			if (!block[x][y].getUseUpdate()) // �˻����� �ʴ� ���̸� ����
				continue;
			float length = WINSIZEX;

			for (int x2 = 0; x2 < MAX_X; x2++)
			{
				for (int y2 = 0; y2 < MAX_Y; y2++)
				{
					if (!block[x][y].getUseUpdate()) //������Ʈ�� ���� �ʰų�
						continue;
					if (!block[x2][y2].isValid()) //���忡 �������� �ʰų�
						continue;
					if (!block[x2][y2].getIsCollision_BlockToBlock()) //�浹���� �ʴ� ��ü�ų�
						continue;
					if (x == x2 && y == y2) //�ڱ� �ڽ��̸� ����
						continue;

					//������ ���� �ִ�ġ
					float templength = WINSIZEX;

					Block* source = &block[x][y];
					Block* dest = &block[x2][y2];

					if (block[x][y].getIndex() == 1801 || block[x][y].getIndex() == 1802) //���� ������ �˻�
					{
						//�������� �� �´� ��ġ�� �ѱ��
						//������ X���� ��ǥ�� ���� ����
						if (source->getCenterX() > dest->getRect().right || source->getCenterX() < dest->getRect().left)
							continue;
						//��� ��ġ�� ���� ��ġ���� ��
						if (source->getCenterY() < dest->getCenterY())
							continue;
						//�´� ��ġ��� �� ��ϱ����� �Ÿ��� ����
						templength = UTIL::getDistance(dest->getX(), dest->getY(), source->getX(), source->getY());
					}

					if (block[x][y].getIndex() == 1803 || block[x][y].getIndex() == 1804) //���� ������ �˻�
					{
						//�������� �� �´� ��ġ�� �ѱ��
						//������ X���� ��ǥ�� ���� ����
						if (source->getCenterX() > dest->getRect().right || source->getCenterX() < dest->getRect().left)
							continue;
						//��� ��ġ�� ���� ��ġ���� �Ʒ�
						if (source->getCenterY() > dest->getCenterY())
							continue;
						//�´� ��ġ��� �� ��ϱ����� �Ÿ��� ����
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
