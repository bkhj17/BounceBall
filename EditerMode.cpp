#include "BounceBallHeader.h"
#include "EditerMode.h"

#define	FILEPATH TEXT("Stage\\")

EditerMode::EditerMode() {}
EditerMode::~EditerMode() {}

HRESULT EditerMode::init()
{
	GetClientRect(g_hWnd, &rcClient);

	//////
	ButtonSetting();

	_clickIndex = 000;			//시작은 지우개

								// 레벨 초기화
	for (int x = 0; x < MAX_X; x++)
	{
		for (int y = 0; y < MAX_Y; y++)
		{
			block[x][y].setX(x * 50);
			block[x][y].setY(y * 50);
			block[x][y].updateRect();
		}
	}
	playerBall.setRadius(12.5);
	playerBall.setYspeed(0);

	menuSelected = false;
	blockSetting = true;

	if (_tcslen(_fileNow) > 0) {
		TCHAR strFile[128];

		_stprintf_s(strFile, _countof(strFile), TEXT("%s%s"), FILEPATH, _fileNow);

		if (EDITER->load(strFile, MAX_X, MAX_Y, block)) {
			//로드 성공
			if (_tcscmp(_fileNow, TEXT("Test")) == 0)
				_tcscpy_s(_fileNow, _fileName);
			else
				setFileName(_fileNow);
		}
		else {
			//파일 로드 실패
			if (_tcslen(_fileName) <= 0) {
				_tcscpy_s(_fileNow, TEXT(""));
				setFileName(TEXT(""));
			}
		}
	}
	else {
		//파일 미설정
		playerBall.setVisible(false);

		_tcscpy_s(_fileNow, TEXT(""));
		setFileName(TEXT(""));

		for (int x = 0; x < MAX_X; x++) {
			for (int y = 0; y < MAX_Y; y++) {
				block[x][y].init(0, false);
			}
		}
	}

	// 플레이어 초기화 : 볼 블록(시작위치)을 받아온다
	for (int x = 0; x < MAX_X; x++) {
		for (int y = 0; y < MAX_Y; y++) {
			int i = (int)(block[x][y].getIndex());
			if (block[x][y].getIndex() == 001) {
				playerBall.init(x, y);
				break;
			}
		}
	}

	_fileSelecting = false;
	return S_OK;
}

void EditerMode::ButtonSetting() {

	//UI에서
	//버튼   : 000, 001, 401, 901, 1701 - 5종
	//오프너 : 1, 2, 3, 5, 6, 7, 8, 10, 11, 12, 13, 14, 15, 16, 18, 19 - 16종

	int nB[5] = { 000, 001, 401, 901, 1701 };
	int nO[16] = { 1, 2, 3, 5, 6, 7, 8, 10, 11, 12, 13, 14, 15, 16, 18, 19 };
	int oMax[16] = { 3, 17, 14, 20, 8, 10, 4, 4, 4, 8, 3, 4, 4, 4, 4, 2 };

	for (int i = 0; i < 5; i++) {
		if (nB[i] == 0) {
			_button[i].init(nB[i], 0, 0, true);
		}
		else if (nB[i] == 1) {
			_button[1].init(IMAGEMANAGER->findImage(TEXT("001-008_Ball")), 50, 0, 0, 0, 50, 50, true);
			_button[1].setIndex(001);
		}
		else
			_button[i].init(nB[i], (nB[i] / 100 + 1) * 50, 0, true);
	}

	for (int i = 0; i < 16; i++) {
		_opener[i].init(nO[i] * 100 + 1, 50 * (nO[i] + 1), 0, true);
		for (int j = 0; j < oMax[i]; j++) {
			_opener[i].input(new BlockButton(_opener[i].getIndex() + j,
				_opener[i].getRect().left + (j / (_opener[i].getMaxFrameY() + 1)) * 50,
				_opener[i].getRect().bottom + 1 + (j % (_opener[i].getMaxFrameY() + 1)) * 50));
		}
	}
}

void EditerMode::release()
{
	for (int i = 0; i < 16; i++)	_opener[i].release();
}

void EditerMode::update()
{
	//파일이름 변경
	if (_fileSelecting) {
		if (KEYMANAGER->isOnceKeyDown(VK_BACK)) {
			_fileName[_tcslen(_fileName) - 1] = '\0';
		}

		for (int i = 48; i <= 90; i++) {
			if (KEYMANAGER->isOnceKeyDown((char)i)) {
				int len = _tcslen(_fileName);
				if ((i >= (int)'A' && i < (int)'Z')) {
					if (KEYMANAGER->isStayKeyDown(VK_SHIFT)) _fileName[len] = (char)i;
					else _fileName[len] = (char)(i + 32);
				}
				else {
					_fileName[len] = (char)i;
				}
				_fileName[len + 1] = '\0';
			}
		}

		for (int i = 96; i <= 105; i++) {
			if (KEYMANAGER->isOnceKeyDown((char)i)) {
				int len = _tcslen(_fileName);
				_fileName[len] = (char)(i - 48);
				_fileName[len + 1] = '\0';
			}
		}

		if (KEYMANAGER->isOnceKeyDown(190)) {
			int len = _tcslen(_fileName);
			_fileName[len] = '.';
			_fileName[len + 1] = '\0';
		}

		if (KEYMANAGER->isOnceKeyDown(189)) {
			int len = _tcslen(_fileName);
			if (KEYMANAGER->isOnceKeyDown(VK_SHIFT))
				_fileName[len] = '_';
			else
				_fileName[len] = '-';
			_fileName[len + 1] = '\0';
		}

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
			TCHAR strFile[128];
			_stprintf_s(strFile, _countof(strFile), TEXT("%s%s"), FILEPATH, _fileName);

			EDITER->load(strFile, MAX_X, MAX_Y, block);
			for (int x = 0; x < MAX_X; x++) {
				for (int y = 0; y < MAX_Y; y++) {
					if (block[x][y].getIndex() == 001) {
						playerBall.init(x, y);
						break;
					}
				}
			}

			_fileSelecting = false;
		}

		return;
	}

	if (KEYMANAGER->isOnceKeyUp(VK_F1)) {
		//F1: 현재 파일에 저장
		TCHAR strFile[128];
		_stprintf_s(strFile, _countof(strFile), TEXT("%s%s"), FILEPATH, _fileName);

		EDITER->save(strFile, MAX_X, MAX_Y, block);

		_vStage.push_back(pair<string, bool>(_fileName, false));
	}
	if (KEYMANAGER->isOnceKeyUp(VK_F2)) {
		//F2: 파일 로드

		TCHAR strFile[128];
		_stprintf_s(strFile, _countof(strFile), TEXT("%s%s"), FILEPATH, _fileName);

		EDITER->load(strFile, MAX_X, MAX_Y, block);

		for (int x = 0; x < MAX_X; x++) {
			for (int y = 0; y < MAX_Y; y++) {
				if (block[x][y].getIndex() == 001) {
					playerBall.init(x, y);
					break;
				}
			}
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_F3)) {
		//F3 : 파일 변경창 열기
		_fileSelecting = true;
	}

	if (KEYMANAGER->isOnceKeyUp(VK_BACK))
	{
		//backspace : 타이틀로 돌아가기
		SCENEMANAGER->ChangeScene(TEXT("TitleScene"));
	}

	if (KEYMANAGER->isOnceKeyUp(VK_SPACE))
	{
		TCHAR strFile[128];
		_stprintf_s(strFile, _countof(strFile), TEXT("%sTest"), FILEPATH, _fileName);
		EDITER->save(strFile, MAX_X, MAX_Y, block);

		_tcscpy_s(_fileNow, TEXT("Test"));
		SCENEMANAGER->ChangeScene(TEXT("playGame"));
	}


	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
		GetCursorPos(&g_ptMouse);
		ScreenToClient(g_hWnd, &g_ptMouse);

		menuSelected = false;


		for (int i = 0; i < 5; i++) {
			if (_button[i].isClicked(g_ptMouse)) {
				menuSelected = true;
				break;
			}
		}
		for (int i = 0; i < 16; i++) {
			if (_opener[i].isClicked(g_ptMouse)) {
				menuSelected = true;
				break;
			}
		}
		if (!menuSelected) {
			for (int i = 0; i < 16; i++) {
				int index = _opener[i].buttonClicked(g_ptMouse);

				if (index >= 0) {
					menuSelected = true;
					_clickIndex = index;

					break;
				}
			}
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
		GetCursorPos(&g_ptMouse);
		ScreenToClient(g_hWnd, &g_ptMouse);

		menuSelected = false;
		for (int i = 0; i < 5; i++) {
			if (_button[i].isClicked(g_ptMouse)) {
				for (int j = 0; j < 16; j++) {
					_opener[j].close();
				}

				menuSelected = true;
				_clickIndex = _button[i].getIndex();
				break;
			}
		}
		for (int i = 0; i < 16; i++) {
			if (_opener[i].isClicked(g_ptMouse)) {
				for (int j = 0; j < 16; j++) {
					_opener[j].close();
				}

				menuSelected = true;
				_opener[i].changeState();
				break;
			}
		}

		blockSetting = false;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !menuSelected) blockSetting = true;

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && blockSetting) {
		GetCursorPos(&g_ptMouse);
		ScreenToClient(g_hWnd, &g_ptMouse);

		int px = g_ptMouse.x / 50;
		int py = g_ptMouse.y / 50;

		if (px < 0 || px >= MAX_X || py < 0 || py >= MAX_Y) return;

		if (_clickIndex == 0)
			block[px][py].init(0, false);
		else if (_clickIndex == 1) {
			int bx = (int)playerBall.getX() / 50;
			int by = (int)playerBall.getY() / 50;

			block[bx][by].init(0, false);
			block[px][py].init(1, true);
			playerBall.init(px, py);
		}
		else if (_clickIndex == 509 || _clickIndex == 510
			|| _clickIndex == 511 || _clickIndex == 512)
		{
			//유일
			for (int x = 0; x < MAX_X; x++) {
				for (int y = 0; y < MAX_Y; y++) {
					if (block[x][y].getIndex() == _clickIndex) {
						block[x][y].init(0, false);
					}
				}
			}

			block[px][py].init(_clickIndex, true);
		}
		else
			block[px][py].init(_clickIndex, true);
	}
}

void EditerMode::render()
{

	// 배경화면 렌더링
	IMAGEMANAGER->render(TEXT("BackGround_game"), getMemDC());

	// 플레이어공
	if (playerBall.getVisible())
		playerBall.render(getMemDC());

	// 블럭
	for (int x = 0; x < MAX_X; x++)
	{
		for (int y = 0; y < MAX_Y; y++)
		{
			if (!block[x][y].isValid())
				continue;
			block[x][y].render(getMemDC());
		}
	}

	for (int i = 0; i < 5; i++)
		_button[i].render(getMemDC());

	for (int i = 0; i < 16; i++) {
		_opener[i].render(getMemDC());
	}

	//디버그
	TCHAR			str[256] = { 0, };
	//RECT rcBlock = block[2][10].getRect();
	//_stprintf_s(str, sizeof(str), TEXT("디버그 : %f"), UTIL::getDistance(playerBall.getX(), playerBall.getY(), rcBlock.left, rcBlock.top, rcBlock.right, rcBlock.top));
	//TextOut(getMemDC(), 0, 0, str, _tcslen(str));
	//_stprintf_s(str, sizeof(str), TEXT("디버그 : %f"), UTIL::getDistance(100, 100, 50, 100, 150, 100));
	//TextOut(getMemDC(), 0, 20, str, _tcslen(str));
	_stprintf_s(str, sizeof(str), TEXT("File name : %s"), _fileName);
	TextOut(getMemDC(), 0, 100, str, _tcslen(str));
	_stprintf_s(str, sizeof(str), TEXT("clickIndex : %d"), _clickIndex);
	TextOut(getMemDC(), 0, 120, str, _tcslen(str));

	_stprintf_s(str, sizeof(str), TEXT("F1 = Save"));
	TextOut(getMemDC(), 0, 160, str, _tcslen(str));
	_stprintf_s(str, sizeof(str), TEXT("F2 = Load"));
	TextOut(getMemDC(), 0, 180, str, _tcslen(str));
	_stprintf_s(str, sizeof(str), TEXT("F3 = File Change"));
	TextOut(getMemDC(), 0, 200, str, _tcslen(str));
	_stprintf_s(str, sizeof(str), TEXT("SPACE = Test"));
	TextOut(getMemDC(), 0, 220, str, _tcslen(str));
	_stprintf_s(str, sizeof(str), TEXT("Backspace = back to Title"));
	TextOut(getMemDC(), 0, 240, str, _tcslen(str));


	if (_fileSelecting) {
		RectangleMakeCenter(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, 300, 100);
		_stprintf_s(str, sizeof(str), TEXT("File name :   %s"), _fileName);
		TextOut(getMemDC(), WINSIZEX / 2 - 100, WINSIZEY / 2 - 10, str, _tcslen(str));
	}
}



