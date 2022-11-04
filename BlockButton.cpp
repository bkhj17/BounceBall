#include "Game.h"
#include "Button.h"
#include "Block.h"
#include "BlockButton.h"

BlockButton::BlockButton()
{
}

BlockButton::BlockButton(int index, float x, float y, bool valid)
{
	init(index, x, y, valid);
}

BlockButton::~BlockButton()
{
}

HRESULT BlockButton::init(Image * img, float x, float y, int frameX, int frameY, int width, int height, bool valid)
{
	Button::init(img, x, y, frameX, frameY, width, height, valid);
	return S_OK;
}

HRESULT BlockButton::init(int index, float x, float y, bool valid) {
	_index = index;

	Image *img = NULL;
	switch (_index / 100) {
	case 0:
		if (_index == 0) img = IMAGEMANAGER->findImage(TEXT("Eraser"));
		else if (_index == 1) img = IMAGEMANAGER->findImage(TEXT("001_Ball"));
		break;
	case 1:
		img = IMAGEMANAGER->findImage(TEXT("101-103_Star"));
		break;
	case 2:
		img = IMAGEMANAGER->findImage(TEXT("201-217_Block"));
		break;
	case 3:
		img = IMAGEMANAGER->findImage(TEXT("301-314_Block"));
		break;
	case 4:
		img = IMAGEMANAGER->findImage(TEXT("401_Block"));
		break;
	case 5:
		img = IMAGEMANAGER->findImage(TEXT("501-520_Block"));
		break;
	case 6:
		img = IMAGEMANAGER->findImage(TEXT("601-608_Block"));
		break;
	case 7:
		img = IMAGEMANAGER->findImage(TEXT("701-710_Block"));
		break;
	case 8:
		img = IMAGEMANAGER->findImage(TEXT("801-804_Block"));
		break;
	case 9:
		img = IMAGEMANAGER->findImage(TEXT("901_Block"));
		break;
	case 10:
		img = IMAGEMANAGER->findImage(TEXT("1001-1004_Block"));
		break;
	case 11:
		img = IMAGEMANAGER->findImage(TEXT("1101-1104_Block"));
		break;
	case 12:
		img = IMAGEMANAGER->findImage(TEXT("1201-1208_Block"));
		break;
	case 13:
		img = IMAGEMANAGER->findImage(TEXT("1301-1303_Block"));
		break;
	case 14:
		img = IMAGEMANAGER->findImage(TEXT("1401-1404_Block"));
		break;
	case 15:
		img = IMAGEMANAGER->findImage(TEXT("1501-1504_Block"));
		break;
	case 16:
		img = IMAGEMANAGER->findImage(TEXT("1601-1604_Block"));
		break;
	case 17:
		img = IMAGEMANAGER->findImage(TEXT("1701_Block"));
		break;
	case 18:
		img = IMAGEMANAGER->findImage(TEXT("1801-1804_Block"));
		break;
	case 19:
		img = IMAGEMANAGER->findImage(TEXT("1901-1902_Block"));
		break;
	default:
		break;
	}

	if (img == NULL) return E_FAIL;

	if (img->getMaxFrameY() > 0) {

		Button::init(img, x, y,
			((_index % 100) - 1) / (img->getMaxFrameY() + 1), ((_index % 100) - 1) % (img->getMaxFrameY() + 1),
			img->getFrameWidth(), img->getFrameHeight(), valid);
	}
	else {
		if (_index == 0) {
			Button::init(img, x, y, 0, 0, 50, 50, valid);
		}
		else Button::init(img, x, y, 0, 0, img->getWidth(), img->getHeight(), valid);
	}

	return S_OK;
}

void BlockButton::release()
{
	Button::release();
}

void BlockButton::update()
{
}

void BlockButton::render(HDC _hdc)
{
	if(isValid()) RectangleMake(_hdc, getX(), getY(), getWidth(), getHeight());
	Button::render(_hdc);
}