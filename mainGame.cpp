#include "BounceBallHeader.h"

#include "mainGame.h"
#include "PlayGame.h"
#include "EditerMode.h"
#include "LevelSelect.h"
#include "TitleScene.h"

mainGame::mainGame()
{
}

mainGame::~mainGame()
{
}

//===========================================================================

//전역 변수 extern
TCHAR _fileNow[128] = { 0, };

map<string, bool> _mStage;
vector<pair<string, bool>> _vStage;

//============================================================================

HRESULT mainGame::init()
{
	gameNode::init(true);
	GetClientRect(g_hWnd, &rcClient);

	setImages();

	SOUNDMANAGER->Init();
	SOUNDMANAGER->AddSound(TEXT("ButtonSound"), TEXT("Sound\\ButtonSound.wav"), false, false);
	SOUNDMANAGER->AddSound(TEXT("StarSound"), TEXT("Sound\\StarSound.wav"), false, false);
	SOUNDMANAGER->AddSound(TEXT("BallSound"), TEXT("Sound\\BallSound.wav"), false, false);
	SOUNDMANAGER->AddSound(TEXT("BounceSound"), TEXT("Sound\\BounceSound.wav"), false, false);
	SOUNDMANAGER->AddSound(TEXT("DieSound"), TEXT("Sound\\DieSound.wav"), false, false);
	SOUNDMANAGER->AddSound(TEXT("RouletteSound"), TEXT("Sound\\RouletteSound.wav"), false, false);

	_vStage = EDITER->StageLoad(TEXT("System\\stages.txt"));

	SCENEMANAGER->Init();
	//게임 플레이씬
	SCENEMANAGER->AddScene(TEXT("playGame"), new PlayGame);

	//에디터모드 씬
	SCENEMANAGER->AddScene(TEXT("editerMode"), new EditerMode());

	//레벨선택 씬
	SCENEMANAGER->AddScene(TEXT("levelSelect"), new LevelSelect);

	//타이틀씬
	SCENEMANAGER->AddScene(TEXT("TitleScene"), new TitleScene);
	SCENEMANAGER->ChangeScene(TEXT("TitleScene"));

	return S_OK;
}

void mainGame::release()
{
	gameNode::release();

	EDITER->stageSave(TEXT("System\\stages.txt"), _vStage);

	SCENEMANAGER->Release();
}

void mainGame::update()
{
	gameNode::update();
	SCENEMANAGER->Update();
}

void mainGame::render()
{
	PatBlt(getMemDC(), 0, 0, rcClient.right, rcClient.bottom, WHITENESS);
	//===================================================================

	SCENEMANAGER->Render();

	//====================================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}


void mainGame::setImages()
{
	IMAGEMANAGER->addImage(TEXT("BackGround_game"), TEXT("Image\\background_game.bmp"), WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage(TEXT("BackGround_title"), TEXT("Image\\background_title.bmp"), WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage(TEXT("001-008_Ball"), TEXT("Image\\001-008_ball.bmp"), 50, 100, 2, 4, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage(TEXT("101-103_Star"), TEXT("Image\\101-103_star.bmp"), 50, 150, 1, 3, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage(TEXT("201-217_Block"), TEXT("Image\\201-217_block.bmp"), 150, 300, 3, 6, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage(TEXT("301-314_Block"), TEXT("Image\\301-314_block.bmp"), 150, 300, 3, 6, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage(TEXT("401_Block"), TEXT("Image\\401_block.bmp"), 50, 50, 1, 1, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage(TEXT("501-520_Block"), TEXT("Image\\501-520_block.bmp"), 200, 300, 4, 6, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage(TEXT("601-608_Block"), TEXT("Image\\601-608_block.bmp"), 100, 300, 2, 6, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage(TEXT("701-710_Block"), TEXT("Image\\701-710_block.bmp"), 100, 300, 2, 6, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage(TEXT("801-804_Block"), TEXT("Image\\801-804_block.bmp"), 50, 200, 1, 4, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage(TEXT("901_Block"), TEXT("Image\\901_block.bmp"), 50, 50, 1, 1, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage(TEXT("1001-1004_Block"), TEXT("Image\\1001-1004_block.bmp"), 50, 200, 1, 4, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage(TEXT("1101-1104_Block"), TEXT("Image\\1101-1104_block.bmp"), 50, 200, 1, 4, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage(TEXT("1201-1208_Block"), TEXT("Image\\1201-1208_block.bmp"), 100, 300, 2, 6, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage(TEXT("1301-1303_Block"), TEXT("Image\\1301-1303_block.bmp"), 50, 150, 1, 3, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage(TEXT("1401-1404_Block"), TEXT("Image\\1401-1404_block.bmp"), 50, 200, 1, 4, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage(TEXT("1501-1504_Block"), TEXT("Image\\1501-1504_block.bmp"), 50, 200, 1, 4, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage(TEXT("1601-1604_Block"), TEXT("Image\\1601-1604_block.bmp"), 50, 200, 1, 4, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage(TEXT("1701_Block"), TEXT("Image\\1701_block.bmp"), 50, 50, 1, 1, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage(TEXT("1801-1804_Block"), TEXT("Image\\1801-1804_block.bmp"), 50, 200, 1, 4, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage(TEXT("1901-1902_Block"), TEXT("Image\\1901-1902_block.bmp"), 50, 100, 1, 2, true, TRANSCOLOR);

	IMAGEMANAGER->addFrameImage(TEXT("513_Block_ani"), TEXT("Image\\513_block_ani.bmp"), 200, 50, 4, 1, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage(TEXT("516_Block_ani"), TEXT("Image\\516_block_ani.bmp"), 200, 100, 4, 2, true, TRANSCOLOR);
	IMAGEMANAGER->addFrameImage(TEXT("1501-1504_Block_ani"), TEXT("Image\\1501-1504_block_ani.bmp"), 50, 200, 1, 4, true, TRANSCOLOR);

	IMAGEMANAGER->addImage(TEXT("216_Block_ani"), TEXT("Image\\216_block_ani.bmp"), 50, 50, true, TRANSCOLOR);
	IMAGEMANAGER->addImage(TEXT("217_Block_ani"), TEXT("Image\\217_block_ani.bmp"), 50, 50, true, TRANSCOLOR);
	IMAGEMANAGER->addImage(TEXT("701_Block_ani"), TEXT("Image\\701_block_ani.bmp"), 50, 50, true, TRANSCOLOR);
	IMAGEMANAGER->addImage(TEXT("702_Block_ani"), TEXT("Image\\702_block_ani.bmp"), 50, 50, true, TRANSCOLOR);

	IMAGEMANAGER->addImage(TEXT("Eraser"), TEXT("Image\\eraser.bmp"), 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage(TEXT("LevelBlock_lock"), TEXT("Image\\levelBlock_lock.bmp"), 150, 140, true, TRANSCOLOR);
	IMAGEMANAGER->addImage(TEXT("LevelBlock_unlock"), TEXT("Image\\levelBlock_unlock.bmp"), 150, 140, true, TRANSCOLOR);
	IMAGEMANAGER->addImage(TEXT("MapEditor"), TEXT("Image\\mapEditor.bmp"), 300, 100, true, TRANSCOLOR);
	IMAGEMANAGER->addImage(TEXT("Menu"), TEXT("Image\\menu.bmp"), 200, 300, true, TRANSCOLOR);
	IMAGEMANAGER->addImage(TEXT("Play"), TEXT("Image\\play.bmp"), 500, 150, true, TRANSCOLOR);
	IMAGEMANAGER->addImage(TEXT("Title"), TEXT("Image\\title.bmp"), 1100, 120, true, TRANSCOLOR);
}