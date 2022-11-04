#pragma once

// <Windows.h> �� �� �ȿ� ����
#include "commonMacroFunction.h"	

// �ý��� ��� �߰� �κ�
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

// ����� ���� ��� �߰� �κ�
#include "randomFunction.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "Image.h"
#include "util.h"
#include "txtData.h"


// ��ũ��
#define WINSTARTX		50
#define WINSTARTY		50
#define WINSIZEX		1250
#define WINSIZEY		750

// ���� ��ũ�� ������ �߰� �κ�
#define IMAGEMANAGER	ImageManager::getSingleton()
#define KEYMANAGER		KeyManager::getSingleton()
#define RND				randomFunction::getSingleton()
#define TXTDATA			txtData::getSingleton()
#define TIMEMANAGER		TimeManager::getSingleton()
#define SCENEMANAGER	SceneManager::getSingleton()
#define SOUNDMANAGER	SoundManager::getSingleton()

#define SAFE_DELETE(p)	{ if(p) { delete(p); (p) = NULL; }}
#define SAFE_RELEASE(p) { if(p) { (p)->release(); (p) = NULL; }}

// EXTERN ������ ���� �߰� �κ�
extern HWND			g_hWnd;
extern HINSTANCE	g_hInstance;
extern POINT		g_ptMouse;
