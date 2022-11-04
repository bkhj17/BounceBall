#pragma once
class Timer
{
private:
	bool			_isHardware;			// CPU 클럭 사용 여부
	float			_timeScale;				// CPU에 신호를 보내고 받을때의 시간량
	float			_timeElapsed;			// 시간차

	__int64			_curTime;				// QPC(Query Performance Count)에 사용되는 현재 시간
	__int64			_lastTime;				// QPC에 사용되는 지난 시간 
	__int64			_periodFrequency;		// QPF에서 사용되는 주기(클록) 값

	unsigned long	_frameRate;				// 프레임 속도
	unsigned long	_FPSFrameCount;			// 프레임 카운트

	float			_FPSTimeElapsed;		// 프레임 당 시간차
	float			_worldTime;				// 타이머 시작 후 지난 시간(초단위)

public:
	Timer();
	~Timer();

	HRESULT			init();
	void			tick(float lockFPS = 0.0f);
	unsigned long	getFrameRate(TCHAR * str = NULL, int nStr = 0) const;

	inline float	getElapsedTime() const { return _timeElapsed; }
	inline float	getWorldTime() const { return _worldTime; }

};

