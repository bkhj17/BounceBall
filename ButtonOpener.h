#pragma once
#include "BlockButton.h"

class ButtonOpener : public BlockButton
{
	vector<BlockButton *> vButton;

	bool opened;

	///////////////////////////
public:
	ButtonOpener();
	~ButtonOpener();

	HRESULT	init(int index, float x, float y, bool valid = true);
	void release();

	void input(BlockButton *button) {
		if(button != NULL) vButton.push_back(button);
	}

	void render(HDC _hdc);

	void open();
	void close();

	void changeState();

	void defaultImage();

	int buttonClicked(POINT pt);
};

