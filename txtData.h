#pragma once
#include "singletonBase.h"

class txtData : public singletonBase<txtData>
{
	typedef map<pair<string, string>, string> INIMap;
	typedef map<pair<string, string>, string>::iterator INIMap_it;

	INIMap		mINIData;
	INIMap_it	miINIData;

	string		strPath;
public:
	txtData();
	~txtData();

	HRESULT init();
	void	release();

	//txt파일 저장
	void	txtSave(const TCHAR* saveFileName, vector<string> vStr);
	void	txtSave2(const TCHAR* saveFileName, vector<string> vStr);
	void	vectorArrayCombine(TCHAR* str, int _strCount, vector<string> vArray);

	//txt파일 불러오기
	vector<string> txtLoad(const TCHAR* loadFileName);
	vector<string> txtLoad2(const TCHAR* loadFileName);
	vector<string> charArrayseperation(TCHAR charArray[]);

	// INI File Path Setting
	bool INIFilePathSetting();
	// INI File Load
	string GetINIFileInfo(const TCHAR* pszSection, const TCHAR* pszKey, const TCHAR* pszFile);
	// INI File Save
	void setINIFileInfo(const TCHAR* pszSection, const TCHAR* pszKey, const TCHAR* pszData, const TCHAR* pszFile);
};

