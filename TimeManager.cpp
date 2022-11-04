#include "Game.h"
#include "TimeManager.h"
#include "Timer.h"

TimeManager::TimeManager() {}
TimeManager::~TimeManager() {}

HRESULT TimeManager::init()
{
	_timer = new Timer;
	_timer->init();

	return S_OK;
}

void TimeManager::release()
{
	SAFE_DELETE(_timer);
}

void TimeManager::update(float lockFPS)
{
	if (_timer != NULL)
		_timer->tick(lockFPS);

}

void TimeManager::render(HDC _hdc)
{
	TCHAR str[256] = { 0, };

	string frameRate;

	SetBkMode(_hdc, TRANSPARENT);

	//#ifdef _DEBUG
#if defined(_DEBUG)
	_stprintf_s(str, _countof(str), TEXT("Frame PER SEC : %d"), _timer->getFrameRate());
	TextOut(_hdc, 0, 0, str, _tcslen(str));

	_stprintf_s(str, _countof(str), TEXT("World Time : %f"), _timer->getWorldTime());
	TextOut(_hdc, 0, 20, str, _tcslen(str));

	_stprintf_s(str, _countof(str), TEXT("Elapsed Time : %f"), _timer->getElapsedTime());
	TextOut(_hdc, 0, 40, str, _tcslen(str));
#else
	_stprintf_s(str, _countof(str), TEXT("Frame PER SEC : %f"), _timer->getFrameRate());
	TextOut(_hdc, 0, 0, str, _tcslen(str));
#endif // _DEBUG

}

float TimeManager::getElapsedTime()
{
	return _timer->getElapsedTime();
}

float TimeManager::getWorldTime()
{
	return _timer->getWorldTime();
}
