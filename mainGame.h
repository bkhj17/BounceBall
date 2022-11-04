#pragma once
#include "gameNode.h"
#include "Block.h"
#include "Ball.h"
#include "Bullet.h"

class Image;

class mainGame : public gameNode
{
private:
	RECT			rcClient;

	/////////////////////////////////////////
	// µð¹ö±×
	/////////////////////////////////////////

	float			debug;

public:
	mainGame();
	~mainGame();

	//=============================================


	//============================================
	virtual HRESULT init();
	virtual void	update();
	virtual void	render();
	virtual void	release();

	void setImages();

};

