#pragma once
#include "gameNode.h"

class Button;
class TitleScene : public gameNode
{
	Button playButton;
	Button newEditButton;
public:
	TitleScene();
	~TitleScene();

	HRESULT	init();
	void	release();
	void	update();
	void	render();
};

