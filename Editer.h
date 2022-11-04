#pragma once

class Block;
class Editer : public singletonBase<Editer>
{
public:
	Editer();
	~Editer();

	bool save(const TCHAR* fileName, int dx, int dy, Block block[][15]);
	bool load(const TCHAR* fileName, int dx, int dy, Block block[][15]);

	vector<string> dirLoad(const TCHAR * dirName);
	
	//map<string, bool> StageLoad(const TCHAR* fileName);
	//bool stageSave(const TCHAR* fileName, map<string, bool> mStage);

	vector<pair<string, bool>> StageLoad(const TCHAR* fileName);
	bool stageSave(const TCHAR* fileName, vector<pair<string, bool>> vStage);
};

