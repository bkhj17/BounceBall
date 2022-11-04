#pragma once
#include "Button.h"

class LevelButton : public Button
{
	TCHAR _stageName[128] = { 0, };
	bool _opened;
public:
	LevelButton(const TCHAR* name, bool opened, int x, int y);
	~LevelButton();

	void setName(const TCHAR* name) {
		_tcscpy_s(_stageName, name);
	}
	const TCHAR *getName() { return _stageName; }
	void setOpened(bool op) { _opened = op; }
	bool isOpened() { return _opened; }

	HRESULT init();
	void	release();
	void	update();
	void	render(HDC _hdc);
};

