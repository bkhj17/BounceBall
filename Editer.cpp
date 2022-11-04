#include "Game.h"
#include "Editer.h"
#include "Block.h"
#include <io.h>

Editer::Editer() {}
Editer::~Editer() {}

bool Editer::save(const TCHAR* fileName, int dx, int dy, Block block[][15])
{
	TCHAR szTemp[128];

	vector<string> vStr;

	for (int x = 0; x < dx; x++) {
		for (int y = 0; y < dy; y++) {
			if (block[x][y].isValid() && block[x][y].getIndex() != 0) {
				_stprintf_s(szTemp, _countof(szTemp), TEXT("%d-%d-%d"), x, y, (int)block[x][y].getIndex());
				vStr.push_back(szTemp);
			}
		}
	}
	TXTDATA->txtSave2(fileName, vStr);

	return false;
}

bool Editer::load(const TCHAR* fileName, int dx, int dy, Block block[][15])
{
	vector<string> vStr = TXTDATA->txtLoad2(fileName);
	if (vStr.begin() == vStr.end()) return false;

	vector<string>::iterator it = vStr.begin();
	vector<string>::iterator it_end = vStr.end();

	TCHAR szTemp[128];
	int x, y, index;
	const TCHAR* sep = TEXT("-");
	TCHAR* token;
	TCHAR* token_next = NULL;

	for (int x = 0; x < dx; x++) {
		for (int y = 0; y < dy; y++) {
			block[x][y].init(0, false);
		}
	}

	for (; it != it_end; it++) {
		_stprintf_s(szTemp, _countof(szTemp), TEXT("%s"), it->c_str());

		token = _tcstok_s(szTemp, sep, &token_next);
		x = atoi(token);
		token = _tcstok_s(NULL, sep, &token_next);
		y = atoi(token);
		token = _tcstok_s(NULL, sep, &token_next);
		index = atoi(token);

		if (x >= 0 && x < dx && y >= 0 && y < dy) {
			block[x][y].init(index);
			block[x][y].setValid(true);
		}
	}

	return true;
}

vector<string> Editer::dirLoad(const TCHAR * dirName)	//\\전까지만 입력
{
	vector<string> vFile;

	_finddata_t fd;
	intptr_t  handle;
	int result = 1;

	TCHAR str[128] = { 0, };

	_stprintf_s(str, _countof(str), TEXT("%s\\*"), dirName);

	handle = _findfirst(str, &fd);  //현재 폴더 내 모든 파일을 찾는다.

	if (handle == -1)
	{
		//로드 실패
		return vFile;
	}

	while (result != -1)
	{
		//디렉토리 주소와 상위 디렉토리 주소를 블록
		if (_tcscmp(fd.name, TEXT(".")) != 0 && _tcscmp(fd.name, TEXT("..")) != 0 && _tcscmp(fd.name, TEXT("Test")))
			vFile.push_back(fd.name);

		result = _findnext(handle, &fd);
	}

	_findclose(handle);

	return vFile;
}
/*
map<string, bool> Editer::StageLoad(const TCHAR* fileName) {

	map<string, bool> mStage;

	vector<string> vStr = TXTDATA->txtLoad2(fileName);
	if (vStr.empty()) {
		//파일 없음 or 정보 없음
	}
	else {
		vector<string>::iterator it_str = vStr.begin();

		TCHAR szTemp[128];

		TCHAR stageName[128];
		bool isLock;

		const TCHAR* sep = TEXT("-");
		TCHAR* token;
		TCHAR* token_next = NULL;

		for (; it_str != vStr.end(); it_str++) {
			_stprintf_s(szTemp, _countof(szTemp), TEXT("%s"), it_str->c_str());

			token = _tcstok_s(szTemp, sep, &token_next);
			_tcscpy_s(stageName, token);
			token = _tcstok_s(NULL, sep, &token_next);
			if (_tcscmp(token, "1") == 0) {
				mStage.insert(pair<string, bool>(stageName, true));
			}
			else {
				mStage.insert(pair<string, bool>(stageName, false));
			}
		}
	}

	return mStage;
}

bool Editer::stageSave(const TCHAR* fileName, map<string, bool> mStage) {
map<string, bool>::iterator it = mStage.begin();
vector<string> vStr;
TCHAR szTemp[128] = { 0, };

for (; it != mStage.end(); it++) {
if (_tcslen(it->first.c_str()) <= 0) continue;

if (it->second) {
_stprintf_s(szTemp, _countof(szTemp), TEXT("%s-1"), it->first.c_str());
vStr.push_back(szTemp);
}
else {
_stprintf_s(szTemp, _countof(szTemp), TEXT("%s-0"), it->first.c_str());
vStr.push_back(szTemp);
}
}

TXTDATA->txtSave2(fileName, vStr);

return true;
}

*/
vector<pair<string, bool>> Editer::StageLoad(const TCHAR* fileName) {

	vector<pair<string, bool>> vStage;

	vector<string> vStr = TXTDATA->txtLoad2(fileName);
	if (vStr.empty()) {
		//파일 없음 or 정보 없음
	}
	else {
		vector<string>::iterator it_str = vStr.begin();

		TCHAR szTemp[128];

		TCHAR stageName[128];
		bool isLock;

		const TCHAR* sep = TEXT("-");
		TCHAR* token;
		TCHAR* token_next = NULL;

		for (; it_str != vStr.end(); it_str++) {
			_stprintf_s(szTemp, _countof(szTemp), TEXT("%s"), it_str->c_str());

			token = _tcstok_s(szTemp, sep, &token_next);
			_tcscpy_s(stageName, token);
			token = _tcstok_s(NULL, sep, &token_next);
			if (_tcscmp(token, "1") == 0) {
				vStage.push_back(pair<string, bool>(stageName, true));
			}
			else {
				vStage.push_back(pair<string, bool>(stageName, false));
			}
		}
	}

	return vStage;
}

bool Editer::stageSave(const TCHAR* fileName, vector<pair<string, bool>> vStage) {
	vector<pair<string, bool>>::iterator it = vStage.begin();
	vector<string> vStr;
	TCHAR szTemp[128] = { 0, };

	for (; it != vStage.end(); it++) {
		if (_tcslen(it->first.c_str()) <= 0) continue;

		if (it->second) {
			_stprintf_s(szTemp, _countof(szTemp), TEXT("%s-1"), it->first.c_str());
			vStr.push_back(szTemp);
		}
		else {
			_stprintf_s(szTemp, _countof(szTemp), TEXT("%s-0"), it->first.c_str());
			vStr.push_back(szTemp);
		}
	}

	TXTDATA->txtSave2(fileName, vStr);

	return true;
}