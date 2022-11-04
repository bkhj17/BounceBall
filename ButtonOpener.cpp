#include "Game.h"
#include "ButtonOpener.h"



ButtonOpener::ButtonOpener()
{
}
ButtonOpener::~ButtonOpener()
{
}

void ButtonOpener::open() {
	opened = true;

	vector<BlockButton*>::iterator it = vButton.begin();
	vector<BlockButton*>::iterator it_end = vButton.end();

	for (; it != it_end; it++) {
		(*it)->setValid(true);
	}
}
void ButtonOpener::close() {
	opened = false;

	vector<BlockButton*>::iterator it = vButton.begin();
	vector<BlockButton*>::iterator it_end = vButton.end();

	for (; it != it_end; it++) {
		(*it)->setValid(false);
	}
}
HRESULT ButtonOpener::init(int index, float x, float y, bool valid)
{
	BlockButton::init(index, x, y, valid);

	return S_OK;
}

void ButtonOpener::release()
{
	vector<BlockButton*>::iterator it = vButton.begin();

	for (; it != vButton.end();) {
		SAFE_DELETE(*it);
		it = vButton.erase(it);
	}
}

void ButtonOpener::render(HDC _hdc)
{
	BlockButton::render(_hdc);

	vector<BlockButton*>::iterator it = vButton.begin();
	vector<BlockButton*>::iterator it_end = vButton.end();

	for (; it != it_end; it++) {
		(*it)->render(_hdc);
	}
}

void ButtonOpener::changeState()
{
	if (opened) {
		close();
		defaultImage();
	}
	else {
		open();
	}
}

void ButtonOpener::defaultImage()
{
	this->setIndex((this->getIndex() % 100) * 100 + 1);
}

int ButtonOpener::buttonClicked(POINT pt)
{
	int index = -1;

	vector<BlockButton*>::iterator it = vButton.begin();
	vector<BlockButton*>::iterator it_end = vButton.end();

	for (; it != it_end; it++) {
		if (PtInRect(&(*it)->getRect(), pt) && (*it)->isValid()) {

			index = (*it)->getIndex();

			setIndex(index);
			setFrameX(((getIndex() - 1) % 100) / (getMaxFrameY() + 1));
			setFrameY(((getIndex() - 1) % 100) % (getMaxFrameY() + 1));

			break;
		}
	}
	
	close();

	return index;
}