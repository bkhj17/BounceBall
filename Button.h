#pragma once
class Image;
class Button
{
	bool _valid;
	Image *_img;
	int _frameX, _frameY;

	float _x, _y;
	int _width, _height;
public:
	Button();
	virtual ~Button();

	void	setValid(bool valid) { _valid = valid; }
	bool	isValid() { return _valid; }
	void	setX(float x) { _x = x; }
	float	getX() { return _x; }
	void	setY(float y) { _y = y; }
	float	getY() { return _y; }
	void	setFrameX(int x) { _frameX = x; }
	int		getFrameX() { return _frameX; }
	void	setFrameY(int y) { _frameY = y; }
	int		getFrameY() { return _frameY; }

	int		getMaxFrameX() { return _img->getMaxFrameX(); }
	int		getMaxFrameY() { return _img->getMaxFrameY(); }

	void	setWidth(int width) { _width = width; }
	int		getWidth() { return _width; }
	void	setHeight(int height) { _height = height; }
	int		getHeight() { return _height; }

	RECT	getRect() { return RectMake(_x, _y, _width, _height); }

	Image*	getImage() { return _img; }

	virtual HRESULT	init(Image *img, float x, float y, int frameX, int frameY, int width, int height, bool valid = false);
	virtual	void	release();
	virtual	void	update();
	virtual	void	render(HDC _hdc);

	bool	isClicked(POINT pt);
};