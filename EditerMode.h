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


	//UI����
	//��ư   : 000, 001, 401, 901, 1701 - 5��
	//������ : 1, 2, 3, 5, 6, 7, 8, 10, 11, 12, 13, 14, 15, 16, 18, 19 - 16��

	int				_clickIndex;
	/////////////////////////////////////////
	// ���� ����
	/////////////////////////////////////////

	// ��
	Block			block[MAX_X][MAX_Y];

	// �÷��̾� ��
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

