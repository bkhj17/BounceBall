#include "Game.h"
#include "txtData.h"

#define STR_SIZE 128

txtData::txtData() {}
txtData::~txtData() {}

HRESULT txtData::init() {

	return S_OK;
}

void	txtData::release() {}

void	txtData::txtSave(const TCHAR* saveFileName, vector<string> vStr) {
	HANDLE file;
	TCHAR str[STR_SIZE];
	DWORD write;

	vectorArrayCombine(str, _countof(str), vStr);
	file = CreateFile(saveFileName, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, str, _tcslen(str), &write, NULL);
	CloseHandle(file);
}

void	txtData::txtSave2(const TCHAR* saveFileName, vector<string> vStr) {
	HANDLE file;
	TCHAR str[STR_SIZE];
	DWORD write;

	vector<string>::iterator it = vStr.begin();
	vector<string>::iterator it_end = vStr.end();

	file = CreateFile(saveFileName, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	for (; it != it_end; it++) {
		_stprintf_s(str, _countof(str), TEXT("%s\r\n"), (*it).c_str());
		WriteFile(file, str, _tcslen(str), &write, NULL);
	}
	CloseHandle(file);
}

void txtData::vectorArrayCombine(TCHAR* str, int _strCount, vector<string> vArray) {
	ZeroMemory(str, _strCount);

	for (int i = 0; i < vArray.size(); i++) {
		_tcsncat_s(str, _strCount, vArray[i].c_str(), _strCount - 1);

		if (i + 1 < vArray.size()) {
			_tcscat_s(str, _strCount - 1, TEXT(","));
		}
	}
	_tcscat_s(str, _strCount - 1, TEXT(","));
}

vector<string> txtData::txtLoad(const TCHAR* loadFileName) {
	HANDLE file;
	TCHAR str[STR_SIZE];
	DWORD read;

	file = CreateFile(loadFileName, GENERIC_READ, false, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, str, STR_SIZE, &read, NULL);

	CloseHandle(file);

	return charArrayseperation(str);
}

vector<string> txtData::txtLoad2(const TCHAR* loadFileName) {
	TCHAR str[STR_SIZE];

	vector<string> vStr;

	FILE *fp;

	fopen_s(&fp, loadFileName, "r");

	if (fp != NULL) {
		while (fscanf_s(fp, TEXT("%s"), str, _countof(str)) > 0) {
			vStr.push_back(str);
		}

		fclose(fp);
	}
	return vStr;
}

vector<string> txtData::charArrayseperation(TCHAR charArray[]) {
	vector<string> vArray;

	TCHAR* temp;
	const TCHAR* seperator = TEXT(",");
	TCHAR* token;
	TCHAR* token_next = NULL;

	token = _tcstok_s(charArray, seperator, &token_next);
	vArray.push_back(token);

	while (NULL != (token = _tcstok_s(NULL, seperator, &token_next))) {
		vArray.push_back(token);
	}

	return vArray;
}

bool txtData::INIFilePathSetting() {
	TCHAR szTemp[MAX_PATH] = { 0, };
	GetModuleFileName(NULL, szTemp, MAX_PATH);

	string strTemp(szTemp, szTemp + _tcslen(szTemp));

	size_t size = strTemp.rfind(TEXT("\\"), strTemp.size());

	string::iterator it = strTemp.begin();
	string::iterator it_end = it + size;

	strTemp.assign(it, it_end);

	strPath = strTemp;

	return true;
}

string txtData::GetINIFileInfo(const TCHAR* pszSection, const TCHAR* pszKey, const TCHAR* pszFile) {
	size_t size = 0;

	INIMap_it it = mINIData.find(std::make_pair<string, string>(pszSection, pszKey));
	if (it != mINIData.end()) {
		return it->second;
	}

	INIFilePathSetting();

	string strTemp;
	string strTempPath = strPath + TEXT("\\") + pszFile;

	TCHAR szTemp[100] = { 0, };
	GetPrivateProfileString(pszSection, pszKey, TEXT("None"), szTemp, sizeof(szTemp), strTempPath.c_str());

	if (!_tcscmp(strTemp.c_str(), TEXT("None")))
		return TEXT("None");
	else
		strTemp = szTemp;

	mINIData.insert(INIMap::value_type(std::make_pair<string, string>(pszSection, pszKey), strTemp));

	return strTemp;
}

void txtData::setINIFileInfo(const TCHAR* pszSection, const TCHAR* pszKey, const TCHAR* pszData, const TCHAR* pszFile) {
	INIFilePathSetting();

	string strTempPath = strPath + TEXT("\\") + pszFile;

	if (!WritePrivateProfileString(pszSection, pszKey, pszData, strTempPath.c_str())) {
		//쓰기 실패
	}
}