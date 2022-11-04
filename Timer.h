#pragma once
class Timer
{
private:
	bool			_isHardware;			// CPU Ŭ�� ��� ����
	float			_timeScale;				// CPU�� ��ȣ�� ������ �������� �ð���
	float			_timeElapsed;			// �ð���

	__int64			_curTime;				// QPC(Query Performance Count)�� ���Ǵ� ���� �ð�
	__int64			_lastTime;				// QPC�� ���Ǵ� ���� �ð� 
	__int64			_periodFrequency;		// QPF���� ���Ǵ� �ֱ�(Ŭ��) ��

	unsigned long	_frameRate;				// ������ �ӵ�
	unsigned long	_FPSFrameCount;			// ������ ī��Ʈ

	float			_FPSTimeElapsed;		// ������ �� �ð���
	float			_worldTime;				// Ÿ�̸� ���� �� ���� �ð�(�ʴ���)

public:
	Timer();
	~Timer();

	HRESULT			init();
	void			tick(float lockFPS = 0.0f);
	unsigned long	getFrameRate(TCHAR * str = NULL, int nStr = 0) const;

	inline float	getElapsedTime() const { return _timeElapsed; }
	inline float	getWorldTime() const { return _worldTime; }

};

