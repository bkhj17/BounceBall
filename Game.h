#pragma once

// <Windows.h> 는 이 안에 있음
#include "commonMacroFunction.h"	

// 시스템 헤더 추가 부분
#include <tchar.h>
#include <math.h>
#include <string>
#include <list>
#include <map>
#include <vector>

using std::string;
using std::list;
using std::map;
using std::vector;
using std::pair;

// 사용자 정의 헤더 추가 부분
#include "randomFunction.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "Image.h"
#include "util.h"
#include "txtData.h"


// 매크로
#define WINSTARTX		50
#define WINSTARTY		50
#define WINSIZEX		1250
#define WINSIZEY		750

// 각종 매크로 디파인 추가 부분
#define IMAGEMANAGER	ImageManager::getSingleton()
#define KEYMANAGER		KeyManager::getSingleton()
#define RND				randomFunction::getSingleton()
#define TXTDATA			txtData::getSingleton()
#define TIMEMANAGER		TimeManager::getSingleton()
#define SCENEMANAGER	SceneManager::getSingleton()
#define SOUNDMANAGER	SoundManager::getSingleton()

#define SAFE_DELETE(p)	{ if(p) { delete(p); (p) = NULL; }}
#define SAFE_RELEASE(p) { if(p) { (p)->release(); (p) = NULL; }}

// EXTERN 선언한 변수 추가 부분
extern HWND			g_hWnd;
extern HINSTANCE	g_hInstance;
extern POINT		g_ptMouse;
