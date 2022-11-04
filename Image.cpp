#include "Game.h"
#include "Image.h"

#pragma comment(lib, "msimg32.lib")

Image::Image() : _imageInfo(NULL),
				_fileName(NULL),
				_trans(false),
				_transColor(RGB(0,0,0))
{
}

Image::~Image()
{
}

HRESULT Image::init(int width, int height)
{
	if (_imageInfo != NULL)
		release();

	// ȭ�� DC�� �޾ƿͼ�
	HDC hdc = GetDC(g_hWnd);

	_imageInfo				= new IMAGE_INFO;
	_imageInfo->loadType	= LOAD_EMPTY;
	_imageInfo->resID		= 0;
	_imageInfo->hMemDC		= CreateCompatibleDC(hdc);
	_imageInfo->hBit		= (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOldBit		= (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width		= width;
	_imageInfo->height		= height;

	_fileName	= NULL;
	_trans		= FALSE;
	_transColor = RGB(0, 0, 0);

	// ��Ʈ�� ������ �����ϴ� ��찡 �߻��ϸ�
	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;    // �����ߴٰ� ����
	}

	// ���� ȭ�� DC�� ����
	ReleaseDC(g_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const TCHAR* fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	if (_imageInfo != NULL)
		release();

	HDC hdc = GetDC(g_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOldBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	size_t len = _tcslen(fileName);

	_fileName = new TCHAR[len + 1];
	_tcscpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(g_hWnd, hdc);
	return S_OK;
}

HRESULT Image::init(const TCHAR * fileName, float x, float y, int width, int height, BOOL trans, COLORREF transColor)
{
	if (_imageInfo != NULL)
		release();

	HDC hdc = GetDC(g_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOldBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	size_t len = _tcslen(fileName);

	_fileName = new TCHAR[len + 1];
	_tcscpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(g_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const TCHAR * fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	if (_imageInfo != NULL)
		release();

	HDC hdc = GetDC(g_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOldBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	size_t len = _tcslen(fileName);

	_fileName = new TCHAR[len + 1];
	_tcscpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(g_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const TCHAR * fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	if (_imageInfo != NULL)
		release();

	HDC hdc = GetDC(g_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOldBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	size_t len = _tcslen(fileName);

	_fileName = new TCHAR[len + 1];
	_tcscpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(g_hWnd, hdc);

	return S_OK;
}

void Image::release()
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOldBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);

		_trans = false;
		_transColor = RGB(0, 0, 0);
	}
}

void Image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

void Image::render(HDC hdc)
{
	if (_trans)
	{
		GdiTransparentBlt
		(
			hdc,
			_imageInfo->x,
			_imageInfo->y,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor);
	}
	else
	{
		BitBlt(hdc, 
			_imageInfo->x,
			_imageInfo->y,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}

void Image::render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt
		(
			hdc,
			destX,
			destY,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}

//								�׷��� ������ ��ǥ		����� ��ġ			����� �̹��� ũ��
void Image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,
			destX,					// ����� ��ǥ X
			destY,					// ����� ��ǥ Y
			sourWidth,				// ����� ���� ũ��
			sourHeight,				// ����� ���� ũ��
			_imageInfo->hMemDC,
			sourX, sourY,			// �����ؿ� ��ǥ
			sourWidth,				// �����ؿ� ���� ũ��
			sourHeight,				// �����ؿ� ���� ũ��
			_transColor);
	}
	else
	{
		BitBlt(
			hdc, destX, destY,
			sourWidth, sourHeight,
			_imageInfo->hMemDC,
			sourX, sourY,
			SRCCOPY);
	}
}

void Image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	static int nLoopCount = 0;
	static int nRenderCount = 1;

	// ȭ�� ������ ���� �κп� ���� ����
	if (offsetX < 0)
	{
		offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	}

	if (offsetY < 0)
	{
		offsetY = _imageInfo->height + (offsetY % _imageInfo->height);
	}

	// offset ������ �޾ƿ� ����
	int sourWidth;
	int sourHeight;

	// �׷��ִ� ����
	RECT rcDest;
	RECT rcSour;

	// �׷��ִ� ������ ����ش�.
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawAreaX;
	int drawAreaH = drawArea->bottom - drawAreaY;

	// ������ y�����
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;

		sourHeight = rcSour.bottom - rcSour.top;

		// �׷��ִ� ������ ���̺��� y���� ũ��
		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		// ȭ�� ������ ���� ������ŭ �ѷ��� ��ġ�� �ݿ�
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		// x�� ����...
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc,
				rcDest.left, rcDest.top,		// �ѷ��� ��ġ ��ǥ
				rcSour.left, rcSour.top,		// ������ �̹��� ��ġ ��ǥ
				rcSour.right - rcSour.left,		// �̹����� ����
				rcSour.bottom - rcSour.top);	// �̹����� ����

			nRenderCount++;
		}
	}

	nLoopCount++;
}

void Image::frameRender(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,
			destX,					// ����� ��ǥ X
			destY,					// ����� ��ǥ Y
			_imageInfo->frameWidth,	// ����� ���� ũ��
			_imageInfo->frameHeight,// ����� ���� ũ��
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth, // �����ؿ� ��ǥ
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,	// �����ؿ� ���� ũ��
			_imageInfo->frameHeight,// �����ؿ� ���� ũ��
			_transColor);
	}
	else
	{
		BitBlt(
			hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth, // �����ؿ� ��ǥ
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

void Image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		GdiTransparentBlt(
			hdc,
			destX,					// ����� ��ǥ X
			destY,					// ����� ��ǥ Y
			_imageInfo->frameWidth,	// ����� ���� ũ��
			_imageInfo->frameHeight,// ����� ���� ũ��
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth, // �����ؿ� ��ǥ
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,	// �����ؿ� ���� ũ��
			_imageInfo->frameHeight,// �����ؿ� ���� ũ��
			_transColor);
	}
	else
	{
		BitBlt(
			hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth, // �����ؿ� ��ǥ
			currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}



