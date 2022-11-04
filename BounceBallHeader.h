#pragma once
#include "Game.h"
#include "Bullet.h"
#include "Ball.h"
#include "Block.h"
#include "Button.h"
#include "Editer.h"

#define EDITER			Editer::getSingleton()

//게임 정보
#define GRAVITY 0.3
#define MAXXSPEED 15
#define MAXYSPEED 15
#define MAXBULLET 500

#define DEFAULT_VOLUME 15

#define MAX_X 25
#define MAX_Y 15

#define TRANSCOLOR RGB(255, 255, 255)

// 전역
enum Color
{
	white,
	blue,
	red,
};

// 현재 파일이름 전역변수
extern TCHAR		_fileNow[128];
// 스테이지 목록
// extern map<string, bool> _mStage;
extern vector<pair<string, bool>> _vStage;