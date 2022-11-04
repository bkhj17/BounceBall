#include "Game.h"
#include "gameNode.h"

gameNode::gameNode()
{
}

gameNode::~gameNode()
{
}

HRESULT gameNode::init()
{
	_hdc = GetDC(g_hWnd);
	_managerInit = false;

	return S_OK;
}

HRESULT gameNode::init(bool bInit)
{
	_hdc = GetDC(g_hWnd);
	_managerInit = bInit;

	if (_managerInit)
	{
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		//SetTimer(g_hWnd, 1, 10, NULL);
		TIMEMANAGER->init();
	}

	return S_OK;
}

void gameNode::update()
{
	InvalidateRect(g_hWnd, NULL, false);
}

void gameNode::render()
{

}

void gameNode::release()
{
	if (_managerInit)
	{
		KEYMANAGER->release();
		IMAGEMANAGER->release();
		TIMEMANAGER->release();
	}
	ReleaseDC(g_hWnd, _hdc);
}

LRESULT gameNode::MainProc(HWND _hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC			hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(_hWnd, &ps);
		this->render();
		EndPaint(_hWnd, &ps);
	}
	break;
	case WM_LBUTTONDOWN:
		g_ptMouse.x = static_cast<float>LOWORD(lParam);
		g_ptMouse.y = static_cast<float>HIWORD(lParam);
		break;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		case VK_LEFT:
			break;
		case VK_RIGHT:
			break;
		case VK_UP:
			break;
		case VK_DOWN:
			break;
		}
	}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(_hWnd, iMessage, wParam, lParam));
}



