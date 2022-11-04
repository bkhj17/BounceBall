#include "Game.h"
#include "Timer.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

Timer::Timer() {}
Timer::~Timer() {}

HRESULT Timer::init() {
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency)) {
		_isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);

		_timeScale = 1.f / (float)_periodFrequency;
	}
	else {
		//구형
		_isHardware = false;
		_lastTime = timeGetTime();	// GetTickCount64();

		_timeScale = 1.f / (float)_periodFrequency;
	}

	_frameRate = 0;
	_FPSFrameCount = 0;
	_FPSTimeElapsed = 0;
	_worldTime = 0;

	return S_OK;
}

void Timer::tick(float lockFPS)
{
	if (_isHardware) {
		QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	}
	else {
		_curTime = timeGetTime();
	}

	_timeElapsed = (_curTime - _lastTime) * _timeScale;

	if (lockFPS > 0.f) {
		//고정 프레임 방식 사용 = 프레임 스키핑
		while (_timeElapsed < 1.0f / lockFPS) {
			if (_isHardware)
				QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			else
				_curTime = timeGetTime();

			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}

	_lastTime = _curTime;
	_FPSFrameCount++;
	_FPSTimeElapsed += _timeElapsed;
	_worldTime += _timeElapsed;

	if (_FPSTimeElapsed > 1.f) {
		_frameRate = _FPSFrameCount;
		_FPSFrameCount = 0;
		_FPSTimeElapsed = 0.f;
	}
}

unsigned long Timer::getFrameRate(TCHAR * str, int nStr) const
{
	if (str != NULL) {
		_stprintf_s(str, nStr, TEXT("FPS : %d"), _frameRate);
	}

	return _frameRate;
}
