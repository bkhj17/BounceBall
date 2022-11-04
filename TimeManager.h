#pragma once

class Timer;
class TimeManager : public singletonBase<TimeManager>
{
private:
	Timer * _timer;



public:
	TimeManager();
	~TimeManager();

	HRESULT	init();
	void	release();
	void	update(float lockFPS = 0.f);
	void	render(HDC _hdc);

	float	getElapsedTime();
	float	getWorldTime();
};

