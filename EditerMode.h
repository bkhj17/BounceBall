#pragma once
#include "gameNode.h"
#include "Block.h"
#include "Ball.h"
#include "BlockButton.h"
#include "ButtonOpener.h"

class Image;
class BlockButton;
class ButtonOpener;

class EditerMode : public gameNode
{
private:
	RECT			rcClient;

	TCHAR			_fileName[128] = { 0, };
	/////////////////////////////////////////
	BlockButton		_button[5];
	ButtonOpener	_opener[16];


	//UI에서
	//버튼   : 000, 001, 401, 901, 1701 - 5종
	//오프너 : 1, 2, 3, 5, 6, 7, 8, 10, 11, 12, 13, 14, 15, 16, 18, 19 - 16종

	int				_clickIndex;
	/////////////////////////////////////////
	// 게임 정보
	/////////////////////////////////////////

	// 블럭
	Block			block[MAX_X][MAX_Y];

	// 플레이어 공
	Ball			playerBall;

	//////////////////////////////////////////

	bool menuSelected;
	bool blockSetting;

	bool _fileSelecting;

public:
	EditerMode();
	~EditerMode();

	void setFileName(const TCHAR *fileName) {
		_tcscpy_s(_fileName, fileName);
	}
	//=============================================

	void ButtonSetting();

	//============================================
	virtual HRESULT init();
	virtual void	update();
	virtual void	render();
	virtual void	release();
};

