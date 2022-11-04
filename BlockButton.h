#pragma once
#include "Button.h"

class Block;
class BlockButton : public Button
{
	int _index;
public:
	BlockButton();
	BlockButton(int index, float x, float y, bool valid = false);
	~BlockButton();

	void setIndex(int index) { _index = index; }
	int getIndex() { return _index; }

	HRESULT	init(Image *img, float x, float y, int frameX, int frameY, int width, int height, bool valid = true);
	HRESULT	init(int index, float x, float y, bool valid = false);
	void	release();
	void	update();
	virtual void	render(HDC _hdc);
};

