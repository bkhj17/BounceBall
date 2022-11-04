#include "Game.h"
#include "LevelButton.h"

LevelButton::LevelButton(const TCHAR* name, bool opened, int x, int y) : _opened(opened) {
	setName(name);
	setX(x);
	setY(y);

	init();
}
LevelButton::~LevelButton() {}

HRESULT LevelButton::init()
{
	if (_opened)
		Button::init(IMAGEMANAGER->findImage(TEXT("LevelBlock_unlock")), getX(), getY(), 0, 0, 150, 140, true);
	else
		Button::init(IMAGEMANAGER->findImage(TEXT("LevelBlock_lock")), getX(), getY(), 0, 0, 150, 140, true);

	return S_OK;
}

void LevelButton::release()
{
	Button::release();
}

void LevelButton::update() {}

void LevelButton::render(HDC _hdc)
{
	Button::render(_hdc);

	TextOut(_hdc, getX() + 30, getY() + getHeight() / 2 - 10, getName(), _tcslen(getName()));
}
