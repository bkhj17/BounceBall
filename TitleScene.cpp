#include "BounceBallHeader.h"
#include "TitleScene.h"

TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

HRESULT TitleScene::init()
{
	playButton.init(IMAGEMANAGER->findImage(TEXT("Play")), 0, 200, 0, 0, 500, 150, true);
	newEditButton.init(IMAGEMANAGER->findImage(TEXT("MapEditor")), WINSIZEX - 300, 200, 0, 0, 300, 100, true);

	return S_OK;
}

void TitleScene::release()
{
}

void TitleScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {

		GetCursorPos(&g_ptMouse);
		ScreenToClient(g_hWnd, &g_ptMouse);

		if (playButton.isClicked(g_ptMouse)) {
			SOUNDMANAGER->Play(TEXT("ButtonSound"), DEFAULT_VOLUME);
			SCENEMANAGER->ChangeScene(TEXT("levelSelect"));
		}
		if (newEditButton.isClicked(g_ptMouse)) {
			SOUNDMANAGER->Play(TEXT("ButtonSound"), DEFAULT_VOLUME);
			_stprintf_s(_fileNow, _countof(_fileNow), TEXT(""));
			SCENEMANAGER->ChangeScene(TEXT("editerMode"));
		}
	}
}

void TitleScene::render()
{
	IMAGEMANAGER->render(TEXT("BackGround_title"), getMemDC(), 0, 0);
	IMAGEMANAGER->render(TEXT("Title"), getMemDC(), 0, 0);

	playButton.render(getMemDC());
	newEditButton.render(getMemDC());
}
