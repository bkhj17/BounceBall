#include "Game.h"
#include "Image.h"
#include "Button.h"

Button::Button() {}
Button::~Button() {}

HRESULT Button::init(Image *img, float x, float y, int frameX, int frameY, int width, int height, bool valid)
{
	if (img) _img = img;

	_x = x;
	_y = y;
	_frameX = frameX;
	_frameY = frameY;
	_width = width;
	_height = height;

	_valid = valid;
	return S_OK;
}

void Button::release()
{
	_img = NULL;
}

void Button::update()
{

}

void Button::render(HDC _hdc)
{
	if (!isValid()) return;

	if (!_img)
		RectangleMake(_hdc, _x, _y, _width, _height);
	else {
		if (_img->getMaxFrameX() > 0 || _img->getMaxFrameY() > 0) {
			_img->frameRender(_hdc, _x + (_width / 2) - _img->getFrameWidth() / 2, _y + (_height / 2) - _img->getFrameHeight() / 2, _frameX, _frameY);
		}
		else {
			_img->render(_hdc, (_x + (_width / 2)) - _img->getWidth() / 2, _y + (_height / 2) - _img->getHeight() / 2, 0, 0, _img->getWidth(), _img->getHeight());
		}
	}
}

bool Button::isClicked(POINT pt)
{
	if (isValid())
		return PtInRect(&getRect(), pt);
	else
		return false;
}
